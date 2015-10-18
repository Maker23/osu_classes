/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);	// This deref will dump core if s is a null pointer
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	
	char c;
	DynArr *Parens;
	Parens = newDynArr(5); // Arbitrary first length

	//printf("DEBUG 40 s = %p\n", s);
	while ( (c = nextChar(s)) != '\0' ) 
	{
		if (EQ(c, '(')) pushDynArr(Parens, ')');
		else if (EQ(c, '{')) pushDynArr(Parens, '}');
		else if (EQ(c, '[')) pushDynArr(Parens, ']');
		else if (EQ(c, ')') || EQ(c,'}') || EQ(c, ']'))
		{
			if(isEmptyDynArr(Parens))
				return 0; // We already know we're unbalanced
			else
				if ( EQ(topDynArr(Parens), c)) popDynArr(Parens);
		}
	}

	if (isEmptyDynArr(Parens))
		return 1;  // True, is balanced
  else
		return 0; // False, is not balanced
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

  if ( s != NULL ) // This is a bad test, should probably use argc > 1
	{
	  //printf("DEBUG 71 s = %p\n", s);
		res = isBalanced(s);

		if (res)
			printf("The string %s is balanced\n",s);
		else 
			printf("The string %s is not balanced\n",s);
	}
	else
	{
		printf ("USAGE: %s <string>\n", argv[0]);
	}
	
	return 0;	
}

