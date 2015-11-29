/* vim: ts=2
 *
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Class: OSU CS261, Data structures. Fall 2015 section 400
 *  Filename: main.c
 *
 *  Overview: This program exercises the hashMap functions
 *            and calculates the concordance for an input file
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hashMap.h"
#include <time.h>

#define DEBUG 0


void test();
/*
 the getWord function takes a FILE pointer and returns you a string which was
 the next word in the in the file. words are defined (by this function) to be
 characters or numbers seperated by periods, spaces, or newlines.
 
 when there are no more words in the input file this function will return NULL.
 
 this function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it.
 */
char* getWord(FILE *file);

int main (int argc, const char * argv[]) {
	const char* filename;
	struct hashMap *hashTable;	
	int tableSize = 10;
	clock_t timer;
	FILE *fileptr;	
	char *nextWord;
	ValueType *valueptr;

	if (DEBUG)
	{
		printf ("DEBUGGING is on\n"); 
		test();
		return 0;
	}
	/*
	 this part is using command line arguments, you can use them if you wish
	 but it is not required. DO NOT remove this code though, we will use it for
	 testing your program.
	 
	 if you wish not to use command line arguments manually type in your
	 filename and path in the else case.
	 */
	if(argc == 2)
		filename = argv[1];
	else
		filename = "input1.txt"; /*specify your input text file here*/
		
	printf("opening file: %s\n", filename);
	fileptr = fopen (filename, "r");
	if (fileptr == NULL)
	{
		perror(filename);
		return 1;
	}
		
	timer = clock();
	
	hashTable = createMap(tableSize);	   
	
  /*... concordance code goes here ...*/

	nextWord = getWord(fileptr);
	while ( nextWord != NULL )
	{
		valueptr = atMap(hashTable, nextWord);

		if (valueptr == NULL )
			insertMap(hashTable, nextWord, 1);
		else
			insertMap(hashTable, nextWord, *valueptr + 1);
		
		nextWord = getWord(fileptr);
	}
	fclose(fileptr);
		
	/*... concordance code ends here ...*/

	printMap(hashTable);
	timer = clock() - timer;
	printf("\nconcordance ran in %f seconds \n", (float)timer / (float)CLOCKS_PER_SEC);
	printf("Table emptyBuckets = %d\n", emptyBuckets(hashTable));
		printf("Table count = %d\n", size(hashTable));
	printf("Table capacity = %d\n", capacity(hashTable));
	printf("Table load = %f\n", tableLoad(hashTable));
	
	printf("Deleting keys\n");
	
	removeKey(hashTable, "and");
	removeKey(hashTable, "me");
	removeKey(hashTable, "the");
	printMap(hashTable);
		
	deleteMap(hashTable);
	printf("\nDeleted the table\n");   
	return 0;
}

void printValue(ValueType v) {
	//printf("Value:%d",(int *)v);
	printf("Value:%d",v);
}

char* getWord(FILE *file)
{
	int length = 0;
	int maxLength = 16;
	char character;
		
	char* word = malloc(sizeof(char) * maxLength);
	assert(word != NULL);
		
	while( (character = fgetc(file)) != EOF)
	{
		if((length+1) > maxLength)
		{
			maxLength *= 2;
			word = (char*)realloc(word, maxLength);
		}
		if((character >= '0' && character <= '9') || /*is a number*/
		   (character >= 'A' && character <= 'Z') || /*or an uppercase letter*/
		   (character >= 'a' && character <= 'z') || /*or a lowercase letter*/
		   character == 39) /*or is an apostrophy*/
		{
			word[length] = character;
			length++;
		}
		else if(length > 0)
			break;
	}
		
	if(length == 0)
	{
		free(word);
		return NULL;
	}
	word[length] = '\0';
	return word;
}

void test()
{
	struct hashMap *hashTable;	
	int tableSize = 23;
	hashTable = createMap(tableSize);	   
	insertMap(hashTable, "test", 1);
	insertMap(hashTable, "test Two", 2);
	insertMap(hashTable, "This is not a test", 4);
	insertMap(hashTable, "What the what", 5);
	printMap(hashTable); printf("\n");

	insertMap(hashTable, "test", 7);
	insertMap(hashTable, "No, who's on second", 30);
	printMap(hashTable); printf("\n");

	printf("\nValue for key \"test\" is %d\n", *(atMap(hashTable, "test")));

	struct hashMap *hTable2;
	tableSize = 4;
	hTable2 = createMap(tableSize);	   
	insertMap(hTable2, "ate", 1);
	insertMap(hTable2, "tea", 2);
	insertMap(hTable2, "eat", 3);
	printf("Worst case table for hash function 1:\n");
	printMap(hTable2); printf("\n");
}
