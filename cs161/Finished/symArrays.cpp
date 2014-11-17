/* vim: ts=2
 *
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/11/09
 *  Last Modification date: 2014/11/16
 *  Filename: symArrays.cpp
 *
 *  Overview:
 *  Write a program that allows the user to use command line arguments to
 *  specify the sizes of 3 int arrays they will enter data for. Then you will
 *  dynamically allocate the arrays using new. Then allow the user to enter the
 *  integers for each element in each array. Let them do this on a single line
 *  with whitespace separated values. Next, for each array, print out whether
 *  it is symmetric. 
 *  Lastly, you will  deallocate the arrays with delete. 
 *
 */

/* Function prototypes */
// Check args for validity, fill arrayLen with values
int 	parseArguments(int argc, char **argv, int *arrayLen);
// Return true if an array is symmetric, false otherwise
bool 	isSymmetric(int *array, int arrayLen);
// Print a usage/help statement about this program
void 	printUsage(char **argv);
// This function is declared in _validateIntegerInput.cpp"
bool getSmallIntegerInput(int *intArray, int arrayLen); 

#include <iostream>
#include <string>
#include "_validateIntegerInput.cpp"

#define MINARRAYLEN 1
#define MAXARRAYLEN 256

#define DEBUG false

int main (int argc, char **argv)
{
	int *arrayOne;	// Three arrays, size not yet known
	int *arrayTwo;
	int *arrayThree;
	int arrayLen[3]; // Array sizes will be supplied by user at runtime
	bool goodData;

	if (parseArguments(argc, argv, arrayLen))
	{
		// Bad arguments?  Explain and exit
		printUsage(argv);
		return(1);
	}
	// Allocate memory for the requested arrays
	arrayOne = new int [arrayLen[0]];
	arrayTwo = new int [arrayLen[1]];
	arrayThree = new int [arrayLen[2]];

	// Ask the user to fill the arrays with integers
	std::cout <<
		"Enter the required number of integers for your arrays." << std::endl
		<< "Use integer values between 1 and 100. This program will" << std::endl
		<< "check the arrays for symmetry" << std::endl<< std::endl;
	do {
		std::cout << "Array one.  ";
		goodData = getSmallIntegerInput (arrayOne, arrayLen[0]);
	} while (! goodData);
	do {
		std::cout << "Array two.  ";
		goodData = getSmallIntegerInput (arrayTwo, arrayLen[1]);
	} while (! goodData);
	do {
		std::cout << "Array three.  ";
		goodData = getSmallIntegerInput (arrayThree, arrayLen[2]);
	} while (! goodData);

	// Test the arrays for symmetry, print the results
	std::cout << "arrayOne is ";
	if (! isSymmetric(arrayOne, arrayLen[0])) std::cout << "not ";
	std::cout << "symmetric" << std::endl;

	std::cout << "arrayTwo is ";  
	if (! isSymmetric(arrayTwo, arrayLen[1])) std::cout << "not ";
	std::cout << "symmetric" << std::endl;

	std::cout << "arrayThree is ";
	if (! isSymmetric(arrayThree, arrayLen[2])) std::cout << "not ";
	std::cout << "symmetric" << std::endl;

	// Free up the memory, unset the pointers
	delete [] arrayOne;  arrayOne = 0;
	delete [] arrayTwo;  arrayTwo = 0;
	delete [] arrayThree;  arrayThree = 0;
}

bool isSymmetric(int *array, int arrayLen)
{
	int halfLen = arrayLen/2;

	for (int i=0; i < halfLen; i++)
	{
		if (array[i] != array[arrayLen-(1+i)] )
			return(0);
	}
	return(1);
}

int parseArguments(int argc, char **argv, int *arrayLen)
{
	int tmp;
	if (argc < 4)
	{
		return(1);
	}
	for (int i=1; i<argc; i++)
	{
		if (DEBUG) std::cout << "argv " << i << " is " << argv[i] << std::endl;
		tmp =  validateIntegerInput(argv[i], MINARRAYLEN, MAXARRAYLEN);
		if ( tmp < MINARRAYLEN)
		{
			std::cout << "Bad value. Exiting...." << std::endl;
			return(1);
		}
		arrayLen[i-1] = tmp;
	}
}
void printUsage(char **argv)
{
	std::cout << 
		"USAGE: " << argv[0] << "  <int> <int> <int>" << std::endl <<
		"WHICH: takes three integer arguments as array sizes." << std::endl;
}
