/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/11/02
 *  Last Modification date: 2014/11/09
 *  Filename: arrayAdd.cpp
 *
 *  Overview:
 *		Write a  function that takes as parameters three arrays-of-int (that are
 *		the same length) and the size of the arrays. It should add the first two
 *		arrays element by element, storing each sum in the corresponding element
 *		of the third array. All array accesses should be done with pointer
 *		arithmetic. 
 *
 *		In main you will need to query the user for the size of the arrays and
 *		the values in the first two arrays, pass them to the function, and then
 *		print out the third array. For example, if the first two arrays are
 *		[3,4,1,4,6] and 
 *		[5,1,7,8,3], then the third array will be 
 *		[8,5,8,12,9].
 */

#include <iostream>
#include "_validateIntegerInput.cpp"

#define MAX_NUMS 50

// validateIntegerInput (MinValue, MaxValue, MaxNumberOfTries, Prompt);
// In a .cpp file, use a one- or two-line comment above the function declaration
void addArrays(int *arrayA, int *arrayB, int *arraySum, int arrayLen);
void fillArrays(int *arrayA, int *arrayB, int arrayLen);



int main () 
{
	int arrayLen;
	int counter;
	int *arrayA;
	int *arrayB;
	int *arraySum;

	std::cout << "How many values do you want to enter?[1-" << MAX_NUMS << "]  ";
	arrayLen = validateIntegerInput(1,MAX_NUMS,1," ");

  arrayA = new int [arrayLen];
  arrayB = new int [arrayLen];
  arraySum = new int [arrayLen];
 
  fillArrays(arrayA, arrayB, arrayLen);
	addArrays(arrayA, arrayB, arraySum, arrayLen);

	for (counter=0; counter < arrayLen; counter++)
		std::cout << "(" << arrayA[counter] << " + " << arrayB[counter] << ") =  " 
			<< arraySum[counter] << std::endl;
}

/****************************************************************
 * addArrays(int *arrayA, int *arrayB, int *arraySum, int arrayLen)
 *
 * 		Purpose: Add two arrays of integers, store the sum in a third
 * 					   array
 * 		Takes:  int* pointers to three arrays of integers
 * 					  arrayLen, the length of all three arrays
 ***************************************************************/
void addArrays(int *arrayA, int *arrayB, int *arraySum, int arrayLen)
{
	for (int i=0; i< arrayLen; i++)
	{
		//arraySum[i] = arrayA[i] + arrayB[i];
		*(arraySum + i)  = *(arrayA + i) + *(arrayB +i);
	}
}
/****************************************************************
 * void fillArrays(int *arrayA, int *arrayB, int arrayLen)
 *
 * 		Purpose: Collect integers from user input, fill two arrys
 * 		Takes:  int* pointers to two arrays of integers
 * 					  arrayLen, the length of both arrays
 ***************************************************************/
void fillArrays(int *arrayA, int *arrayB, int arrayLen)
{
	int counter;

  std::cout << "Enter the first set of numbers." <<std::endl;
	for (counter=0; counter < arrayLen; counter++)
	{
		std::cout << "A" << counter+1 ;
		// TODO: better use of this function, reporting range, etc.
		arrayA[counter] = validateIntegerInput(-250,250,1, ": ");	  
	}
  std::cout << "Enter the Second set of numbers." <<std::endl;
	for (counter=0; counter < arrayLen; counter++)
	{
		std::cout << "B" << counter+1 ;
		arrayB[counter] = validateIntegerInput(-250,250,1, ": ");
	}

}
