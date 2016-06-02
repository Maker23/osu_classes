/* vim:ts=2
 *                      Shoshana Abrass
 *                  abrasss@oregonstate.edu
 *                    CS372_400 Program 2
 *                       May 29, 2016
 *
 * FTP server based on sample code at tldp.
 * See README file for more code attribution.
 *
 * USAGE: ftserver <port>
 * WHICH: opens a TCP listening socket on port and accepts
 *        incoming requests (1 at a time)
 *
 * The server remains running until it receives a SIGINT or <ctrl>-C
 *
 */
#include <dirent.h>
#include <errno.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // Yup, there's two of 'em
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#ifndef FUNCTION
#define FUNCTION ENCODE
#endif

#include "otp_proto.h"

#define DEBUG 1
#define BUFSZ 1024

enum States {
	looking_for_command,
	receiving_key,
	receiving_file,
	sending_file,
	closing,
};

struct Connection {
	int 	CSock; // File descriptor
	enum 	States State;
	char *Host_name;
	char *CPort_name;
	char *dataBuf;
	int  	expectMoreData;
};

void signalHandler (int param);
int setUpServSocket(struct addrinfo *hints, char * PortString);
int stripTrailingNewline(char * theString);
void * logaroo (char *stringy);

int main ( int argc, char ** argv )
{
	int pid;
	int errcount = 0; // So we can end gracefully if something goes wrong
	int ServerListenSocket, ChildListenSocket, ServerDataSocket, ChildDataSocket;

	struct addrinfo hints;
	struct sockaddr_in client_sockaddr;
	socklen_t sin_size;

	char * PortStr;
	char ChildPortStr[16];
	unsigned short ChildPortNum;
	char serverHostname[NI_MAXHOST];
	char clientIP[256];
	char officialClientHostname[NI_MAXHOST]; 
	char clientService[NI_MAXSERV];
	char logString[8192];
	char sendData[BUFSZ];

	struct Connection clientConnect;

	if ( argc < 2 ) {
		// This is the only argument validation we do. 
		// If the argument isn't a valid port number or service name 
		// then setUpServSocket will fail
		fprintf(stderr, "Usage : %s <portnumber>\n", argv[0]);
		exit(1);
	}
	memset (&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; //TODO; look this up

	/* ***************************
	 * Create the listening socket
	 * **************************/
	PortStr = argv[1];
	if ( (ServerListenSocket = setUpServSocket(&hints,PortStr) ) < 0 )
	{
		exit(ServerListenSocket);
	}
	ChildPortNum = (unsigned short) atoi(PortStr);
	gethostname(serverHostname, sizeof (serverHostname) - 1);
	sprintf(logString, "Server listening on %s port %s", serverHostname, PortStr);
	logaroo(logString);

	// TODO: Parent close stdin and set stdout to logfile

	/* ********************************************************
	 * Loop indefinitely waiting for connect() on the listening
	 * socket. The only way to end is with a SIGINT or <ctrl>-c
	 * ********************************************************/
	while ( 1 )
	{
			ChildPortNum++;
			sprintf(logString, "Waiting for client to connect...");
			logaroo(logString);
			sin_size = sizeof(client_sockaddr);
			ServerDataSocket = accept(ServerListenSocket, (struct sockaddr *) &client_sockaddr, &sin_size);
			if (ServerDataSocket == -1)
			{
				sprintf(logString, "Failed to accept connection %d\n", errcount);
				logaroo(logString);
				// Limit prevents an infinite while loop if something goes wrong
				if ( errcount > 5 ) 
					exit(1);
				errcount++;
				continue;
			}
			/* ************************************************************* */
			sprintf(ChildPortStr, "%hu", ChildPortNum);
			if ( (ChildListenSocket = setUpServSocket(&hints,ChildPortStr) ) < 0 )
			{
				perror("ChildListenSocket"); //TODO: log this, but only if we're debugging
				ChildPortNum++; // Try again until we find a free port

				if ( ChildPortNum > 65500 )
					exit(1); // TODO: Log and warn and stuff
				
				sprintf(ChildPortStr, "%hu", ChildPortNum);
			}

			/* 
			 * Now we have a listening child port. Send a Reconnect command
			 * to the client. Close the client socket. Fork here.
			 */
			if (DEBUG) fprintf(stdout, "Client will reconnect on port %s (%d)\n", ChildPortStr, ChildPortNum);
			snprintf(sendData, BUFSZ, "%s %s\n", RECONNECT_CMD, ChildPortStr);
			send(ServerDataSocket, sendData, strlen(sendData), 0);

			pid = fork();
			if ( pid < 0 )
			{
				// FATAL ERROR oh noes what to do
			}
			else if (pid == 0 )
			{
				// Child process
				close(ServerDataSocket);
				ChildDataSocket = accept(ChildListenSocket, (struct sockaddr *) &client_sockaddr, &sin_size);
				if (ChildDataSocket == -1)
				{
					sprintf(logString, "Failed to accept connection %d\n", errcount);
					logaroo(logString);
					// Limit prevents an infinite while loop if something goes wrong
					if ( errcount > 5 ) 
						exit(1);
					errcount++;
					continue;
				}
				/* ********************************************************
				 * Store these values in the clientConnect struct so we can
				 * pass them to subroutines. 
				 * *******************************************************/
				clientConnect.Host_name = officialClientHostname;
				clientConnect.CPort_name = ChildPortStr;
				clientConnect.CSock = ChildDataSocket;
				clientConnect.State = looking_for_command; // initially
				clientConnect.dataBuf = malloc(BUFSZ * sizeof(char));
				clientConnect.expectMoreData = 0;

				exit ( handleConnection(&clientConnect));
			}
			else
			{
				// Parent process
				// Log connection; close sockets
				

				// Get information about the client so we can print a useful log message 
				// Use the name of the client if we can get it - otherwise the IP address
				inet_ntop(client_sockaddr.sin_family, &(client_sockaddr.sin_addr), clientIP, sizeof(clientIP));
				if (( getnameinfo((struct sockaddr *) &client_sockaddr, sizeof(struct sockaddr_in), 
						officialClientHostname, NI_MAXHOST, clientService, NI_MAXSERV, NI_NUMERICSERV)) == 0)
				{
					char * cptr;
					if ( (cptr=strchr(officialClientHostname, '.')) != NULL )
						*cptr = '\0';
					sprintf (logString, "Client connection from %s, assigned to port ", 
						officialClientHostname, ChildPortNum);
				}
				else
				{
					sprintf (logString, "Client connection from %s assigned port", 
						clientIP, ChildPortNum);
				}
				logaroo(logString);
				close(ChildListenSocket);
				close(ServerDataSocket);
			}
			/* Child closes the parent listening port and waits on the new port.
			 * Parent closes the child connect port and goes back to the 
			 * listening wait loop.
			 */

			DEBUG && fprintf(stdout, "End of outer while (listen / accept)\n");
		}

	return 0;
}

int handleConnection(struct Connection * clientConnect)
{
	int retval; // capture return values
	char recvData[BUFSZ];
	char sendData[BUFSZ];
	ssize_t recvBytes, sendBytes;
	char *cryptoKey;
	char *clearFile;
	char *cryptoFile;
	char errorString[BUFSZ];

	char *key;
	char *file;
	int keylen=256; 	// initial value
	int filelen=4096; // initial value

	/* ********************************************************
	* Loop indefinitely on the client socket, collecting commands
	* and acting on them. This exits when the client closes the socket.
	* ********************************************************/
	while ( 1 )
	{
		/*
		 * Receive data from the socket, store it in a char array for
		 * processing.
		 */
		memset(recvData, 0, sizeof(recvData));
		memset (clientConnect->dataBuf, 0, sizeof(clientConnect->dataBuf));
		recvBytes = recv(clientConnect->CSock, &recvData, sizeof(recvData)-1,0);
		if (recvBytes < 0 )
		{
			fprintf(stderr, "recv bytes: %s\n", gai_strerror(errno));
			close(clientConnect->CSock);
			return(1);
		}
		else if (recvBytes == 0 )
		{
			DEBUG && fprintf(stderr, "recv bytes: %s\n", gai_strerror(errno));
			close(clientConnect->CSock);
			return(1);
		}
		DEBUG && fprintf(stdout, "DBG received raw message |%s| from client\n", recvData);

		/* *******************************************************
		 * Strip trailing newlines and CRs
		 * Send resulting string to subroutine for parsing and execution
		 * ******************************************************/
		stripTrailingNewline(recvData);
		DEBUG && fprintf(stdout, "DBG received message |%s| from client\n", recvData);

		// TODO: use fcntl to non-block the receive
		retval = parseReceiveBuffer(clientConnect, &recvData, strlen(recvData));
		if ( retval < 0 )
		{
			// Fatal error
			close(clientConnect->CSock);
			return(retval);
		}
		if ( retval > 0 )
		{
			snprintf(sendData, BUFSZ, "%s %s\n", BAD_RESPONSE, clientConnect->CPort_name);
			send(clientConnect->CSock, sendData, strlen(sendData), 0);
		}
		else
		{
			if ( clientConnect->State == closing )
			{
				DEBUG && fprintf(stdout, "CLOSE command issued\n");
				close(clientConnect->CSock);
				return(0);
			}
			else if ( clientConnect->State == receiving_key )
			{
				// Append buffer to long key or key file
			}
			else if ( clientConnect->State == receiving_file )
			{
				// Append buffer to long file or file
			}

			if ( clientConnect->expectMoreData == 0)
			{
				// Or, respond with the file if that's a thing
				snprintf(sendData, BUFSZ, "%s %s\n", OK_RESPONSE, clientConnect->CPort_name);
				send(clientConnect->CSock, sendData, strlen(sendData), 0);
			}
		}

		DEBUG && fprintf(stdout, "End of inner while (receive data)\n");
		memset(errorString, 0, sizeof(errorString)); // TODO we're not really using this
		fflush(stderr);
		fflush(stdout);
	}
	return(0);
}
/* *********************************************************
 * parseReceiveBuffer()
 *
 * All the work of parsing and executing client commands
 * happens here.
 *
 * Returns:
 * 0    success
 * >0   soft fail, keep going
 * <0   hard fail, close the connection
 *
 * *********************************************************/
int parseReceiveBuffer(struct Connection* clientConnect, char * recvData, int recvBytes)
{

	int retval;
	char errorString[BUFSZ];
	char logString[8192];
	int dataLength=0;
	int bufLength=0;
	int scancount=0,ccount;
	int state;
 	char command[4];

	// Defined by the protocol
	char KeyCmd[] = KEY_CMD;
	char FileCmd[] = FILE_CMD;
	char CloseCmd[] = CLOSE_CMD;
	//char KeyCmd[] = "KEY";
	//char FileCmd[] = "FIL";
	//char CloseCmd[] = "CLO";

	/* ******************************************************* */

	DEBUG &&  fprintf(stderr, "DBG Entering parseReceiveBuffer\n");
	DEBUG && fprintf(stdout, "DBG received on socket |%s|, recvBytes=%d\n", recvData, recvBytes);

	if ( clientConnect->expectMoreData > 0 )
	{
		// It's just data; don't change the state.
		DEBUG && fprintf(stdout, "Getting more data: start: %d (state=%d)\n", clientConnect->expectMoreData, clientConnect->State);
		for (ccount = 0; ccount < recvBytes; ccount++)
		{
			if (ccount > 1023) 
			{
				DEBUG && fprintf (stdout, "Exceeded sizeof buffer %d\n", sizeof(clientConnect->dataBuf));
				break;
			}
			clientConnect->dataBuf[ccount] = recvData[ccount];
		}
		if ( strlen(clientConnect->dataBuf) > clientConnect->expectMoreData )
		{
			clientConnect->expectMoreData = 0;
		}
		else
		{
			clientConnect->expectMoreData -= strlen(clientConnect->dataBuf);
		}
		DEBUG && fprintf(stdout, "Getting more data:   end: %d (state=%d)\n", clientConnect->expectMoreData, clientConnect->State);
		DEBUG && fprintf(stdout, "More data string is |%s|\n", clientConnect->dataBuf);
		return(0);
	}

  /* Looking for something other than data - shoudl be a command */

	memset (command, 0, sizeof(command));
	sscanf(recvData, "%3s", command);

  if ((strcmp(command,"") == 0) || ( recvBytes < 3 )) {

		sprintf(logString, "DBG unrecognized command |%s| from %s", command, clientConnect->Host_name);
		DEBUG && fprintf(stdout, "%s\n", logString);
		logaroo(logString);
		return(1);
	}

	if ( (strncasecmp(command, CloseCmd, strlen(CloseCmd))) == 0 )
	{
		clientConnect->State=closing;
		return(0);
	}
	else if ( (strncasecmp(command, KeyCmd,  strlen(KeyCmd)))  == 0 
	        ||(strncasecmp(command, FileCmd, strlen(FileCmd))) == 0 )
	{
		sscanf(recvData, "%*3s%*[ ]%d%n", &dataLength, &scancount); // TODO: check for errors
		scancount++;
		DEBUG && fprintf(stdout, "DBG recvBytes = %d, scancount = %d\n", recvBytes, scancount);
		for (ccount = scancount; ccount < recvBytes; ccount++)
		{
			bufLength = ccount - scancount; // Starts at 0
			clientConnect->dataBuf[bufLength] = recvData[ccount];
		}
		DEBUG && fprintf(stdout, "DBG length = %d, data = |%s|\n", dataLength, clientConnect->dataBuf);
		DEBUG && fprintf(stdout, "DBG got %d bytes\n", strlen(clientConnect->dataBuf));
		if ( dataLength == 0 )
		{
			return(1);
		}

		if ( strlen(clientConnect->dataBuf) < dataLength )
		{
			// More data is coming
			clientConnect->expectMoreData = dataLength - strlen(clientConnect->dataBuf);
			if ( (strncasecmp(command, KeyCmd,  strlen(KeyCmd)))  == 0 )
			{
				clientConnect->State=receiving_key;
			}
			else		
			{
				clientConnect->State=receiving_file;
			}
		}
	}
	else
	{
		clientConnect->State=looking_for_command;
		sprintf(logString, "DBG unrecognized command |%s| from %s", command, clientConnect->Host_name);
		DEBUG && fprintf(stdout, "%s\n", logString);
		logaroo(logString);
		return(1); // TODO: should this be fatal?
	}

	return(0);

	DEBUG && 	fprintf(stderr, "Exiting parseReceiveBuffer\n");
}

int setUpServSocket(struct addrinfo *hints, char * PortString)
{
	struct addrinfo *servInfo, *p;
	int savError;
	int status;
	int yes=1;
	int sockListen;
	struct servent * sstatus;
 
	DEBUG && fprintf(stdout, "Entering setUpServSocket\n");
	
 	
	if ( (status = getaddrinfo(NULL, PortString, hints, &servInfo)) !=0 ) 
	{
		savError = errno;
		if ( (sstatus = getservbyname(PortString, "tcp")) == NULL ) 
		{
			fprintf(stderr, "getservbyname: failed to find service \"%s\"\n", PortString);
		}
		else
		{
			fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(savError));
		}
		return(-1);
	}
	if ((sockListen = socket(servInfo->ai_family, servInfo->ai_socktype, servInfo->ai_protocol)) == -1 )
	{
		fprintf(stderr, "socket: %s\n", strerror(errno));
		return(-1);
	}
	if ((setsockopt(sockListen, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))) == -1)
	{
		fprintf(stderr, "setsockopt: %s\n", strerror(errno));
		return(-1);
	}
	if ((bind(sockListen, servInfo->ai_addr, servInfo->ai_addrlen)) == -1 )
	{
		close (sockListen);
		fprintf(stderr, "bind: %s\n", strerror(errno));
		return(-1);
	}
	if ((listen(sockListen, 20) == -1))
	{
		fprintf(stderr, "listen: %s\n", strerror(errno));
		return(-1);
	}
	
	DEBUG && fprintf(stdout, "Exiting setUpServSocket\n");

	return(sockListen);
}

int stripTrailingNewline(char * theString)
{
	size_t strPosition;
	int i;

	for (i = strlen(theString)-1; i >= 0; i-- )
	{
		if ( (theString[i] == '\n' ) || theString[i] == '\r' || theString[i] == '\f' )
		{
			theString[i] = '\0';
		}
		else
			break;
	}
	return(0);
}

void * logaroo (char *stringy)
{
	FILE * fp;
	char   timestring[256];
	time_t now;
	struct tm * timeinfo;

	time(&now);
	timeinfo = localtime(&now);
	strftime(timestring,sizeof(timestring), "%a %b %d %H:%M:%S",timeinfo);

	fp = fopen("program_log", "a");

	if ( fp == NULL)
		perror("program_log");

	if (fp) fprintf(fp, "%s: %s\n", timestring, stringy);

	fclose(fp);
}
