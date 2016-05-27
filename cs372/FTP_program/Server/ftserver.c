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

#define DEBUG 1
#define TEXT 0
#define BINARY 1
#define UNRECOGNIZED "Unrecognized command : "

void signalHandler (int param);
int listDirectory(int ssock);
int setUpServSocket(struct addrinfo *hints, char * PortString);
int stripTrailingNewline(char * theString);
char * shortToAscii( unsigned short num );

int main ( int argc, char ** argv )
{
	int Port; // we may not need this.
	int status;
	int sockListen, sockConnect;
	int clientDataSocket;
	int sockSendFlags = 0;
	int errcount = 0;
	ssize_t recv_bytes, send_bytes;

	struct addrinfo hints, *clientInfo;
	struct sockaddr_in client_info; // TODO: disambiguate the clientInfos
	socklen_t sin_size;

	size_t found;
	char tmpstr[2048];
	char * cstr;
	char * PortStr;
	char GetCmd[] = "GET ";
	char GetBinaryCmd[] = "GETBIN ";
	char HelloCmd[] = "HELO";
	char ListCmd[] = "LIST";
	char ChdirCmd[] = "CD ";
	char clientIP[255];
	char clientHandle[255];
	char clientHostname[255];
	unsigned short  clientDataPort;
	char * Hostname;
	char commandArg[1024];
	char recvData[1024];
	char sendData[1024];
	char errorString[1024];

	char officialClientHostname[NI_MAXHOST], clientService[NI_MAXSERV];
	int s;

	if ( argc < 2 ) {
		fprintf(stderr, "Usage : %s <portnumber>\n", argv[0]);
		exit(1);
	}
	Port = atoi ( argv[1] ); // we may not need this.
	PortStr = argv[1];
	gethostname(tmpstr, sizeof tmpstr - 1);
	Hostname = tmpstr;
	DEBUG && printf("hostname= %s\n", Hostname);
	
	// Create the socket
	memset (&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; //TODO; look this up

	sockListen = setUpServSocket(&hints,PortStr);
	
	fprintf(stdout, "FTP server listening on %s port %d\n", Hostname,Port);
  /* *************************************************** */

	while ( 1 )
	{
			fprintf(stdout, "Waiting for client to connect...\n");
			sin_size = sizeof(client_info);
			sockConnect = accept(sockListen, (struct sockaddr *) &client_info, &sin_size);
			if (sockConnect == -1)
			{
				fprintf(stderr, "accept: %s\n", strerror(errno));
				if ( errcount > 25 )
					exit(1);
				errcount++;
				continue;
			}
			// clientDataSocket = -1; // Fail if not initialized

			//inet_ntop(client_info.sin_family, &(client_info.sin_addr), clientIP, sizeof(clientIP));
			if (( getnameinfo((struct sockaddr *) &client_info, sizeof(struct sockaddr_in), 
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
			

			while ( 1 )
			{
				memset(recvData, 0, sizeof(recvData));
				recv_bytes = recv(sockConnect, &recvData, sizeof(recvData)-1,0);
				if (recv_bytes < 0 )
				{
					fprintf(stderr, "recv bytes: %s\n", gai_strerror(errno));
					close(sockConnect);
					break;
				}
				else if (recv_bytes == 0 )
				{
					fprintf(stderr, "recv bytes: %s\n", gai_strerror(errno));
					close(sockConnect);
					break;
				}
				// Test sockConnect here!!! TODO
				//if ( status = recv (sockConnect, &recvData, 1, MSG_PEEK) < 0 )
			  //	break;

				DEBUG && fprintf(stdout, "DBG received raw message |%s| from client\n", recvData);
				stripTrailingNewline(recvData);
				DEBUG && fprintf(stdout, "DBG received message |%s| from client\n", recvData);

 				// TODO: OMG, move this all into parse received buffer! 
				if ( (strncasecmp(recvData, HelloCmd, strlen(HelloCmd))) == 0 )
				{
					// get client information from HELO command
					// TODO: error checking
					// TODO: use a boolean to determin if HELO is done. If it isn't, default to sockConnect
					DEBUG && fprintf(stdout, "DBG received Hello |%s|\n", recvData);
					sscanf(recvData, "%*s %s %hu", clientHostname, &clientDataPort);
					DEBUG && fprintf(stdout, "Client hostname |%s| and data socket |%hu|\n", clientHostname, clientDataPort);

					if ( clientDataPort != 0 ) 
					{
						//if ( clientHostname == "" ) { clientHostname = clientIP };
						if ((status = getaddrinfo(clientHostname, shortToAscii(clientDataPort), &hints, &clientInfo)) != 0)
						{
							fprintf(stderr, "Unable to connect to client %s port %hu: %s\n",
								clientHostname, clientDataPort, strerror(errno));
							clientDataPort=0;
						}
						else
						{
							clientDataSocket = openClientDataSocket(clientInfo);
							if (clientDataSocket == 0 )
							{
								clientDataPort=0;
								clientDataSocket = sockConnect;
							}
						}
					}
					else
					{
						clientDataSocket = sockConnect;
					}
				}
				else if ( (strncasecmp(recvData, GetCmd,strlen(GetCmd))) == 0 )
				{
					DEBUG && fprintf(stdout, "DBG received Get args |%s|\n", recvData);
					strcpy(commandArg, (char * ) (recvData + strlen(GetCmd)));
					DEBUG && fprintf(stdout, "commandArg is |%s|\n", commandArg);
					transferFile(commandArg, clientDataSocket, TEXT);
				}
				else if ( (strncasecmp(recvData, GetBinaryCmd,strlen(GetBinaryCmd))) == 0 )
				{
					DEBUG && fprintf(stdout, "DBG received GetBinaryCmd args |%s|\n", recvData);
					strcpy(commandArg, (char * ) (recvData + strlen(GetBinaryCmd)));
					DEBUG && fprintf(stdout, "commandArg is |%s|\n", commandArg);
					transferFile(commandArg, clientDataSocket, BINARY);
				}
				else if ( (strncasecmp(recvData, ListCmd, strlen(ListCmd))) == 0 )
				{
					DEBUG && fprintf(stdout, "DBG received List |%s|\n", recvData);
					listDirectory(clientDataSocket);
				}
				else if ( (strncasecmp(recvData, ChdirCmd,strlen(ChdirCmd))) == 0 )
				{
					/* TODO chdir here */
					DEBUG && fprintf(stdout, "DBG received chdir command |%s|\n", recvData);
					strcpy(commandArg, (char * ) (recvData + strlen(ChdirCmd)));
					DEBUG && fprintf(stdout, "commandArg is |%s|\n", commandArg);

					if ( (status = chdir (commandArg)) < 0 )
					{
						// send the error to sockConnect
						DEBUG && fprintf (stderr, "Error: %s: %s\n", commandArg,strerror(errno));
						snprintf(errorString, sizeof(errorString)-1, "Error: %s: %s\n", commandArg, strerror(errno));
						send (clientDataSocket, errorString, strlen(errorString), sockSendFlags);
					}
					else
					{
						//open_socket << "Changed directory to " << commandArg << "\n";
						fprintf(stdout, "Client changed directory to %s\n", commandArg);
						snprintf(errorString, sizeof(errorString)-1, "Changed directory to %s\n", commandArg);
						send (clientDataSocket, errorString, strlen(errorString), sockSendFlags);
					}
				}
				else if ( (strncasecmp(recvData, ChdirCmd,strlen(ChdirCmd)-1)) == 0 || 
				          (strncasecmp(recvData, GetCmd,strlen(GetCmd)-1)) == 0)
				{
					// TODO: use errorstring
					fprintf (stderr, "%s: missing argument\n", recvData);
					send (sockConnect, recvData, strlen(recvData), sockSendFlags);
					send (sockConnect, ": missing argument\n", strlen(": missing argument\n"), sockSendFlags);
				}
				else 
				{
					// TODO: use errorstring
					fprintf (stderr, "%s%s\n", UNRECOGNIZED, recvData);
					send (sockConnect, UNRECOGNIZED, strlen(UNRECOGNIZED), sockSendFlags);
					send (sockConnect, recvData, strlen(recvData), sockSendFlags);
					send (sockConnect, "\n", 1, sockSendFlags);
					//open_socket << "Unrecognized Command " << recvData << "\n";
					//open_socket << "Available commands are: get, list, cd \n";
				}
				DEBUG && fprintf(stdout, "End of inner while\n");
				memset(errorString, 0, sizeof(errorString));
			} // inner while
			//close(sockConnect);
			DEBUG && fprintf(stdout, "End of outer while\n");
		} // outer while

	return 0;
}

int listDirectory(int ssock)
{
	DIR *dir;
	struct dirent *de;
	char cwdbuf[PATH_MAX];
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
		fprintf(stderr, "Can open directory %s: %s\n", cwdbuf, strerror(errno));
		// TODO: print to socket
		return(-1);
	}

	while ( (de = readdir(dir)) != NULL )
	{
		if ((strncmp(de->d_name, ".", 1)) != 0)
		{
			DEBUG && fprintf(stdout, "DBG: %s\n", de->d_name);
			send(ssock, de->d_name, strlen(de->d_name), sendFlags);
			send(ssock, "\n", 1, sendFlags);
		}
	}
	closedir(dir);
	DEBUG && fprintf(stdout, "DBG: end listDirectory\n");
}

int transferFile(char *filename, int csock, int binary)
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

	DEBUG && fprintf(stdout, "DBG: entering transferFile\n");
	if (( fp = fopen(filename, "r")) == NULL)
	{
		snprintf(errorString, sizeof(errorString)-1, "Error: %s: %s\n", filename, strerror(errno));
		send (csock, errorString, strlen(errorString), 0);
		fprintf(stderr, "%s\n", errorString);	
		return(-1);
	}

	if (binary)
	{
		DEBUG && fprintf(stdout, "DBG: beginning binary transfer of %s\n",filename);
		fd = fileno(fp);
		while (( (i = read(fd, buffer, 1023)) > 0 ) &&
			(send (csock, buffer, 1023, 0 )) == i)
		{
			byte_count += i;
		}
		DEBUG && fprintf(stdout, "DBG: sent %d bytes\n", byte_count);
		close(fd);
	}
	else
	{

		DEBUG && fprintf(stdout, "DBG: beginning text transfer of %s\n",filename);
		// TODO: get size of file in advance, send size of file to the client
		// count up to size of file rather than EOF
		// But EOF could still occur if the file is truncated while being read
		//memset (ubuffer, 0, sizeof(ubuffer));
		//while ( (i = read(fd, ubuffer, (unsigned int)1023)) > 0 
					//&& (send(csock,ubuffer, i, 0)) == i )
	
		memset (buffer, 0, sizeof(buffer));
		c = fgetc(fp);
		while (c != EOF )
		{
			buffer[i++] = c;
			if (i == 1023)
			{
				DEBUG && fprintf(stdout, "DBG: sent buffer %s\n", buffer);
				send (csock, buffer, strlen(buffer), 0);
				memset (buffer, 0, sizeof(buffer));
				i=0;
			}
			c = fgetc(fp);
		}
		if ( i > 0 )
		{
			DEBUG && fprintf(stdout, "DBG: sent buffer %s\n", buffer);
			send (csock, buffer, strlen(buffer), 0);
		}
	}
	DEBUG && fprintf(stdout, "DBG: exiting transferFile\n");
}

int setUpServSocket(struct addrinfo *hints, char * PortString)
{
	struct addrinfo *servInfo, *p;
	int status;
	int yes=1;
	int sockListen;
 
	DEBUG && fprintf(stdout, "Entering setUpServSocket\n");
	
 	
	if ( (status = getaddrinfo(NULL, PortString, hints, &servInfo)) !=0 ) 
	{
		fprintf(stderr, "getaddrinfo: %s\n", strerror(errno));
		return(1);
	}
	if ((sockListen = socket(servInfo->ai_family, servInfo->ai_socktype, servInfo->ai_protocol)) == -1 )
	{
		fprintf(stderr, "socket: %s\n", strerror(errno));
		return(1);
	}
	if ((setsockopt(sockListen, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))) == -1)
	{
		fprintf(stderr, "setsockopt: %s\n", strerror(errno));
		return(1);
	}
	if ((bind(sockListen, servInfo->ai_addr, servInfo->ai_addrlen)) == -1 )
	{
		close (sockListen);
		fprintf(stderr, "bind: %s\n", strerror(errno));
		return(1);
	}
	if ((listen(sockListen, 20) == -1))
	{
		fprintf(stderr, "listen: %s\n", strerror(errno));
		return(1);
	}
	
	DEBUG && fprintf(stdout, "Exiting setUpServSocket\n");

	return(sockListen);
}

int openClientDataSocket(struct addrinfo *clientInfo)
{
	int sockConnect;

	DEBUG && fprintf(stdout, "Entering openClientDataSocket\n");
	if ((sockConnect = socket(clientInfo->ai_family, clientInfo->ai_socktype, clientInfo->ai_protocol)) == -1 )
	{
		fprintf(stderr, "socket: %s\n", strerror(errno));
		return(0);
	}
	if ((connect(sockConnect, clientInfo->ai_addr, clientInfo->ai_addrlen)) == -1 )
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
