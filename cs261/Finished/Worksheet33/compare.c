/* vim ts=2
 
 Shoshana Abrass
 abrasss@oregonstate.edu
 CS261 Fall 2015

 Assignment 4
 File: bst.c
 Implementation of the binary search tree data structure.
 
 */
#include <stdio.h>
#include <assert.h>
#include "bst.h"
#include "structs.h"

/*----------------------------------------------------------------------------
 very similar to the compareTo method in java or the strcmp function in c. it
 returns an integer to tell you if the left value is greater then, less then, or
 equal to the right value. you are comparing the number variable, letter is not
 used in the comparison.

 if left < right return -1
 if left > right return 1
 if left = right return 0
 */

 /*Define this function, type casting the value of void * to the desired type.
  The current definition of TYPE in bst.h is void*, which means that left and
  right are void pointers. To compare left and right, you should first cast
  left and right to the corresponding pointer type (struct data *), and then
  compare the values pointed by the casted pointers.

  DO NOT compare the addresses pointed by left and right, i.e. "if (left < right)",
  which is really wrong.
 */
int compare(TYPE left, TYPE right)
{
	
  struct data * Left = (struct data *)left;
  struct data * Right = (struct data *)right;

  if ( Left->number < Right->number )
		return -1;
  else if ( Left->number > Right->number )
		return 1;
	else
		return 0;

}

/*Define this function, type casting the value of void * to the desired type*/
void print_type(TYPE curval)
{
  struct data * cur = (struct data *)curval;

	//printf ("name = %s, number = %d\n", cur->name, cur->number);
	printf ("%d", cur->number);

}


