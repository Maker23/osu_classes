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
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define DEBUG 1

void signalHandler (int param);
int listDirectory(int ssock);
int stripTrailingNewline(char * theString);

int main ( int argc, char ** argv )
{
	int Port;
	int status;
	int sockListen, sockConnect;
	int yes=1;
	pid_t	child_pid;
	ssize_t recv_bytes, send_bytes;

	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_storage client_info;
	socklen_t sin_size;

	size_t found;
	char tmpstr[2048];
	char * cstr;
	char * PortStr;
	char Get[] = "get ";
	char List[] = "list";
	char Changedir[] = "cd ";
	char Domainname[] = ".engr.oregonstate.edu";
	char clientIP[255];
	char * Hostname;
	char commandArg[1024];
	char recvData[1024];
	char sendData[1024];

	if ( argc < 2 ) {
		fprintf(stderr, "Usage : %s <portnumber>\n", argv[0]);
		exit(1);
	}
	Port = atoi ( argv[1] );
	PortStr = argv[1];
	gethostname(tmpstr, sizeof tmpstr - 1);
	Hostname = tmpstr;
	DEBUG && printf("hostname= %s, domainname = %s\n", Hostname, Domainname);
	
	// Create the socket
	memset (&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; //TODO; look this up

	if ( (status = getaddrinfo(NULL, PortStr, &hints, &servinfo)) !=0 ) 
	{
		fprintf(stderr, "getaddrinfo: %s\n", strerror(errno));
		return(1);
	}
	if ((sockListen = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1 )
	{
		fprintf(stderr, "socket: %s\n", strerror(errno));
		return(1);
	}
	if ((setsockopt(sockListen, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))) == -1)
	{
		fprintf(stderr, "setsockopt: %s\n", strerror(errno));
		return(1);
	}
	if ((bind(sockListen, servinfo->ai_addr, servinfo->ai_addrlen)) == -1 )
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
	
	fprintf(stdout, "FTP server listening on %s port %d\n", Hostname,Port);

	while ( 1 )
	{
			fprintf(stdout, "Waiting for client to connect...\n");
			sin_size = sizeof(client_info);
			sockConnect = accept(sockListen, (struct sockaddr *) &client_info, &sin_size);
			if (sockConnect == -1)
			{
				fprintf(stderr, "accept: %s\n", strerror(errno));
				continue;
			}

			//inet_ntop(client_info.ss_family, get_in_addr((struct sockaddr *) &client_info), clientIP, sizeof(clientIP));
			//fprintf (stdout, "Client has connected from %s.\n", clientIP);

			/* Fork here */
			/*
			if ( (child_pid =  fork() ) == 0 )
			// Child
			*/
			while ( 1 )
			{
				memset(recvData, 0, sizeof(recvData));
				recv_bytes = recv(sockConnect, &recvData, sizeof(recvData)-1,0);
				if (recv_bytes < 0 )
				{
					fprintf(stderr, "accept: %s\n", strerror(errno));
					close(sockConnect);
					break;
				}
				else if (recv_bytes == 0 )
				{
					fprintf(stderr, "accept: %s\n", strerror(errno));
					close(sockConnect);
					break;
				}
				// Test sockConnect here!!! TODO
				//if ( status = recv (sockConnect, &recvData, 1, MSG_PEEK) < 0 )
			  //	break;

				DEBUG && fprintf(stdout, "DBG received raw message |%s| from client\n", recvData);

				cstr = (char *) malloc (sizeof( char ) * (strlen(recvData)+1));
				strcpy(cstr, recvData);
				DEBUG && fprintf(stdout, "DBG received control message |%s| from client\n", recvData);
						if ( (strncmp(cstr, Get,strlen(Get))) == 0 )
						{
							DEBUG && fprintf(stdout, "DBG received Get args |%s|\n", recvData);
							strcpy(commandArg, (char * ) (recvData + strlen(Get)));
							DEBUG && fprintf(stdout, "commandArg is |%s|\n", commandArg);
							stripTrailingNewline(commandArg);
							DEBUG && fprintf(stdout, "commandArg is |%s|\n", commandArg);
							/* TODO: Validate the file, Open a data socket, open the file, send it to the DATA port
							 */
						}
						else if ( (strncmp(cstr, Changedir,strlen(Changedir))) == 0 )
						{
							/* TODO chdir here */
							DEBUG && fprintf(stdout, "DBG received chdir command |%s|\n", recvData);
							strcpy(commandArg, (char * ) (recvData + strlen(Changedir)));
							stripTrailingNewline(commandArg);
							DEBUG && fprintf(stdout, "commandArg is |%s|\n", commandArg);

							if ( (status = chdir (commandArg)) < 0 )
							{
								// send the error to sockConnect
								DEBUG && fprintf (stderr, "Error: %s: %s\n", commandArg,strerror(errno));
							}
							else
							{
								//open_socket << "Changed directory to " << commandArg << "\n";
								fprintf(stdout, "Client changed directory to %s\n", commandArg);
							}
						}
						else 
						{
							;
							//open_socket << "Unrecognized Command " << recvData << "\n";
							//open_socket << "Available commands are: get, list, cd \n";
						}
						DEBUG && fprintf(stdout, "End of inner while\n");
						free (cstr);
			} // while
			close(sockConnect);
			DEBUG && fprintf(stdout, "End of outer while\n");
		} // outer while

	return 0;
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
