/* You can modify the structure to store whatever you'd like in your BST */
#ifndef _StructsH
#define _StructsH
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define DEBUG 0

struct fileLine {
	int QID;
	char *Question;
	char *Yes;
	char * No;
};

struct Node {
	char * String;
	struct Node *Yes;
	struct Node *No;
};

struct Tree {
	struct Node *root;
	int          cnt;
};

/* Prototypes from main.c */
struct Tree*  newTree();
void printNode(struct Node *cur);
char getOneChar();

struct Node * parseFile();
void writeFile(struct Tree * tree);

/* Prototypes from parseFile.c */
#endif
