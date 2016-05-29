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
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define DEBUG 0
#define CHATTY 1

#define TEXT 0
#define BINARY 1
#define UNRECOGNIZED "Unrecognized command : "

struct Connection {
	char *Host_name;
	char *CPort_name;
	unsigned short DPort_num;
	int Control_sock; // File descriptor
	int Data_sock;		// File descriptor
	struct addrinfo *Hints;
};

void signalHandler (int param);
int listDirectory(struct Connection *clientConnect);
int setUpServSocket(struct addrinfo *hints, char * PortString);
int stripTrailingNewline(char * theString);
char * shortToAscii( unsigned short num );
int transferFile(struct Connection *clientConnect, char *filename, int binary);

int main ( int argc, char ** argv )
{
	int retval; // capture return values
	int errcount = 0; // So we can end gracefully if something goes wrong
	int ListenSocket, ControlSocket, DataSocket;
	ssize_t recv_bytes, send_bytes;

	struct addrinfo hints;
	struct sockaddr_in client_sockaddr;
	socklen_t sin_size;

	char * PortStr;
	char serverHostname[NI_MAXHOST];
	char clientIP[255];
	char clientHandle[255];
	char officialClientHostname[NI_MAXHOST]; 
	char clientService[NI_MAXSERV];
	char commandArg[1024];
	char recvData[1024];
	char sendData[1024];
	char errorString[1024];

	struct Connection clientConnect;

	if ( argc < 2 ) {
		// This is the only argument validation we do. 
		// If the argument isn't a valid port number or service name 
		// then setUpServSocket will fail
		fprintf(stderr, "Usage : %s <portnumber>\n", argv[0]);
		exit(1);
	}
	/* ***************************
	 * Create the listening socket
	 * **************************/
	memset (&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; //TODO; look this up

	PortStr = argv[1];
	if ( (ListenSocket = setUpServSocket(&hints,PortStr) ) < 0 )
	{
		exit(ListenSocket);
	}
	gethostname(serverHostname, sizeof (serverHostname) - 1);
	fprintf(stdout, "FTP server listening on %s port %s\n", serverHostname,PortStr);

	/* ********************************************************
	 * Loop indefinitely waiting for connect() on the listening
	 * socket. The only way to end is with a SIGINT or <ctrl>-c
	 * ********************************************************/
	while ( 1 )
	{
			fprintf(stdout, "Waiting for client to connect...\n");
			sin_size = sizeof(client_sockaddr);
			ControlSocket = accept(ListenSocket, (struct sockaddr *) &client_sockaddr, &sin_size);
			if (ControlSocket == -1)
			{
				fprintf(stderr, "accept: %s\n", strerror(errno));
				// Limit prevents an infinite while loop if something goes wrong
				if ( errcount > 25 ) 
					exit(1);
				errcount++;
				continue;
			}

			/* 
			 * Get information about the client so we can print a useful message 
			 */
			inet_ntop(client_sockaddr.sin_family, &(client_sockaddr.sin_addr), clientIP, sizeof(clientIP));
			if (( getnameinfo((struct sockaddr *) &client_sockaddr, sizeof(struct sockaddr_in), 
					officialClientHostname, NI_MAXHOST, clientService, NI_MAXSERV, NI_NUMERICSERV)) == 0)
			{
				char * cptr;
				if ( (cptr=strchr(officialClientHostname, '.')) != NULL )
					*cptr = '\0';
				fprintf (stdout, "Client connection from %s.\n", officialClientHostname);
			}
			else
			{
				fprintf (stdout, "Client connection from %s.\n", clientIP);
			}

			/* ********************************************************
			 * Store all settings in the clientConnect struct so we can
			 * pass them to subroutines. 
			 *
			 * The default value for Data_sock is Control_sock - that is,
			 * data will be sent over the control socket if the client 
			 * does not specify a separate data port.
			 * *******************************************************/
			clientConnect.Host_name = officialClientHostname;
			clientConnect.DPort_num = 0;
			clientConnect.CPort_name = PortStr;
			clientConnect.Control_sock = ControlSocket;
			clientConnect.Data_sock = ControlSocket;
			clientConnect.Hints = &hints;
			
			/* ********************************************************
	 		* Loop indefinitely on the client socket, collecting commands
	 		* and acting on them. This only exits when the client closes
			* the socket; code handles one client connection at a time
			* (no forked children or threads)
	 		* ********************************************************/
			while ( 1 )
			{
				/*
				 * Receive data from the socket, store it in a char array for
				 * processing.
				 */
				memset(recvData, 0, sizeof(recvData));
				recv_bytes = recv(clientConnect.Control_sock, &recvData, sizeof(recvData)-1,0);
				if (recv_bytes < 0 )
				{
					fprintf(stderr, "recv bytes: %s\n", gai_strerror(errno));
					close(clientConnect.Control_sock);
					close(clientConnect.Data_sock);
					break;
				}
				else if (recv_bytes == 0 )
				{
					DEBUG && fprintf(stderr, "recv bytes: %s\n", gai_strerror(errno));
					close(clientConnect.Control_sock);
					close(clientConnect.Data_sock);
					break;
				}
				DEBUG && fprintf(stdout, "DBG received raw message |%s| from client\n", recvData);

				/* *******************************************************
				 * Strip trailing newlines and CRs
				 * Send resulting string to subroutine for parsing and execution
				 * ******************************************************/
				stripTrailingNewline(recvData);
				DEBUG && fprintf(stdout, "DBG received message |%s| from client\n", recvData);
				retval = parseReceiveBuffer(&clientConnect, &recvData);
				if ( retval < 0 )
					break;

				DEBUG && fprintf(stdout, "End of inner while (receive data)\n");
				memset(errorString, 0, sizeof(errorString));
				fflush(stderr);
				fflush(stdout);
			}

			DEBUG && fprintf(stdout, "End of outer while (listen / accept)\n");
		}

	return 0;
}

/* *********************************************************
 * parseReceiveBuffer()
 *
 * All the work of parsing and executing client commands
 * happens here.
 *
 * Returns:
 * 0    complete success
 * >0   soft failure, continue executing
 * <0   hard fail, close the connection
 *
 * *********************************************************/
int parseReceiveBuffer(struct Connection* clientConnect, char * recvData, int *DataSocket)
{
	// Defined by the protocol
	char GetCmd[] = "GET ";
	char GetBinaryCmd[] = "GETBIN ";
	char HelloCmd[] = "HELO";
	char ListCmd[] = "LIST";
	char ChdirCmd[] = "CD ";

	int retval;
	char commandArg[1024];
	char errorString[1024];
	char clientHostname[NI_MAXHOST];
	unsigned short  clientDataPort = 0;
	struct addrinfo *client_addrinfo;
	int sockSendFlags = 0;

	DEBUG &&  fprintf(stderr, "DBG Entering parseReceiveBuffer\n");

	if ( (strncasecmp(recvData, HelloCmd, strlen(HelloCmd))) == 0 )
	{
		// get client information from HELO command
		// TODO: error checking
		DEBUG && fprintf(stdout, "DBG received Hello |%s|\n", recvData);
		sscanf(recvData, "%*s %s %hu", clientHostname, &clientDataPort);
		DEBUG && fprintf(stdout, "Client hostname |%s| and data socket |%hu|\n", clientHostname, clientDataPort);

		if ( clientDataPort != 0 ) 
		{
			if ((retval = getaddrinfo(clientHostname, shortToAscii(clientDataPort), clientConnect->Hints, &client_addrinfo)) != 0)
			{
				snprintf(errorString, sizeof(errorString)-1, "Unable to connect to client %s data port %hu: %s\n",
					clientHostname, clientDataPort, strerror(errno));
				fprintf(stderr, errorString);
				send (clientConnect->Control_sock, errorString, strlen(errorString), sockSendFlags);
				return(-1); // hard / fatal error
			}
			else
			{
				clientConnect->Data_sock = openClientDataSocket(client_addrinfo);
				if (clientConnect->Data_sock == 0 )
				{
					snprintf(errorString, sizeof(errorString)-1, "Unable to open client %s data port %hu: %s\n",
						clientHostname, clientDataPort, strerror(errno));
					fprintf(stderr, errorString);
					send (clientConnect->Control_sock, errorString, strlen(errorString), sockSendFlags);
					return(-1); // hard / fatal error
				}
				clientConnect->DPort_num = clientDataPort;
				CHATTY && fprintf(stdout, "\tClient data port = %hu\n",clientConnect->DPort_num);
			}
		}
		else
		{
			// If the client specifies '0', they want the Control Socket 
			// and the Data Socket to be the same.
			CHATTY && fprintf(stdout, "DataSock == ControlSock\n");
			clientConnect->Data_sock = clientConnect->Control_sock;
			return(0);
		}
	}
	else if ( (strncasecmp(recvData, GetCmd,strlen(GetCmd))) == 0 )
	{
		strcpy(commandArg, (char * ) (recvData + strlen(GetCmd)));
		DEBUG && fprintf(stdout, "DBG Get file |%s|\n", commandArg);
		CHATTY && fprintf(stdout, "\tFile \"%s\" requested on port %hu\n", 
			commandArg, clientConnect->DPort_num);
		retval = transferFile(clientConnect, commandArg, TEXT);
	}
	else if ( (strncasecmp(recvData, GetBinaryCmd,strlen(GetBinaryCmd))) == 0 )
	{
		strcpy(commandArg, (char * ) (recvData + strlen(GetBinaryCmd)));
		DEBUG && fprintf(stdout, "DBG Get binary file |%s|\n", commandArg);
		CHATTY && fprintf(stdout, "\tBinary file \"%s\" requested on port %hu\n", 
			commandArg, clientConnect->DPort_num);
		retval = transferFile(clientConnect, commandArg, BINARY);
	}
	else if ( (strncasecmp(recvData, ListCmd, strlen(ListCmd))) == 0 )
	{
		DEBUG && fprintf(stdout, "DBG List |%s|\n", recvData);
		CHATTY && fprintf(stdout, "\tList directory requested on port %hu\n", 
			clientConnect->DPort_num);
		retval = listDirectory(clientConnect);
		return(retval);
	}
	else if ( (strncasecmp(recvData, ChdirCmd,strlen(ChdirCmd))) == 0 )
	{
		strcpy(commandArg, (char * ) (recvData + strlen(ChdirCmd)));
		DEBUG && fprintf(stdout, "DGB chdir |%s|\n", commandArg);
		CHATTY && fprintf(stdout, "\tChange directory requested on port %hu\n", 	
			clientConnect->DPort_num);

		if ( (retval = chdir (commandArg)) < 0 )
		{
			DEBUG && fprintf (stderr, "Error: %s: %s\n", commandArg,strerror(errno));
			snprintf(errorString, sizeof(errorString)-1, "Error: %s: %s\n", commandArg, strerror(errno));
			send (clientConnect->Control_sock, errorString, strlen(errorString), sockSendFlags);
		}
		else
		{
			CHATTY && fprintf(stdout, "\tClient %s:%s changed directory to %hu\n", 
				clientConnect->Host_name, clientConnect->DPort_num, commandArg);
			snprintf(errorString, sizeof(errorString)-1, "Changed directory to %s\n", commandArg);
			send (clientConnect->Data_sock, errorString, strlen(errorString), sockSendFlags);
		}
		return(retval);
	}
	else if ( (strncasecmp(recvData, ChdirCmd,strlen(ChdirCmd)-1)) == 0 || 
	          (strncasecmp(recvData, GetCmd,strlen(GetCmd)-1)) == 0)
	{
		// TODO: use errorstring
		fprintf (stderr, "Error: %s: missing argument\n", recvData);
		send (clientConnect->Control_sock, recvData, strlen(recvData), sockSendFlags);
		send (clientConnect->Control_sock, ": missing argument\n", strlen(": missing argument\n"), sockSendFlags);
		return(1);
	}
	else 
	{
		// TODO: use errorstring
		fprintf (stderr, "%s%s\n", UNRECOGNIZED, recvData);
		send (clientConnect->Control_sock, UNRECOGNIZED, strlen(UNRECOGNIZED), sockSendFlags);
		send (clientConnect->Control_sock, recvData, strlen(recvData), sockSendFlags);
		send (clientConnect->Control_sock, "\n", 1, sockSendFlags);
		return(1);
	}
	DEBUG && 	fprintf(stderr, "Exiting parseReceiveBuffer\n");
}

int listDirectory(struct Connection *clientConnect)
{
	DIR *dir;
	struct dirent *de;
	char cwdbuf[PATH_MAX];
	char errorString[1024];
	char *cptr;
	char tmpstring[1024];
	int sendFlags = 0;

	cptr = getcwd(cwdbuf, sizeof(cwdbuf));
	if (cptr == NULL )
	{
		// this shouldn't really happen
	}
	else if ( (dir = opendir(cwdbuf)) == NULL )
	{
		snprintf(errorString, sizeof(errorString)-1, "Error: %s: %s\n", cwdbuf, strerror(errno));
		CHATTY && fprintf(stdout, "\t%s", errorString);
		CHATTY && fprintf(stdout, "\tSending error to %s:%s",
			clientConnect->Host_name, clientConnect->CPort_name);
		send (clientConnect->Control_sock, errorString, strlen(errorString), 0);
		send (clientConnect->Data_sock, "\0", 1, 0);
		// TODO: print to socket
		return(-1);
	}

	CHATTY && fprintf(stdout, "\tSending directory listing to %s:%hu\n",
		clientConnect->Host_name, clientConnect->DPort_num);
	while ( (de = readdir(dir)) != NULL )
	{
		if ((strncmp(de->d_name, ".", 1)) != 0)
		{
			DEBUG && fprintf(stderr, "DBG: %s\n", de->d_name);
			send(clientConnect->Data_sock, de->d_name, strlen(de->d_name), sendFlags);
			send(clientConnect->Data_sock, "\n", 1, sendFlags);
		}
	}
	closedir(dir);
	send (clientConnect->Control_sock, "\0", 1, 0);
	DEBUG && fprintf(stderr, "DBG: end listDirectory\n");
	return(0);
}

int transferFile(struct Connection *clientConnect, char *filename, int binary)
{
	char buffer[1024];
	unsigned int ubuffer[1024];
	char errorString[1024];
	int i = 0;
	int byte_count=0;
	FILE * fp;
	int fd;
	char c;

	/* TODO: Validate the file, open the file, send it to the DATA port */

	DEBUG && fprintf(stderr, "DBG: entering transferFile\n");
	if (( fp = fopen(filename, "r")) == NULL)
	{
		snprintf(errorString, sizeof(errorString)-1, "Error transferring file: %s: %s\n", filename, strerror(errno));
		CHATTY && fprintf(stderr, "\t%s", errorString);	
		CHATTY && fprintf(stdout, "\tSending error to %s:%s",
			clientConnect->Host_name, clientConnect->CPort_name);
		send (clientConnect->Control_sock, errorString, strlen(errorString), 0);
		send(clientConnect->Data_sock, "\0", 1, 0);
		return(-1);
	}

	if (binary)
	{
		DEBUG && fprintf(stderr, "DBG: beginning binary transfer of %s\n",filename);
		CHATTY && fprintf(stdout, "\tTransferring \"%s\" to %s:%hu\n", filename,
			clientConnect->Host_name, clientConnect->DPort_num);
		fd = fileno(fp);
		while (( (i = read(fd, buffer, 1023)) > 0 ) &&
			(send (clientConnect->Data_sock, buffer, 1023, 0 )) == i)
		{
			byte_count += i;
		}
		DEBUG && fprintf(stderr, "DBG: sent %d bytes\n", byte_count);
		close(fd);
	}
	else
	{

		DEBUG && fprintf(stdout, "DBG: beginning text transfer of %s\n",filename);
	
		memset (buffer, 0, sizeof(buffer));
		c = fgetc(fp);
		while (c != EOF )
		{
			buffer[i++] = c;
			if (i == 1023)
			{
				DEBUG && fprintf(stdout, "DBG: sent buffer %s\n", buffer);
				send (clientConnect->Data_sock, buffer, strlen(buffer), 0);
				memset (buffer, 0, sizeof(buffer));
				i=0;
			}
			c = fgetc(fp);
		}
		if ( i > 0 )
		{
			DEBUG && fprintf(stdout, "DBG: sent buffer %s\n", buffer);
			send (clientConnect->Data_sock, buffer, strlen(buffer), 0);
		}
	}
	send(clientConnect->Control_sock, "\0", 1, 0);
	DEBUG && fprintf(stdout, "DBG: exiting transferFile\n");
	return(0);
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

int openClientDataSocket(struct addrinfo *client_ai)
{
	int sockConnect;

	DEBUG && fprintf(stdout, "Entering openClientDataSocket\n");
	if ((sockConnect = socket(client_ai->ai_family, client_ai->ai_socktype, client_ai->ai_protocol)) == -1 )
	{
		fprintf(stderr, "socket: %s\n", strerror(errno));
		return(0);
	}
	if ((connect(sockConnect, client_ai->ai_addr, client_ai->ai_addrlen)) == -1 )
	{
		fprintf(stderr, "connect: %s\n", strerror(errno));
		return(0);
	}

	DEBUG && fprintf(stdout, "Exiting openClientDataSocket\n");
	return (sockConnect);
	
}


int stripTrailingNewline(char * theString)
{
	size_t strPosition;
	int i;

	for (i = 0; i < strlen(theString); i++ )
	{
		if ( (theString[i] == '\n' ) || theString[i] == '\r' || theString[i] == '\f' )
		{
			theString[i] = '\0';
			break;
		}
	}
	return(0);
}

char * shortToAscii( unsigned short num )
{
	char * numString;
	char revString[12];
	int remainder;
	int i=0;

	numString = malloc (sizeof (char) * 12);
	memset (numString, 0, sizeof(numString));
	memset (revString, 0, sizeof(revString));

	while ( num ) {
		remainder = num % 10;
		revString[i++] = (char) remainder+48;
		num = num / 10;
	}

	for (i=0; i< strlen(revString); i++ )
	{
		numString[i] = revString[strlen(revString)-(i+1)];
	}

	return(numString);
}
