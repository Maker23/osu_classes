/* CS261- Assignment 1 - Q.3*/
/* Name: Shoshana Abrass, abrasss@oregonstate.edu
 * Date: 2015-10-07
 */
 
#include <stdio.h>
#include <stdlib.h>

void sort(int* number, int n){
	/*Sort the given array number , of length n*/     
	int i = 0;
	int tmp, anySwaps;

	do {
		anySwaps = 0;

		for (i=0; i <n-1; i++)
		{
			if (number[i] > number[i+1])
			{
				tmp = number[i];
				number[i] = number[i+1];
				number[i+1] = tmp;
				anySwaps = 1;
			}
		}
	}
	while (anySwaps == 1);
}

int main(){
	/*Declare an integer n and assign it a value of 20.*/
	int i;
	int n = 20;

  /* Ha, guess this is not allowed */
	/*
	printf ("\n%s\n%s\n\n", 
		">>>>   Graders please note: For readability of the output, ",
		">>>>   I've restricted the random numbers to < 10000.");
	*/
    
	/*Allocate memory for an array of n integers using malloc.*/
	int* myArray = malloc (n * (size_t) sizeof(int));
	if (myArray == 0 ) {
		printf ("malloc fail!\n");
		return  1;
	}

  /*Fill this array with random numbers, using rand().*/
	for (i=0; i< n; i++)
	{
		myArray[i] = rand();
	}

	/*Print the contents of the array.*/
	printf("unsorted: ");
	for (i=0; i< n; i++)
	{
	  printf("%d, ",	myArray[i]);
	}
	printf("\n");

	/*Pass this array along with n to the sort() function of part a.*/
	sort (myArray, n);
    
 	/*Print the contents of the array.*/    
	printf("  sorted: ");
	for (i=0; i< n; i++)
	{
	  printf("%d, ",	myArray[i]);
	}
	printf("\n");
   
	free (myArray);
	return 0;
}
