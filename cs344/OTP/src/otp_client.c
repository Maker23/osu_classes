/* vim:ts=2
 *                      Shoshana Abrass
 *                  abrasss@oregonstate.edu
 *                    CS372_400 Program 2
 *                       May 29, 2016
 *
 *
 */
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>

#ifndef FUNCTION
#define FUNCTION ENCODE
#endif

#include "otp_proto.h"

struct Cryptic {
	char * keyfilename;
	char * textfilename;
	FILE * keyfp;
	FILE * textfp;
	int		 keyfilesize;
	int		 textfilesize;
};

main (int argc, char ** argv)
{
	struct Cryptic myCrypt;
	char Hostname[NI_MAXHOST];
	char buffer[BUFSZ];
	int	 sSock;
	int  rv;
	int  scancount;


	if (argc < 4 )
	{
		usage(argv[0]);
		exit(1);
	}

	myCrypt.textfilename=argv[1];
	myCrypt.keyfilename=argv[2];
	if (( rv = openFiles(&myCrypt) ) < 0 ) { exit(1); }

	if ((rv= gethostname(Hostname,sizeof(Hostname)) < 0))
	{
		perror("gethostname");
		exit(1);
	}
	if (( sSock = openOTPServerSocket(Hostname, argv[3])) < 0)
	{
		fprintf(stderr, "Failed to open socket on port %s: %s\n", argv[3], strerror(errno));
		exit(1);
	}
	/* **************************************************
	 * Confirm the daemon does what we want: 
	 * send the FUNCTION command
	 * **************************************************/
	memset(buffer,0, sizeof(buffer));
	sprintf(buffer, "%s\n", FUNCTION_CMD);
	send(sSock, buffer, strlen(buffer), 0);
	recv(sSock, buffer, sizeof(buffer)-1, 0);
	sscanf(buffer, "%*3s%*[ ]%d%n", &rv, &scancount);
	if (scancount < 5)
	{
		fprintf (stderr, "Server refused protocol handshake (wrong port #?)\n");
		exit(1);
	}
	if (rv != FUNCTION)
	{
		fprintf(stderr, "ERROR: Could not contact ");
		if ( FUNCTION == DECODE )
			fprintf(stderr, "decryption");
		else
			fprintf(stderr, "encryption");
		fprintf(stderr, " server on port %s.  Exiting...\n", argv[3]);

		exit(2);
	}
		
	/* **************************************************
	 * Send the key
	 * **************************************************/
	memset(buffer,0, sizeof(buffer));
	sprintf(buffer, "%s %d\n", KEY_CMD, myCrypt.keyfilesize);
	send(sSock, buffer, strlen(buffer), 0);
	if ( sendFileInChunks(sSock, myCrypt.keyfp) < 0 )
	{
		fprintf(stderr, "Failed to send key file %s\n",myCrypt.keyfilename);
		exit(1);
	}

	/* **************************************************
	 * Send the text to be encrypted or decrypted
	 * **************************************************/
	memset(buffer,0, sizeof(buffer));
	sprintf(buffer, "%s %d\n", FILE_CMD, myCrypt.textfilesize);
	send(sSock, buffer, strlen(buffer), 0);
	if ( sendFileInChunks(sSock, myCrypt.textfp) < 0 )
	{
		fprintf(stderr, "Failed to send text file %s\n",myCrypt.textfilename);
		exit(1);
	}

	/* **************************************************
	 * Now expect back the encrypted or decrypted version.
	 * Should be the same size as the text we sent.
	 * **************************************************/
	DEBUG && fprintf(stderr, "DEBUG receiving %d bytes\n", myCrypt.textfilesize);
	memset(buffer,0, sizeof(buffer));
	recv(sSock, buffer, sizeof(buffer)-1, MSG_PEEK);
	if ( (strncasecmp(buffer, BAD_RESPONSE, strlen(BAD_RESPONSE) )) == 0 )
	{
		fprintf(stderr, "ERROR: daemon responded with %s\n", buffer);
		exit(1);
	}
	/* Just print the received text to stdout per the assignment */
	receiveFileInChunks(sSock, stdout, myCrypt.textfilesize);
	fprintf(stdout, "\n");
}


/*
 * Wackiness ensues: We open a socket with the server,  
 * are given a new port #, and have to open another socket.
 * Do all that here.
 */
