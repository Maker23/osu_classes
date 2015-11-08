/* vim ts=2
 
 Shoshana Abrass
 abrasss@oregonstate.edu
 CS261 Fall 2015

 Assignment 4 Extra Credit
 File: parseFile.c
 File reading/writing routines for the animal guessing game.
 
*/

#ifndef _ParseH
#define _ParseH
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "structs.h"

struct fileLine * _parseOneLine (char *oneLine);
struct fileLine *	_createFileLine(char *QID, char *Question, char *Yes, char *No);
void _printFileLine (struct fileLine *FileLine);
struct Node *	_buildTree(struct fileLine *FileLine);
char * _writeLine (struct Node * Node, FILE * fp);

struct fileLine *FileLineArray[256]; // It's a global. So sue me.

/*
 *
 * TODO: Free everything in FileLineArray
 * TODO: Comment all the functions
 *
 */

/* 
 * Function to read in a 'database' for the animal guessing game.(a text file)
 * 
 * Returns a root Node for the tree built from the data
 */
/* ****************************************************************** */
struct Node * parseFile()
{
	//int i;
	int countFileLines=0;
	FILE *fp;
	char oneLine[256];
	struct fileLine *newFileLine;

  /*
	 * Open the file, parse the lines using helper functions,
	 * and create an array from the data.
	 *
	 * Array indices correspond to question number (eg, _Q12 
	 * will be in FileLineArray[12]
	 *
	 * The array may be sparse.
	 *
	 */
	fp = fopen("Animals.txt", "r");
	if (fp == NULL )
	{
		perror("Error opening file Animals.txt for read");
		assert (1);
	}
	while (fgets (oneLine, 256, fp) != NULL )
	{
		newFileLine = _parseOneLine(oneLine);
		if (newFileLine != NULL )
		{
			if (newFileLine->QID >0)
			{
				assert (newFileLine->QID < 256);
				FileLineArray[newFileLine->QID] = newFileLine;
				countFileLines++;
			}
		}
	}
	fclose(fp);

	/* uncomment for yet more debugging */
	/*
	for (i=1; i<countFileLines; i++)
	{
		printf ("Item %d: ", i);
		if (FileLineArray[i] != NULL)
			_printFileLine(FileLineArray[i]);
	}
	*/

	assert (FileLineArray[1] != NULL);
	if (DEBUG) printf("I AM ABOUT TO CALL BUILD TREE\n");
	return _buildTree(FileLineArray[1]);
}

/* 
 * Helper function to parse one line read from the input file.
 *
 * Parameter: A character string representing one line of the file
 * Return: A pointer to fileLine struct created from the data
 *         Returns NULL if the line isn't valid
 *       
 *
 * This function parses the line into fields (using ':' as the delimiter)
 * and calls _createFileLine to build the struct
 */
/* ****************************************************************** */
struct fileLine * _parseOneLine (char *oneLine)
{
	char QID[256];
	char Question[256];
	char Yes[256];
	char No[256];
	int i;
	int j;


	i=0;
	j=0;
	if (oneLine[i] == '#') return NULL;
	while (oneLine[i] == 32 || oneLine[i] == 9)
	{
		i++;
	}
	while (oneLine[i] != ':' && i < 256)
	{
		QID[j++] = oneLine[i++];
	}
	QID[j]='\0';
	i++;
	j=0;
	while (oneLine[i] != ':' && i < 256)
	{
		Question[j++] = oneLine[i++];
	}
	Question[j]='\0';
	if (DEBUG) printf ("DEBUG 98: Question = %s\n", Question);
	i++;
	j=0;
	while (oneLine[i] != ':' && i < 256)
	{
		Yes[j++] = oneLine[i++];
	}
	Yes[j]='\0';
	i++;
	j=0;
	while (oneLine[i] != ':' && i < 256)
	{
		No[j++] = oneLine[i++];
	}
	No[j]='\0';
	i++;
	j=0;
	//printf ("QID: %s; Question: %s; Yes: %s; No: %s\n", QID, Question, Yes, No);
	if (DEBUG) printf ("DEBUG 117: Question = %s\n", Question);

	if ( i == 256 ) return (struct fileLine *)NULL;

	return _createFileLine(QID, Question, Yes, No);

}

/* 
 * Helper function to turn file data into a fileLine struct
 *
 * Parameters: Four strings representing the fields of a data line
 * Return: A pointer to fileLine struct created from the data
 *         Returns NULL if the line isn't valid
 *       
 *
 */
/* ****************************************************************** */
struct fileLine *	_createFileLine(char *QID, char *Question, char *Yes, char *No)
{

  /* Basic error checking: if the strings are too short or if Question
	 * is zero-length, return NULL
	 */
	if ( 	strlen(QID) < 3 ||
	 			Question[0] == '\0' ||
	 			strlen(Yes) < 3 ||
	 			strlen(No) < 3 )  return (struct fileLine *)NULL;
	
	int i, ret;
	struct fileLine *tmpFileLine = malloc (sizeof(struct fileLine));
	assert (tmpFileLine != NULL);
	// TODO test all the mallocs below
	
