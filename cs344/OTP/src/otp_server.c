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
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>

#ifndef FUNCTION
#define FUNCTION ENCODE
#endif

#define MATHDEBUG 0

#ifndef TERMOUTPUT
#define	TERMOUTPUT 1	 // if 0, failures will not print to the terminal, but will be logged
#endif

#include "otp_proto.h"

enum States {
	looking_for_command,
	receiving_key,
	receiving_file,
	sending_file,
	function_query,
	closing,
};

struct Connection {
	int 	CSock; 				// File descriptor
	enum 	States State;	// state diagram
	char *Host_name;		// remote hostname
	char *CPort_name;		// local port name or number
	char *dataBuf;
	char *Key;
	char *Text;
	int	  keylength;
	int	  textlength;
	int  	expectMoreData;
};

void signalHandler (int param);
int setUpListeningSocket(struct addrinfo *hints, char * PortString);
int stripTrailingNewline(char * theString);
void * logaroo (char *stringy);
char * growstring (char *string, int newlength);
char * encrypt(char * key, char * file);
char * decrypt(char * key, char * cryptofile);
int ModuloAdd (int f, int k);
int ModuloSub (int f, int k);
int sendDataInChunks ( int CSock, char * data );
int isWhitespace(char theChar);

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
		// then setUpListeningSocket will fail
		fprintf(stderr, "Usage : %s <portnumber>\n", argv[0]);
		exit(1);
	}

	// TODO: set stdout to logfile ?
	freopen("/dev/null", "r", stdin);
	freopen("/dev/null", "w", stdout);
	memset (&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; //TODO; look this up

	/* ***************************
	 * Create the listening socket
	 * **************************/
	PortStr = argv[1];
	if ( (ServerListenSocket = setUpListeningSocket(&hints,PortStr) ) < 0 )
	{
		exit(ServerListenSocket);
	}
	ChildPortNum = (unsigned short) atoi(PortStr);
	gethostname(serverHostname, sizeof (serverHostname) - 1);
	sprintf(logString, "Server listening on %s port %s", serverHostname, PortStr);
	logaroo(logString);


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
			/* *****************************************************
			 * Client has connected; now look for a new port the server
			 * can open for the use of this client.
			 * *****************************************************/
			sprintf(ChildPortStr, "%hu", ChildPortNum);
			while ( (ChildListenSocket = setUpListeningSocket(&hints,ChildPortStr) ) < 0 )
			{
				sprintf(logString, "ChildListenSocket: %s: %s\n", ChildPortStr,strerror(errno));
				logaroo(logString);
				if (DEBUG) perror("ChildListenSocket");

				ChildPortNum++; // Try again until we find a free port

				if ( ChildPortNum > 65500 )
					exit(1); // TODO: Log and warn and stuff
				
				sprintf(ChildPortStr, "%hu", ChildPortNum);
			}
			// Get information about the client so we can print a useful log message 
			// Use the name of the client if we can get it - otherwise the IP address
			inet_ntop(client_sockaddr.sin_family, &(client_sockaddr.sin_addr), clientIP, sizeof(clientIP));
			if (( getnameinfo((struct sockaddr *) &client_sockaddr, sizeof(struct sockaddr_in), 
					officialClientHostname, NI_MAXHOST, clientService, NI_MAXSERV, NI_NUMERICSERV)) == 0)
			{
				char * cptr;
				if ( (cptr=strchr(officialClientHostname, '.')) != NULL )
					*cptr = '\0';
				sprintf (logString, "Client connection from %s, assigned to port %hu", 
					officialClientHostname, ChildPortNum);
			}
			else
			{
				sprintf (logString, "Client connection from %s assigned port %hu", 
					clientIP, ChildPortNum);
			}
			logaroo(logString);

			/* *****************************************************
			 * Now we have a NEW listening port. Send a Reconnect 
			 * command to the client so it knows which port to use. 
			 * Close the original client socket. 
			 *
			 * Fork here; child handles the new listening socket,
			 * parent does not wait but goes immediately back to
			 * listening on the original port #
			 * *****************************************************/
			if (DEBUG) fprintf(stderr, "Client will reconnect on port %s (%d)\n", ChildPortStr, ChildPortNum);
			snprintf(sendData, BUFSZ, "%s %s\n", RECONNECT_CMD, ChildPortStr);
			send(ServerDataSocket, sendData, strlen(sendData), 0);

			pid = fork();
			if ( pid < 0 )
			{
				// FATAL ERROR oh noes what to do
				exit(1);
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
				clientConnect.keylength = 0;
				clientConnect.textlength = 0;

				/* ******************************************************
				 * The handleConnection function does all the work :)
				 * *****************************************************/
				exit ( handleConnection(&clientConnect));
			}
			else
			{
				// Parent process; close sockets, go back to listening
				close(ChildListenSocket);
				close(ServerDataSocket);
			}
			DEBUG && fprintf(stderr, "End of outer while (listen / accept)\n");
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

	char *key = NULL;
	char *file = NULL;
	char *munged_file = NULL;

	/* *******************************************************
	* Loop indefinitely on the client socket, collecting commands
	* and acting on them. This exits when the client closes the socket.
	* ********************************************************/
	while ( 1 )
	{
		/* *****************************************************
		 * Receive data from the socket, store it in a char array for
		 * processing. 
		 * *****************************************************/
		memset(recvData, 0, sizeof(recvData));
		memset (clientConnect->dataBuf, 0, BUFSZ);
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

		/* *****************************************************
		 * Strip trailing newlines and CRs
		 * Send resulting string to subroutine for parsing and execution
		 * *****************************************************/
		stripTrailingNewline(recvData);
		DEBUG && fprintf(stderr, "DBG received message |%s| from client\n", recvData);

		retval = parseReceiveBuffer(clientConnect, &recvData, strlen(recvData));
		if ( retval < 0 )
		{
			// Fatal error; disconnect.
			// The reason for the error should be logged by the subroutine
			close(clientConnect->CSock);
			return(retval);
		}
		if ( retval > 0 )
		{
			// Non-fatal error: send an error to the client
			snprintf(sendData, BUFSZ, "%s %s\n", BAD_RESPONSE, clientConnect->CPort_name);
			send(clientConnect->CSock, sendData, strlen(sendData), 0);
		}
		else
		{
			if ( clientConnect->State == closing )
			{
				DEBUG && fprintf(stderr, "CLOSE command issued\n");
				close(clientConnect->CSock);
				return(0);
			}

			if ( clientConnect->State == function_query )
			{
				DEBUG && fprintf(stderr, "Function query received, sending %d\n", FUNCTION);
				snprintf(sendData, BUFSZ, "%s %d\n", FUNCTION_CMD, FUNCTION);
				send(clientConnect->CSock, sendData, strlen(sendData), 0);
			}

			if ( clientConnect->expectMoreData == 0)
			{
				if ( clientConnect->Key != NULL && clientConnect->Text != NULL ) 
				{
					/* ****************************************************
					 * We have a key, and a file, and we're not expecting
					 * any more data.  ENCRYPT or DECRYPT NOW!!
					 * ****************************************************/
					DEBUG && fprintf(stderr, "WHOOP! I'm ready to en/de-crypt file \n");
					DEBUG && fprintf(stderr, "========= \"%s\" with key \n========= \"%s\"\n",
						clientConnect->Text, clientConnect->Key);
					if ( FUNCTION == DECODE ) {
						munged_file = decrypt(clientConnect->Key, clientConnect->Text);
					}
					else {
						// Encoding is the default
						munged_file = encrypt(clientConnect->Key, clientConnect->Text);
					}
					DEBUG && fprintf(stderr, "YAHOO sending munged file:\n%s\n", munged_file);

					// Commenting this out for now, client doesn't need it
					// But it would be nice to have a full handshake protocol :)
					// snprintf(sendData, BUFSZ, "%s %d\n", DATA_RESPONSE, strlen(clientConnect->Text));
					//send(clientConnect->CSock, sendData, strlen(sendData), 0);

					sendDataInChunks(clientConnect->CSock, munged_file);

					// We can re-use the key, but not the text
					free(clientConnect->Text);
				}
				else
				{
					// Sigh, commenting this out for now. Assignment doesn't need it.
					//snprintf(sendData, BUFSZ, "%s %s\n", OK_RESPONSE, clientConnect->CPort_name);
					//send(clientConnect->CSock, sendData, strlen(sendData), 0);
				}
			}
		}
		DEBUG && fprintf(stderr, "End of inner while (receive data)\n");
		fflush(stderr);
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
	char logString[8192];
	int dataLength=0;
	int bufLength=0;
	int scancount=0,ccount;
	int state;
 	char command[4];
	int remainingBytes=recvBytes;
	int l=1;
	int storlen = 4096;

	char *key = NULL;
	char *file = NULL;
	char *munged_file = NULL;

	// Defined by the protocol
	char KeyCmd[] = KEY_CMD;
	char FileCmd[] = FILE_CMD;
	char CloseCmd[] = CLOSE_CMD;


	DEBUG &&  fprintf(stderr, "DBG Entering parseReceiveBuffer\n");
	DEBUG && fprintf(stderr, "DBG received on socket |%s|, recvBytes=%d\n", recvData, recvBytes);

	/* **********************************************************
	 * Loop through the buffer that was passed to this function
	 * until it's NULL or has no bytes left to consume
	 * **********************************************************/
	while ( *recvData && (remainingBytes > 0) )
	{
		DEBUG && fprintf(stderr, "DBG loop %d with data |%s|\n", l++, recvData);
		memset (clientConnect->dataBuf, 0, BUFSZ);

		if ( clientConnect->expectMoreData > 0 )
		{
			/* ******************************************************* 
	 		* State: Adding more bytes to Key or Text
	 		* 
			* Consume up to the amount of data we're expecting, 
			* or until the end of recvData
			* ********************************************************/
			DEBUG && fprintf(stderr, "Getting more data: start: %d (state=%d)\n", 
				clientConnect->expectMoreData, clientConnect->State);

			ccount=0;
			while ( ccount < remainingBytes && ccount < clientConnect->expectMoreData)
			{
				if (ccount > BUFSZ) 
				{
					DEBUG && fprintf (stderr, "Exceeded buffer size of %d bytes\n", BUFSZ);
					break;
				}
				clientConnect->dataBuf[ccount] = recvData[ccount];
				ccount++;
			}
			recvData += ccount;
			remainingBytes -= ccount;
			if ( strlen(clientConnect->dataBuf) >= clientConnect->expectMoreData )
			{
				clientConnect->expectMoreData = 0;
				//clientConnect->State = looking_for_command; // not realy using this
			}
			else
			{
				clientConnect->expectMoreData -= strlen(clientConnect->dataBuf);
			}
			if ( DEBUG )
			{
				fprintf(stderr, "Getting more data:   end: %d (state=%d)\n", 
					clientConnect->expectMoreData, clientConnect->State);
				fprintf(stderr, "Consumed data string is |%s|\n", clientConnect->dataBuf);
				fprintf(stderr, "Remaining string is |%s|\n", recvData);
				sprintf(logString, "%s:%s Received %d additional bytes", 
					clientConnect->Host_name, clientConnect->CPort_name, 
					strlen(clientConnect->dataBuf));
				logaroo(logString);
			}
		}
		else
		{
			/* ******************************************************* 
			 * State: Looking for something other than data bytes - should
			 *        be a protocol command (KEY, FIL, etc)
			 * ******************************************************* */
			// First consume leading whitespace.
			while ( isWhitespace( recvData[0]))
			{
				recvData++;
				remainingBytes--;
				continue;
			}

			// Sadly, the length of commands (3 chars) is hardcoded here
			memset (command, 0, sizeof(command));
			sscanf(recvData, "%3s", command);

			if ((strcmp(command,"") == 0) || ( remainingBytes < 3 )) {

				sprintf(logString, "%s:%s Unrecognized command |%s|", 
					clientConnect->Host_name, clientConnect->CPort_name,command);
				logaroo(logString);
				return(1);
			}

			/* ******************************************************* 
			 * FUNCTION command
			 * ******************************************************* */
			if ( (strncasecmp(command, FUNCTION_CMD, strlen(FUNCTION_CMD))) == 0 )
			{
				clientConnect->State=function_query;
				return(0);
			}

			/* ******************************************************* 
			 * CLOSE command
			 * ******************************************************* */
			if ( (strncasecmp(command, CloseCmd, strlen(CloseCmd))) == 0 )
			{
				sprintf(logString, "%s:%s Closing connection", 
					clientConnect->Host_name, clientConnect->CPort_name);
				logaroo(logString);
				clientConnect->State=closing;
				return(0);
			}
			/* ******************************************************* 
			 * KEY or FIL command
			 * ******************************************************* */
			else if ( (strncasecmp(command, KeyCmd,  strlen(KeyCmd)))  == 0 
							||(strncasecmp(command, FileCmd, strlen(FileCmd))) == 0 )
			{
				sscanf(recvData, "%*3s%*[ ]%d%n", &dataLength, &scancount); // TODO: check for errors
				scancount++;
				DEBUG && fprintf(stderr, "DBG remainingBytes = %d, dataLength = %d, scancount = %d\n", 
					remainingBytes, dataLength, scancount);
				DEBUG && fprintf(stderr, "DEBUG HERE while loop recvData=|%s|\n", recvData);

				if ( dataLength == 0 )
				{
					// This is a soft error, we need a dataLength
					DEBUG && fprintf(stderr, "Inexplicably returning\n");
					return(1);
				}

				//for (ccount = scancount; ccount < remainingBytes; ccount++)
				ccount=0;
				recvData += scancount;
				remainingBytes -= scancount;
				DEBUG && fprintf(stderr, "Starting while loop recvData=|%s|\n", recvData);
				while ( ccount < remainingBytes && ccount < dataLength )
				{
					clientConnect->dataBuf[ccount] = recvData[ccount];
					ccount++;
				}
				recvData += ccount;
				remainingBytes -= ccount;
				DEBUG && fprintf(stderr, "DBG length = %d, data = |%s|\n", 
					dataLength, clientConnect->dataBuf);
				DEBUG && fprintf(stderr, "DBG got %d bytes\n", 
					strlen(clientConnect->dataBuf));
				DEBUG && fprintf(stderr, "DBG remaining recvData is |%s| (%p) %d bytes remaining\n", 
					recvData,*recvData,remainingBytes);

				if ( strlen(clientConnect->dataBuf) < dataLength )
				{
					// More data is coming
					clientConnect->expectMoreData = dataLength - strlen(clientConnect->dataBuf);
				}
				if ( (strncasecmp(command, KeyCmd,  strlen(KeyCmd)))  == 0 )
				{
					sprintf(logString, "%s:%s Receiving %d byte key", 
						clientConnect->Host_name, clientConnect->CPort_name, dataLength);
					logaroo(logString);
					clientConnect->State=receiving_key;
				}
				else		
				{
					sprintf(logString, "%s:%s Receiving %d byte file", 
						clientConnect->Host_name, clientConnect->CPort_name, dataLength);
					logaroo(logString);
					clientConnect->State=receiving_file;
				}
				sprintf(logString, "%s:%s Received %d bytes", 
					clientConnect->Host_name, clientConnect->CPort_name, strlen(clientConnect->dataBuf));
				logaroo(logString);
			}
			else
			{
				clientConnect->State=looking_for_command;
				sprintf(logString, "%s:%s Unrecognized command |%s|", 
					clientConnect->Host_name, clientConnect->CPort_name, command);
				logaroo(logString);
				recvData=NULL;
				return(1); // TODO: should this be fatal?
			}
		}
		/* ******************************************************* 
		 * Save the data by appending it to key or file 
		 * in the Connection struct
		 * *******************************************************/
		if ( clientConnect->State == receiving_key )
		{
			// Append buffer to key
			if (clientConnect->Key==NULL) {
				clientConnect->Key  = (char *) malloc (storlen * sizeof(char));
				memset(clientConnect->Key, 0, storlen * sizeof(char));
				clientConnect->keylength  = storlen;
			}
			if ( (strlen(clientConnect->Key) + strlen(clientConnect->dataBuf)) >= clientConnect->keylength ) {
				clientConnect->keylength *= 2;
				clientConnect->Key = growstring(clientConnect->Key, clientConnect->keylength);
			}
			sprintf(logString, "%s:%s Received %d key bytes", 
				clientConnect->Host_name, clientConnect->CPort_name, strlen(clientConnect->dataBuf));
			logaroo(logString);
			strcat(clientConnect->Key,clientConnect->dataBuf);
			DEBUG && fprintf(stderr, "DBG key is now = %s\n", clientConnect->Key);
		}
		else if ( clientConnect->State == receiving_file )
		{
			// Append buffer to file
			if (clientConnect->Text == NULL)
			{
				clientConnect->Text = (char *) malloc (storlen * sizeof(char));
				memset(clientConnect->Text, 0, storlen * sizeof(char));
				clientConnect->textlength  = storlen;
			}
			if ( (strlen(clientConnect->Text) + strlen(clientConnect->dataBuf)) >= clientConnect->textlength ) {
				clientConnect->textlength *= 2;
				clientConnect->Text = growstring(clientConnect->Text, clientConnect->textlength);
			}
			sprintf(logString, "%s:%s Received %d text bytes", 
				clientConnect->Host_name, clientConnect->CPort_name, strlen(clientConnect->dataBuf));
			logaroo(logString);
			strcat(clientConnect->Text,clientConnect->dataBuf);
			DEBUG && fprintf(stderr, "DBG text is now = %s\n", clientConnect->Text);
		}
	}

	DEBUG && 	fprintf(stderr, "Exiting parseReceiveBuffer\n");
	return(0);
}

int setUpListeningSocket(struct addrinfo *hints, char * PortString)
{
	struct addrinfo *servInfo, *p;
	int savError;
	int status;
	int yes=1;
	int sockListen;
	char logString[8192];
	struct servent * sstatus;
 
	DEBUG && fprintf(stderr, "Entering setUpListeningSocket\n");
	
	// For the purposes of the assignment all error output in this function
	// goes to the logs, not to the terminal
 	
	if ( (status = getaddrinfo(NULL, PortString, hints, &servInfo)) !=0 ) 
	{
		savError = errno;
		if ( (sstatus = getservbyname(PortString, "tcp")) == NULL ) 
		{
			snprintf(logString, sizeof(logString), "getservbyname: failed to find service \"%s\"", PortString);
			logaroo(logString);
			TERMOUTPUT && fprintf(stderr, "%s\n", logString);
		}
		else
		{
			snprintf(logString, sizeof(logString),  "getaddrinfo: %s", gai_strerror(savError));
			logaroo(logString);
			TERMOUTPUT && fprintf(stderr, "%s\n", logString);
		}
		return(-1);
	}
	if ((sockListen = socket(servInfo->ai_family, servInfo->ai_socktype, servInfo->ai_protocol)) == -1 )
	{
		snprintf(logString, sizeof(logString), "socket: %s", strerror(errno));
		logaroo(logString);
		TERMOUTPUT && fprintf(stderr, "%s\n", logString);
		return(-1);
	}
	if ((setsockopt(sockListen, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))) == -1)
	{
		snprintf(logString, sizeof(logString),  "setsockopt: %s", strerror(errno));
		logaroo(logString);
		TERMOUTPUT && fprintf(stderr, "%s\n", logString);
		return(-1);
	}
	if ((bind(sockListen, servInfo->ai_addr, servInfo->ai_addrlen)) == -1 )
	{
		close (sockListen);
		snprintf(logString, sizeof(logString),  "bind: %s", strerror(errno));
		logaroo(logString);
		TERMOUTPUT && fprintf(stderr, "%s\n", logString);
		return(-1);
	}
	if ((listen(sockListen, 20) == -1))
	{
		snprintf(logString, sizeof(logString),  "listen: %s\n", strerror(errno));
		logaroo(logString);
		TERMOUTPUT && fprintf(stderr, "%s\n", logString);
		return(-1);
	}
	
	DEBUG && fprintf(stderr, "Exiting setUpListeningSocket\n");

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

int isWhitespace(char theChar)
{
/*	if ( (theChar == ' ')
		 ||(theChar == '\n')
		 ||(theChar == '\r')
		 ||(theChar == '\f')
		 ||(theChar == '\t'))
*/

  // Actually... just remove invalid characters
	if ( (int)theChar <= 32 || (int)theChar > 126)
	{
		DEBUG && fprintf(stderr, "Removed whitespace '%d'\n", (int) theChar);
		return (1);
	}

	DEBUG && fprintf(stderr, "No whitespace found\n");
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

	fp = fopen(LOGFILE, "a");

	if ( fp == NULL)
	{
		perror(LOGFILE);
		fp = stderr;
	}

	if (fp) 		fprintf(fp, "%s: %s\n", timestring, stringy);
	if (DEBUG || LOGTOSCREEN) 	fprintf(stderr, "LOG: %s\n", stringy);

	fclose(fp);
}

char * growstring (char *string, int newlength)
{
	char * newstring;
	char logString[8192];

	DEBUG && fprintf (stderr, "Growing string to %d\n", newlength);
	sprintf(logString, "Growing string to %d", newlength);
	logaroo(logString);

	newstring = (char *) malloc (newlength * sizeof(char));
	if (newstring == NULL)
	{
		fprintf(stderr, "HALP! FATAIL ERRORRS! MALLOC NO GOOD \n");
		exit(1);
	}
	memset(newstring, 0, newlength * sizeof(char));
	strncpy (newstring,string,newlength-1);
	free(string);
	return(newstring);
}

char * encrypt(char * key, char * file)
{
	char F,K,N;
	int f,k,n,x;

	int i;

	int *keynum = malloc (sizeof(int) * strlen(key));
	char * newfile = malloc(sizeof(char) * strlen(file));
	if (keynum == NULL || newfile == NULL)
	{
		fprintf(stderr, "HALP! FATAL ERROrz! MALLOC KEYNUM OR NEWFILE\n");
		exit(1);
	}

	memset(keynum, 0, strlen(key) * sizeof(int));
	memset(newfile, 0, strlen(file) * sizeof(char));

  for ( i=0; i< strlen(key); i++ )
	{
		K = toupper(key[i]);

		if ( K == ' ') k = 26;
		else k = (int) K - 65;

		keynum[i] = k;

	}
	
  for ( i=0; i< strlen(file); i++ )
	{
		F = toupper(file[i]);
		if ( F == ' ')  f = 26;
		else f = (int) F - 65;

		x = ModuloAdd(f,keynum[i]);
		if(DEBUG) printf("%c+%c = %d + %d = %d\n", F, K, f, keynum[i], x);

		if ( x==26)
			newfile[i] = ' ';
	  else if ( x < 0 || x > 26 )
		{
			DEBUG && fprintf (stderr, "DBG this should never happen\n");
		}
	  else
			newfile[i] = (char)(x+65);
	}
	newfile[i] = '\0'; // rlly?

	DEBUG && fprintf(stderr,"DBG encrypted %d bytes\n", i-1);

	free(keynum);
	return(newfile);
}


char * decrypt(char * key, char * file)
{
	char F,K,N;
	int f,k,n,x;

	int i;

	int *keynum = malloc (sizeof(int) * strlen(key));
	char * decrypt = malloc(sizeof(char) * strlen(file));
	memset(keynum, 0, sizeof(int) * strlen(key));
	memset(decrypt, 0, sizeof(char) * strlen(file));

  for ( i=0; i< strlen(key); i++ )
	{
		K = toupper(key[i]);

		if ( K == ' ') k = 26;
		else k = (int) K - 65;

		keynum[i] = k;

	}

  for ( i=0; i< strlen(file); i++ )
	{
		N = toupper(file[i]);
		if ( N == ' ')  n = 26;
		else n = (int) N - 65;

		x = ModuloSub(n,keynum[i]);
		if(MATHDEBUG) printf("%c+%c = %d + %d = %d\n", F, K, f, keynum[i], x);
		if ( x==26)
			decrypt[i] = ' ';
	  else if ( x < 0 || x > 26 )
		{
			DEBUG && fprintf (stderr, "DBG this should never happen either\n");
		}
	  else
			decrypt[i] = (char)(x+65);
	}
	decrypt[i] = '\0'; // rlly? No, this is redundant.

	return(decrypt);
}

int ModuloAdd (int f, int k)
{
	int tmp;
	tmp = f + k;
	MATHDEBUG && fprintf (stderr, "MDBG f+k = t  %d + %d = %d, ", f, k, tmp);
	if (tmp >= KEYSETLEN )
		tmp-=KEYSETLEN;
	MATHDEBUG && fprintf (stderr, " mod= %d\n", tmp);
	return(tmp);
}

int ModuloSub (int f, int k)
{
	int tmp;
	tmp = f - k;
	MATHDEBUG && fprintf (stderr, "MDBG f-k = t  %d - %d = %d, ", f, k, tmp);
	if (tmp < 0 )
		tmp+=KEYSETLEN;
	MATHDEBUG && fprintf (stderr, " mod= %d\n", tmp);
	return(tmp);
}

/*
 * TODO:
 *  If key or file are longer than expected, warn, truncate, and continue
 * 	Timeout child listener if no one connects SIGALRM
 *
 *
 *
 *
 */
