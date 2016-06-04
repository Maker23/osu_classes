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
	int c;
	int fd;

	memset(buffer,0, sizeof(buffer));
	fd = fileno(data);
	while ( ( i = read(fd, buffer, BUFSZ)) > 0 )
	{
		for (c=0; c<i; c++)
		{
			if ( strchr(KEYSET, buffer[c]) == NULL )
			{
				if ( c == (i-1) && buffer[c] == '\n' )
				{
					// ignore
				}
				else 
				{
					fprintf(stderr, "ERROR: text file contains bad characters at byte %d\n", bytecount + c);
					return(-1);
				}
			}
		}
		if (  send (CSock, buffer, strlen(buffer), 0) != i )
			perror("send");
		memset(buffer,0, sizeof(buffer));
		bytecount += i;
	}
	close(fd);
	strcpy(buffer, "\n");
	send(CSock, buffer, strlen(buffer), 0);
	return(bytecount);
}

int receiveFileInChunks (int CSock, FILE *output, int datalen)
{
	char buffer[BUFSZ+1]; // Because we print it as a string, it needs to be null-terminated
	int bytecount=0;
	int	recvcount=1;

	DEBUG && fprintf(stderr, "DBG: Expecting %d bytes\n", datalen);
	while (bytecount < datalen && recvcount != 0 )
	{
		//recvcount = recv(CSock, &buffer, BUFSZ, MSG_DONTWAIT);
		memset(buffer,0, sizeof(buffer));
		recvcount = recv(CSock, &buffer, BUFSZ, 0);
		bytecount+=recvcount;
		DEBUG && fprintf(stderr, "Library received a %d byte data chunk |%s|\n", recvcount,buffer);
		DEBUG && fprintf(stderr, "**** bytecount is %d, expecting %d\n", bytecount, datalen);
		fprintf(output, "%s", buffer);
	}

	DEBUG && fprintf(stderr, "Returning\n");
	return(bytecount);
}

int sendDataInChunks ( int CSock, char *data )
{
	char buffer[BUFSZ+1];
	int bytecount=0;
	int w = 0;
	int p,i,c;

	bytecount = strlen(data);

	while (data && bytecount > 0)
	{
		memset(buffer,0, sizeof(buffer));
		strncpy(buffer,data,BUFSZ);
		/*
		for (p=0; p<BUFSZ; p++)
		{
			i = p+w;
			if ( ! data[i] ) break;

			if ( strchr(KEYSET, data[i]) == NULL )
			{
				if ( i == strlen((char *) data+w) && data[i] == '\n' )
				{
					// ignore
				}
				else
				{
					fprintf(stderr, "ERROR: SEND DATA contains bad character %d at byte %d\n", data[i], i);
					continue;
					//return(-1);
				}
			}
			else
			{
				buffer[p] = data[i];
				bytecount++;
			}
		}
		*/
		DEBUG && fprintf(stderr, "Library sending data chunk |%s|\n", buffer);
		send(CSock, buffer, strlen(buffer), 0);
		//w += p;
		bytecount -= strlen(buffer);
		data += strlen(buffer);
	}
	//strcpy(buffer, "\n");
	//send(CSock, buffer, strlen(buffer), 0);
	return(bytecount);
}