int openOTPServerSocket(char *Hostname, char * PortStr)
{
	char buffer[BUFSZ];
	char newPortStr[16];
	int sSock, tSock;
	int	recvcount;

	memset(buffer,0, sizeof(buffer));
	if (( sSock = openSocketConnection(Hostname, PortStr)) < 0)
	{
		perror("Open socket");
		exit(1);
	}
	recvcount = recv(sSock,&buffer,sizeof(buffer), 0);
	if (recvcount <= 0)
	{
		perror("Received no data from server");
		return(-1);
	}
	close(sSock);

	/* **************************************************
	 * Expect to see the Reconnect command with a new port #
	 * Anything else is an error.
	 * **************************************************/
	if ((strncasecmp(buffer, RECONNECT_CMD, strlen(RECONNECT_CMD))) != 0 )
	{
		fprintf(stderr, "Received unrecognized command from server \"%s\"\n", buffer);
		return(-1);
	}

	sscanf(buffer, "%*3s %s", newPortStr);
	tSock = openSocketConnection(Hostname, newPortStr);
	if ( tSock < 0 )
	{
		perror("Reconnect socket");
		exit(1);
	}
	DEBUG && fprintf(stderr, "Reconnecting on port %s\n", newPortStr);
	return (tSock);
}

int openFiles ( struct Cryptic * myCrypt)
{
	int rv;
	struct stat statbuf;

	if ((rv = stat(myCrypt->textfilename, &statbuf)) < 0 )
	{
		perror(myCrypt->textfilename);
		return(-1);
	}
	myCrypt->textfilesize = (int) statbuf.st_size - 1;
	if ((rv = stat(myCrypt->keyfilename, &statbuf)) < 0 )
	{
		perror(myCrypt->keyfilename);
		return(-1);
	}
	myCrypt->keyfilesize = (int) statbuf.st_size - 1;

	if ( myCrypt->keyfilesize < myCrypt->textfilesize )
	{
		fprintf(stderr,"ERROR: key file must be at least as long as text file\n");
		fprintf(stderr,"       (%d byte key required for %s)\n",
			myCrypt->textfilesize, myCrypt->textfilename);
		return(-1);
	}

	if ((myCrypt->textfp = fopen(myCrypt->textfilename, "r")) == NULL) 
	{
		fprintf(stderr, "Can't open %s for reading: %s\n",
			myCrypt->textfilename, strerror(errno));
		return(-1);
	}
	if ((myCrypt->keyfp = fopen(myCrypt->keyfilename, "r")) == NULL) 
	{
		fprintf(stderr, "Can't open %s for reading: %s\n",
			myCrypt->keyfilename, strerror(errno));
		return(-1);
	}
}

/* **********************************************************
 * openSocketConnection
 *
 * returns a valid sockfd file descriptor for a given hostname
 * and portnumber, or -1 on error
 *
 * ********************************************************* */
int openSocketConnection ( char * host, char * port)
{
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // In theory we could use IPv6
	hints.ai_socktype = SOCK_STREAM; // TCP please :)

  // Fill the servinvo struct with information about "host"
	if ((rv = getaddrinfo(host, port, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return -1;
	}

	// loop through all the results and connect to the first we can
	// Although this is silly 'cause we're all about the IPv4 here
	for(p = servinfo; p != NULL; p = p->ai_next) {
		DEBUG && fprintf (stderr,"DBG family = %d, socktype = %d, protocol = %d\n",
			p->ai_family, p->ai_socktype, p->ai_protocol);

		// Create the socket
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("client: socket");
			continue;
		}

		// Connect the socket to the destination host
		// The port number is part of the sockaddr struct at p->ai_addr
		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			perror("client: connect");
			close(sockfd);
			continue;
		}
		break;
	}

	if (p == NULL) {
		fprintf(stderr, "client: failed to connect\n");
		return -1;
	}

	DEBUG && fprintf(stderr, "Connected to %s:%s\n", host, port);

	return (sockfd);
}


usage(progname)
{
	fprintf(stderr, "USAGE: %s <textfile> <keyfile> <port>\n");
	fprintf(stderr, "WHERE:\n");
	fprintf(stderr, "       <textfile> is a file to ");

	if ( FUNCTION == DECODE ) 
		fprintf(stderr, "decrypt\n");
	else
		fprintf(stderr, "encrypt\n");

	fprintf(stderr, "       <keyfile> contains the ");
	if ( FUNCTION == DECODE ) 
		fprintf(stderr, "decryption key\n");
	else
		fprintf(stderr, "encryption key\n");

	
	fprintf(stderr, "       <port> is the listening port of the ");
	if ( FUNCTION == DECODE ) 
		fprintf(stderr, "decryption server\n");
	else
		fprintf(stderr, "encryption server\n");

}
