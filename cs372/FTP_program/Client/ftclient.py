#!/bin/python

#vim:ts=2:

# Expecting Python 2.7.5
#
# Based on :
#	course book pg 164
# getopt example from docs.python.org
#  
import getopt
import select
import socket
import sys

DEBUG = True


def main():
	DataPort = 0 
	Hostname=""
	HostIP="0.0.0.0"
	ListFlag = CDFlag = GetFlag = BinaryFlag = ExpectFile = False
	dataReceived = bytearray(10240);

	if ( len(sys.argv) < 3 ):
		usage(25)
		sys.exit(1)

	Host = sys.argv[1]
	Port = sys.argv[2]
	try:
		opts, args = getopt.getopt(sys.argv[3:], "p:g:d:lb", ["dataport=", "get=", "dir=", "list", "binary"])
	except getopt.GetoptError as err:
		print "ERROR: ", str(err)
		usage(34)
		sys.exit(1)

	#
	# Parse arguments
	#########################################################
	if ( len(opts) == 0 ):
		usage(42)
		sys.exit(1)
	else:
		if (DEBUG): print "Got some options here: ", opts
		for (o, v) in opts:
			if (o == "-p" or o == "-port" ):
				DataPort = v
			elif (o == "-d"  or o == "-dir"):
				CDFlag = True
				RemoteDir = v
			elif (o == "-g"  or o == "-get"):
				GetFlag = True
				RemoteFile = v
			elif (o == "-l" or o == "-list"):
				ListFlag = True
			elif (o == "-b" or o == "-binary"):
				BinaryFlag = True

	if (not DataPort):
		print "ERROR: Must specify a port for receiving data"
		usage(63)
		sys.exit(1)

  # First open the reverse/data connection
  #
	#########################################################
	listenSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	listenSock.bind((socket.gethostname(), int(DataPort)))
	listenSock.listen(15)
	if (DEBUG): print "Listening on port #", DataPort

	#
	# 
	#########################################################
	if (DEBUG): print "Connecting to host", Host,"on port #", Port
	RemoteIP = socket.gethostbyname(Host)
	if (DEBUG): print "IP addr for host", Host, "is:", RemoteIP

	cmdSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	cmdSock.connect((Host, int(Port)))

	cmdSock.send("HELO " + socket.gethostname()+ " " + DataPort + "\n");
	(dataSock, address) = (listenSock.accept())

	while ( CDFlag or ListFlag or GetFlag ):
		if ( CDFlag ):
			cmdSock.send("cd " + RemoteDir + "\n");
			CDFlag = False
		elif ( ListFlag ):
			cmdSock.send("list" + "\n");
			ListFlag = False
		elif ( GetFlag ):
			# First make sure we can open the local file
			try:
				outputFile = open(RemoteFile, "wb", 0);
				ExpectFile = True
				if (BinaryFlag):
					cmdSock.send("getbin " + RemoteFile + "\n");
				else:
					cmdSock.send("get " + RemoteFile + "\n");
			except OSError as err:
				fprintf(stderr, "OS error: {0}".format(err));
				continue
			GetFlag = False

		try:
			bytesReceived = dataSock.recv(10240);
			while ( len(bytesReceived) != 0 ):
				if (ExpectFile):
					#TODO: if this is file, save to a file
					outputFile.write(bytesReceived);
				else:
					sys.stdout.write(bytesReceived);
				dataSock.settimeout(0.2);
				bytesReceived = dataSock.recv(10240);
		except socket.timeout:
			ExpectFile = False
			# do nothing, just continue

  print "Done with socketing!"

	cmdSock.close()
	dataSock.close()
	if ( GetFlag ):
		try:
			outputFile.close()
		except:
			True # Ignore

#	while 1:
#		(dataSock, address) = (listenSock.accept()
#		bytesReceived = dataSock.recv_into(dataReceived);
#		while ( bytesReceived != 0 ):
#			print dataReceived;
#			bytesReceived = dataSock.recv_into(dataReceived);
#	try:
#		bytesReceived = cmdSock.recv_into(dataReceived);
#		while ( bytesReceived != 0 ):
#			print dataReceived;
#			cmdSock.settimeout(0.1);
#			bytesReceived = cmdSock.recv_into(dataReceived);
#	except socket.timeout:
#		1 == 1
#

				

def usage(lineno):
	print "USAGE: ", sys.argv[0], "<host> <port> -p <portnum> [-g <file> | -l ] {-d dir} {-b}"
	print "WHICH: "
	print "       -p <portnum>  Specify a port number for reverse / data connection"
	print "       -g <file>     Get a file from the remote server"
	print "       -l            List the contents of the server's current directory"
	print "       -d <dir>      Change the server's directory on the remote host"
	print "                     before executing list or get"
	print "       -b            Transfer a binary file (only meaningful with -g)"
	if (DEBUG): print "(", lineno, ")"

main()
