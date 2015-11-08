/* vim ts=2
 
 Shoshana Abrass
 abrasss@oregonstate.edu
 CS261 Fall 2015

 Assignment 4 Extra Credit
 File: main.c
 Implementation of the animal guessing game.
 
*/

#include <stdio.h>
#include "structs.h"

/*
 * Function to create and initialize a new tree with no Nodes
 * Returns the tree pointer.
 */
/*----------------------------------------------------------------------------*/
struct Tree*  newTree()
{
	struct Tree *tree = (struct Tree *)malloc(sizeof(struct Tree));
	assert(tree != NULL);

	tree->cnt  = 0;
	tree->root = NULL;
	return tree;
}

/*----------------------------------------------------------------------------*/
/*
function to free the nodes of a binary search tree
param: node  the root node of the tree to be freed
 pre: none
 post: node and all descendants are deallocated
*/

void _freeTree(struct Node *node)
{
	if (node != NULL) 
	{
		_freeTree(node->Yes);
		_freeTree(node->No);
		free(node);
	}
}

/*
 function to clear the nodes of a binary search tree
 param: tree    a binary search tree
 pre: tree ! = null
 post: the nodes of the tree are deallocated
		  	tree->root = 0;
				tree->cnt = 0
 */
void clearTree(struct Tree *tree)
{
	_freeTree(tree->root);
	tree->root = NULL;
	tree->cnt  = 0;
}

/* Functions to print a tree and a node, useful for debugging */
/*----------------------------------------------------------------------------*/
void printNode(struct Node *cur) {
	 if (cur == 0) return;
	 printf("(");
	 printNode(cur->Yes);	 
	 printf("%s", cur->String);
	 printNode(cur->No);
	 printf(")");
}

void printTree(struct Tree *tree) {
	 if (tree == 0) return;	 
	 printNode(tree->root);	 
}

/*
 * After reaching a leaf node and guessing the player's animal, ask
 * if the guess is correct.  If not, add a new question and a new
 * animal to the tree.
 */
/*----------------------------------------------------------------------------*/
struct Node * amIRight (struct Node *Question)
{
	char Ans;
	char *pos;
	char NewQ[256];
	char NewA[256];

	printf("Am I right? [yn] ");
	Ans = getOneChar();

	if ( Ans == 'n')
	{
		struct Node * NewAnimal = malloc (sizeof (struct Node));
		struct Node * ThisAnimal = malloc (sizeof (struct Node));

		ThisAnimal->String = malloc((strlen(Question->String) +1 )* sizeof(char)); 
		strcpy(ThisAnimal->String, Question->String);
		ThisAnimal->Yes = NULL;
		ThisAnimal->No = NULL;


		printf ("What animal are you thinking of? ");
		fgets(NewA, 255, stdin);
		if ((pos=strchr(NewA, '\n')) != NULL)
		    *pos = '\0';
		NewAnimal->String = malloc((strlen(NewA) +1 )* sizeof(char)); 
		strcpy(NewAnimal->String, NewA);
		NewAnimal->Yes = NULL;
		NewAnimal->No = NULL;

		printf ("What is a Yes/No question that would distinguish %s from %s?\nEnter a question; end with a question mark (?)\n   >> ", NewA, Question->String);
		fgets(NewQ, 255, stdin);
		if ((pos=strchr(NewQ, '\n')) != NULL)
		    *pos = '\0';
		Question->String = malloc((strlen(NewQ) +1)* sizeof(char)); 
		strcpy(Question->String, NewQ);

		printf ("For %s, is the answer to this question Yes or No? ", NewA);
		Ans = getOneChar();
		if (Ans == 'y')
		{
			if (DEBUG) printf ("DEBUG 115 got Yes\n");
			Question->No = ThisAnimal;
			Question->Yes = NewAnimal;
		}
		else 
		{
			if (DEBUG) printf ("DEBUG 115 got No\n");
			Question->Yes = ThisAnimal;
			Question->No = NewAnimal;
		}
	}
	// Assume Yes if we don't get no
	return Question;
}

/*
 * During game play, print the contents of a node.
 * If it's a leaf node print a guess (ie, an animal).
 * If it's not a leaf node just print the question.
 *
 * Returns 1 for internal nodes, 0 for leaf nodes
 */
/*----------------------------------------------------------------------------*/
int printForUser(struct Node *Question){
	if (Question->Yes == NULL && Question->No == NULL)
	{
		printf("You must be thinking of a %s!\n", Question->String);
		Question = amIRight(Question);
		return 0; //False
	}
	else
		printf("%s", Question->String);
	return 1; // True
}

/*
 * A helper function to get one character of user input and lowercase it.
 * Everything but the first character is thrown away (to clear the input buffer)
 */
/*----------------------------------------------------------------------------*/
char getOneChar(){	
	char Ans, tmp;

	Ans = fgetc(stdin);
	if (Ans == '\n') return Ans;
	for (;;)
	{
		tmp = fgetc(stdin);
		if (tmp == '\n') break;
	}
	if (Ans < 'Z' && Ans > 'A')
		Ans = Ans + ('a' - 'A'); // lowercase 
	if (DEBUG) printf ("DEBUG: Answer is %c\n", Ans);
	return Ans;

}
/*
 * 
 *  Play the game! Starting with the root node, traverse the tree until
 *  a leaf node is found.
 *
 *  Ask the player if they want to play again.
 *
 */
/*----------------------------------------------------------------------------*/
void play(struct Tree *gameTree)
{
	printf ("Play the animal guessing game!\n");
	printf ("Answer Yes/No questions about the animal you're thinking of.\n\n");
	char Ans;
	char Again = 'y';

	while (Again != 'n')
	{
		struct Node *Current = gameTree->root;
		while ( printForUser(Current))
		{
			printf("  [yn] ");
			Ans = getOneChar();
	
			if ( Ans == 'n')
				Current = Current->No;
			if ( Ans == 'y')
				Current = Current->Yes;
		}
	
		printf ("Play again? [y] ");
		Again = getOneChar();
	}

}

int main(int argc, char *argv[])
{	
  struct Tree *gameTree	= malloc (sizeof(struct Tree));
	gameTree->root = parseFile();
	
	if (DEBUG) printTree(gameTree);
	play (gameTree);
	writeFile(gameTree);
  clearTree(gameTree);
	return 0;
}
