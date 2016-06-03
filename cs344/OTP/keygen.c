/* vim:ts=2
 *                      Shoshana Abrass
 *                  abrasss@oregonstate.edu
 *                    CS372_400 Program 2
 *                       May 29, 2016
 *
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "otp_proto.h"



main(int argc, char **argv)
{
	long int keyLength;
	long int i;
	char k;
	char *keyArray = (char * ) malloc (KEYSETLEN * sizeof(char));
	strncpy(keyArray, KEYSET, KEYSETLEN);

	if (argc < 2)
	{
		fprintf(stderr, "ERROR: Missing argument\n");
		usage(argv[0]);
		exit(1);
	}
	keyLength = strtol(argv[1], NULL, 10);
	if (keyLength <= 0)
	{
		fprintf(stderr, "ERROR: Couldn't interpret %s as a positive integer\n",argv[1]);
		usage(argv[0]);
		exit(1);
	}

	srand(time(NULL));
	for (i = 0; i< keyLength; i++)
	{
		k = keyArray[rand() % KEYSETLEN];
		putc(k, stdout);
	}
	putc('\n', stdout);
}

usage(char * progname)
{
	fprintf(stderr, "USAGE: %s <keylength>\n", progname);
	fprintf(stderr, "       keylength must be a positive integer\n");
}
