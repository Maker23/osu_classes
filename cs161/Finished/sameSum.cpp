/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/11/09
 *  Last Modification date: 2014/11/16
 *  Filename: sameSum.cpp
 *
 *  Overview:
 *  Write a function that takes as parameters a square 2D array of ints and
 *  the number of rows in the user's square. The function should return a
 *  boolean value indicating whether all of the rows, columns, and both
 *  major diagonals of the user's square sum to the same value. In main,
 *  you should ask the user for the size of their square. You can assume a
 *  maximum size of 10x10 – the user's square doesn't have to fill the
 *  array.  Then let the user enter values to fill their square. Let them
 *  enter a whole row on one line, with whitespace separating the values.
 *  After that, call your function and then display the return value. 
 *
 */

#define DEBUG false // more or less verbose
#include <iostream>

// PROTOTYPE
bool getIntegerInput(int *intArray, int arrayLen, int minInt, int maxInt);

#include "_validateIntegerInput.cpp"
#define SQRSIZE 10

bool checkSumRowsAndColumns(int intMatrix[][SQRSIZE], int userSize);

int main () 
{
	int intMatrix[SQRSIZE][SQRSIZE];
	int userSize;
	int minInt = -50;
	int maxInt = 1000;
	int i;
	bool goodData=true;

  // Tell the user what we're doing here
	std::cout << 
		"This program will calculate the row, column, and diagonal sums" 
		<< std::endl 
		<< "for a square of integer numbers. The maximum square size is "
		<< SQRSIZE
		<< std::endl << std::endl;
 	std::cout << "How large will your square be? [1-" << SQRSIZE << "] ";
  userSize = validateIntegerInput(1,SQRSIZE,2," ");

  // Fill the square with numbers
  std::cout << "Please fill your square with integer values between " << minInt 
		<< " and " << maxInt << std::endl << std::endl;
  for (i=0; i<userSize; i++)
	{
		std::cout << "Line " << i+1 << ": ";
		do { 
			goodData = getIntegerInput (intMatrix[i], userSize, minInt, maxInt, " ");
		}
		while ( goodData == false);
	}

	if (checkSumRowsAndColumns(intMatrix, userSize))
		std::cout << "TRUE, row/column/diag sums are the same" << std::endl;
	else
		std::cout << "FALSE, row/column/diag sums are NOT the same" << std::endl;

}

/**********************************************
 * Use a comment block above the function definition
 *
 * 		Purpose:
 * 		Entry:
 * 		Exit:
 *
 *********************************************/
bool checkSumRowsAndColumns(int intMatrix[][SQRSIZE], int userSize)
{
	int i,j;
	int *Sum;
	int numSums;
	 
	// DEBUGGING INFO
  for (i=0; i< userSize; i++) 
	{
		for (j=0; j< userSize; j++)
		{
			if (DEBUG) 
				std::cout << "intMatrix[" << i << "][" << j << "] = " << intMatrix[i][j]
					<< std::endl;
		}
	}

  // There are (userSize) row sums, (userSize) column sums, and 
	// 2 diagonal sums - so, 2*userSums +2 in total.
	// Create an initialize the array to hold the Sums
  numSums = 2*userSize + 2;
  Sum = new int [numSums];
  for (i=0; i<numSums; i++)
		Sum[i] = 0; // initialize sums

  // Calculate all the sums from the input data
  for (i=0; i<userSize; i++)
	{
		Sum[numSums-1] 		 += intMatrix[i][i]; 							// Diagonal one
		Sum[numSums-2]     += intMatrix[i][(userSize-1)-i]; // Diagonal two
		for (j=0; j<userSize; j++)
		{
			Sum[i] += intMatrix[i][j];  				// Row sum
			Sum[j+userSize] += intMatrix[i][j]; // Column sum
		}
  }

	// Now compare the different Sums to see if they're the same
	if (DEBUG) std::cout << "Sum[0] = " << Sum[0] << std::endl;
  for (i=1; i<numSums; i++)
	{
		if (DEBUG) std::cout << "Sum[i] = " << Sum[i] << std::endl;
		if ( Sum[i] != Sum[0] )
		{
			return(false);
		}
	}
	return(true);
}


