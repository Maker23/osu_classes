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

#include "otp_proto.h"



int sendFileInChunks ( int CSock, FILE *data )
{
	char buffer[BUFSZ];
	int bytecount=0;
	int i = 0;
	int fd;

	fd = fileno(data);
	while (( ( i = read(fd, buffer, BUFSZ)) > 0 )
		&& ( send (CSock, buffer, strlen(buffer), 0) ) == i )
	{
		bytecount++;
	}
	close(fd);
	strcpy(buffer, "\n");
	send(CSock, buffer, strlen(buffer), 0);
	return(bytecount);
}

int receiveFileInChunks (int CSock, FILE *output, int datalen)
{
	char buffer[BUFSZ];
	int bytecount=0;
	int	recvcount;

	while (bytecount < datalen)
	{
		//recvcount = recv(CSock, &buffer, BUFSZ, MSG_DONTWAIT);
		recvcount = recv(CSock, &buffer, BUFSZ, 0);
		bytecount+=recvcount;
		fprintf(output, "%s", buffer);
	}
	
}

int sendDataInChunks ( int CSock, char *data )
{
	char buffer[BUFSZ];
	int bytecount=0;
	int i = 0;

	while (data[i])
	{
		memset(buffer,0, sizeof(buffer));
		for (i=0; i<BUFSZ; i++)
		{
			if ( ! data[i] ) break;

			buffer[i] = data[i];
			bytecount++;
		}
		send(CSock, buffer, strlen(buffer), 0);
	}
	strcpy(buffer, "\n");
	send(CSock, buffer, strlen(buffer), 0);
	return(bytecount);
}