	ret = sscanf(QID,"_Q%d", &i);
	assert (ret != 0);
	tmpFileLine->QID = i;
	tmpFileLine->Question = malloc((strlen(Question) +1 ) * sizeof(char)); 
	strncpy (tmpFileLine->Question, Question, (int)strlen(Question));
	tmpFileLine->Yes = malloc((strlen(Yes) +1) * sizeof(char)); strcpy (tmpFileLine->Yes, Yes);
	tmpFileLine->No = malloc((strlen(No) +1)*sizeof(char)); strcpy (tmpFileLine->No, No);

	//_printFileLine (tmpFileLine); // For debugging
	if (DEBUG) printf ("DEBUG 147: tmpFileLine->Question = %s, strlen = %d\n", tmpFileLine->Question, (int) strlen(tmpFileLine->Question));
	if (DEBUG) printf ("DEBUG 147: Question = %s, strlen Question = %d\n", Question, (int) strlen(Question));

	return tmpFileLine;
}

void _printFileLine (struct fileLine *FileLine){
	printf("Question #%d: %s", FileLine->QID, FileLine->Question);
	printf("\tYes: %s\tNo: %s\n", FileLine->Yes, FileLine->No);
}


/* 
 * A recursive helper function that builds a binary tree out of yes/no
 * question data.
 *
 * Parameters: a fileLine struct pointer
 * Returns: A binary tree node representing the fileLine.
 *
 */
/* ****************************************************************** */
struct Node *	_buildTree(struct fileLine *FileLine)
{
	int y, n;
	int yesQ, noQ;
	struct Node * thisNode = malloc(sizeof (struct Node));
	struct Node * LeafNode_Y;
	struct Node * LeafNode_N;


	thisNode->String = malloc(strlen(FileLine->Question)* sizeof(char)); 
	strcpy (thisNode->String, FileLine->Question);
	if ( FileLine->Yes != NULL)
	{
		yesQ = sscanf(FileLine->Yes,"_Q%d", &y);
		if ( yesQ >0 )
		{
			thisNode->Yes = _buildTree(FileLineArray[y]);
		}
		else
		{
			//printf ("166 DEBUG: Question is %s, Yes:%s No:%s\n", FileLine->Question, FileLine->Yes, FileLine->No);
			LeafNode_Y = malloc (sizeof (struct Node));
			LeafNode_Y->String = malloc(strlen(FileLine->Yes)* sizeof(char)); 
			strcpy (LeafNode_Y->String, FileLine->Yes);
			LeafNode_Y->Yes = NULL;
			LeafNode_Y->No = NULL;
			thisNode->Yes = LeafNode_Y;
			//printNode(LeafNode_Y);
		}
	}

	if ( FileLine->No != NULL)
	{
		noQ = sscanf(FileLine->No,"_Q%d", &n);
		//printf ("180 DEBUG: noQ = %d, Question:%s\n", noQ, FileLine->Question);
		if (noQ>0)
		{
			thisNode->No = _buildTree(FileLineArray[n]);
		}
		else
		{
			//printf ("185 DEBUG: Question is %s, Yes:%s No:%s\n", FileLine->Question, FileLine->Yes, FileLine->No);
			LeafNode_N = malloc (sizeof (struct Node));
			LeafNode_N->String = malloc(strlen(FileLine->No)* sizeof(char)); 
			strcpy (LeafNode_N->String, FileLine->No);
			LeafNode_N->Yes = NULL;
			LeafNode_N->No = NULL;
			thisNode->No = LeafNode_N;
			//printNode(LeafNode_N);
		}
	}
	return thisNode;
}


/* 
 * Recursive helper function to write a node out to a text file in
 * "database" format.  A node will be represented as a single line of
 * the file.
 *
 * Parameters: a node in the tree
 * Returns: a string representation of the Question ID for the line
 * just written, in the form "_Q##". For leaf nodes return the animal name.
 *
 */
/* ****************************************************************** */
char * _writeLine (struct Node * Node, FILE * fp)
{
	static int QNum = 1; // monotonically increasing as we process the tree
	char *QStr;
	char tmpStr[26];
	char * YNum;
	char * NNum;

	if ( Node->Yes == NULL || Node->No == NULL ) {
		return (Node->String);
	}
	else 
	{
		sprintf(tmpStr, "_Q%d", QNum);
		QNum++;
		YNum = _writeLine(Node->Yes, fp); 
		QNum++;
		NNum = _writeLine(Node->No, fp); 
	}
	QStr = malloc(strlen(tmpStr)* sizeof(char)); 
	strcpy (QStr, tmpStr);
	fprintf(fp, "%s:%s:%s:%s:\n",QStr,Node->String,YNum,NNum);

	return ( QStr);
}

/* 
 * Function to write a binary tree out to a text file in "database" format
 *
 * Parameters: the root of a tree.
 */
/* ****************************************************************** */
void writeFile(struct Tree * tree){

	FILE *fp;
	fp = fopen("Animals.txt", "w");
	if (fp == NULL )
	{
		perror("Error opening file Animals.txt for overwrite");
		assert (1);
	}
	_writeLine(tree->root,fp);
	fclose(fp);
	return;
}
#endif
