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
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "otp_proto.h"

#ifndef DEBUG
#define DEBUG 0
#endif

char * encrypt(char * key, char * file);
char * decrypt(char * key, char * cryptofile);

main (int arc, char **argv)
{
	char * clear;
	char * crypto;
	char * key =  "ERIYZFYLJQSNKCFSZZTUAVIHTVXL PQDFNQUTCEBSLOCNIJAGRJWASCUBOUADJUIWZBOBVPIFS";
	char * file = "this is the text AND MORE text is now the thing tag is a sleepy cat very v";

	crypto = encrypt (key, file);
	clear = decrypt (key, crypto);
	printf("%s\n", file);
	printf("%s\n", crypto);
	printf("%s\n", clear);
}

char * encrypt(char * key, char * file)
{
	char F,K,N;
	int f,k,n,x;

	int i;

	int *keynum = malloc(sizeof(int) * strlen(key));
	char * newfile = malloc(sizeof(char) * strlen(file));
	memset(newfile, 0, sizeof(newfile));

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
	  else
			newfile[i] = (char)(x+65);
	}

	return(newfile);
}

char * decrypt(char * key, char * file)
{
	char F,K,N;
	int f,k,n,x;

	int i;

	int keynum[75];
	char *decrypt = malloc (75 * sizeof(char));
	memset(decrypt, 0, sizeof(decrypt));

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
		if(DEBUG) printf("%c+%c = %d + %d = %d\n", F, K, f, keynum[i], x);
		if ( x==26)
			decrypt[i] = ' ';
	  else
			decrypt[i] = (char)(x+65);
	}

	return(decrypt);
}

int ModuloAdd (int f, int k)
{
	int tmp;
	tmp = f + k;
	if (tmp >= KEYSETLEN )
		tmp-=KEYSETLEN;
	return(tmp);
}

int ModuloSub (int f, int k)
{
	int tmp;
	tmp = f - k;
	if (tmp < 0 )
		tmp+=KEYSETLEN;
	return(tmp);
}
