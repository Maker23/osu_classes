/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/11/02
 *  Last Modification date: 2014/11/09
 *  Filename: grades.cpp
 *
 *  Overview:
 *		Generate a text-based histogram for a quiz given to a class of students.
 *		The quiz is graded on a scale from 0 to 5. Write a program that allows
 *		the user to enter grades for each student. As the grades are being
 *		entered, the program should count, using an array, the number of 0’s, the
 *		number of 1’s, the number of 2’s, the number of 3’s, the number of 4’s,
 *		and the number of 5’s. The program should be capable of handling an
 *		arbitrary number of student grades.
 *
 *		You can do this by making an array of size 6, where each array element is
 *		initialized to zero. Whenever a zero is entered, increment the value in
 *		the array at index 0. Whenever a one is entered, increment the value in
 *		the array at index 1, and so on, up to index 5 of the array.  
 *
 * 		Output the histogram count at the end. For example, if the input grades
 * 		are 3, 0, 1, 3, 3, 5, 5, 4, 5, 4, then the program should output 
 *		1 grade(s) of 0 
 *		1 grade(s) of 1 
 *	 	0 grade(s) of 2 
 *		3 grade(s) of 3 
 *		2 grade(s) of 4 
 *	  3 grade(s) of 5
 *
 */


#include <sstream>
#include <iostream>
#include <cstdlib>

#define MIN_GRADE 0
#define MAX_GRADE 5 
#define DEBUG false	 // More or less verbose

/* Function prototypes */

// Get some number of integers as user input
int *  getIntegerInput(int &arrayLen);

// Print a histogram of integer occurrences in an array
int histogramIntArray(int *intArray, int arrayLen, int MinVal, int MaxVal);

// Check a string, confirm it is an integer, return the int value
int validateIntegerInput (const std::string inputString,
	int MinValue=MIN_GRADE, int MaxValue=MAX_GRADE);

int main () 
{
	int * intArray;
	int arrayLen=0;

	intArray = getIntegerInput(arrayLen);

	histogramIntArray(intArray, arrayLen, MIN_GRADE, MAX_GRADE);
}

/* ***************************************************************************
 * getIntegerInput
 *
 * 		Purpose: Take an arbitrary number of numbers, confirm they're integers,
 * 						 put them into an array.
 * 	  Takes: 	 A reference to an integer arrayLen
 * 		Returns: A pointer to the filled array. 
 * 		 				 arrayLen contains the number of elements in the array
 *
 *    Note:    non-integer numbers are skipped, the function keeps going
 *
 *****************************************************************************/
#define SPC 32
#define COM 44
int * getIntegerInput(int &arrayLen)
{
	int * intArray;
	int inputLetter=0;
	int inputInt=0;
	int wordCount=0;
	char inputWord[256];
	int  wordLetter=0;
	std::string inputLine = "";
	std::string inputString = "";


	// Get input from the user
  std::cout << "Enter grades (0-5), separated by commas, spaces, or newlines."
		<< std::endl << ">>>> End input with a blank line." << std::endl << "data: ";
	do{
		std::getline(std::cin,inputLine);
		inputString+=inputLine;
  	inputString += ",";
	}
	while ( inputLine != "" );
	int inputLen = inputString.length();

	// Count the number of words in the input. Word separators can be
	// spaces, commas, or newlines
	for (inputLetter=0; inputLetter < inputLen; inputLetter++)
	{
		if  (inputString[inputLetter] == SPC || inputString[inputLetter] == COM )
		{
			if (wordLetter != 0)
				wordCount++;
			wordLetter=0;
		}
		else
			wordLetter++;
	}
	if (DEBUG) std::cout << "Word count is " << wordCount << std::endl;

	// Allocate an array of the right size
	intArray = new  int[wordCount];

  arrayLen = 0;
	// Now check whether each value is an integer in the right range
	for (inputLetter=0; inputLetter < inputLen; inputLetter++)
	{
		if  (inputString[inputLetter] == SPC || inputString[inputLetter] == COM )
		{
			if (wordLetter != 0)
			{
				inputWord[wordLetter] = NULL;
				inputInt = validateIntegerInput(inputWord);
				if ( inputInt >=0 )
				{
					intArray[arrayLen] = inputInt;
					arrayLen++;
				}
			}
			wordLetter=0;
		}
    else
		{
			inputWord[wordLetter++] = inputString[inputLetter];
		}
	}

  return(intArray);
}
/* ***************************************************************************
 * int histogramIntArray(int *intArray, int arrayLen, int MinVal, int MaxVal)
 *
 * 		Purpose: Create a histogram of values in an array
 * 	  Takes:   An int* pointer to an array of ints
 * 	  				 arrayLen length of the array
 * 	  				 MinVal, MaxVal: the low/high ends of the range of data
 * 		Returns: An integer, unused. Printing is done in this function.
 *
 *****************************************************************************/
int histogramIntArray(int *intArray, int arrayLen, int MinVal, int MaxVal)
{
	int numValues = std::abs(MaxVal - MinVal) + 1;
  int histArray[numValues];
	int i;
	int c;

	for (i=0; i < numValues; i++)
		histArray[i] = 0;	 // initialize histArray

	for (i=0; i < arrayLen; i++)
		histArray[intArray[i]] ++;	// increment value

	for (i=0; i < numValues; i++)
	{
	  std::cout <<  "Grade " << i << ":  " << histArray[i];
		std::cout <<  "     ";
		for (c=1; c <= histArray[i]; c++)
			std::cout<< "*";
		std::cout << std::endl;
  }

  return(0);
}


/* ***************************************************************************
 *  validateIntegerInput (InputString, MinValue, MaxValue);
 *
 *  Purpose: Confirm that a value grabbed from cin is an integer
 *  Input: 
 *  	MinValue: the low end of the valid number range
 *  	Maxvalue: the high end of the valid number range
 *  	MaxNumberOfTries: how many tries the user has to enter a valid integer
 *  	Prompt: what we use to prompt the user with
 *
 *  Note that acceptable integers
 *  	* Can begin with a minus sign (negative)
 *  	* Can not have any characters other than [0-9] and "."
 *  		* If "." appears, test the string as a float. It may be a number.00;
 *  		  this is accepted as an integer by this function (eg, 43.0,  109.00)
 *
 * ***************************************************************************/

#define ZERO 48
#define NINE 57
#define DASH 45
#define DOT 46
#define SPACE 32

int validateIntegerInput(
	std::string inputString,
	int MinValue,
	int MaxValue)
{
	double inputDouble = 0.0; 	// The input string, as a double
	int  length_of_input = 0;		// Length of the users's input string
	int  inputInteger = 0;			// The input string, as an integer
	int  MaxTries = 1;
	int  number_of_tries = 0;		// Number of times user has tried to enter data
	char buffer[256];						// A buffer for creating the prompt string
	bool notANumber = false;

	
	do {
	  number_of_tries++;

		// Confirm that all the character in the input string are legal 
		// as part of a number
		length_of_input = inputString.length();
		if (length_of_input == 0 ) 
		{
			//std::cout << "Whoa nellie! no input??" << std::endl;
			return(-1);
		}
		for (int i=0; i < length_of_input; i++) 
		{
			// Digits [0-9], negative signs, and decimal points are ok
			// We should really strip spaces
			if(!( ((inputString.at(i) >= ZERO) && (inputString.at(i) <= NINE ))
						|| ( i == 0 && inputString.at(i)==DASH)
						|| ( i == 0 && inputString.at(i)==SPACE)
						|| ( i == length_of_input - 1 && inputString.at(i)==SPACE)
						|| ( inputString.at(i) == DOT )
					))
			{
				// THIS IS NOT A NUMBER
				// TODO: Support Octal, binary, and Hex
				notANumber = true;
			}
		}

		// Now that we know the string is a number, convert it to a double
		// Copy the double into an integer; then test if they are equal
		std::stringstream ss (inputString);
		ss >> inputDouble;
		inputInteger = inputDouble;
		if (DEBUG) std::cout << "inputDouble = " << inputDouble << ", inputInteger = " 
			<< inputInteger << std::endl;

		if ( notANumber )
		{
			// std::cout << "ERROR: Part of your input was not a number\n";
			// TODO 'non-numeric character X found'
		}
		else if ( inputDouble != static_cast<double>(inputInteger) )
		{
				// Number is a float with a fractional part
				// TODO: this is subject to the accuracy limits of the double, 
				// for example, 10.0000000000000001  is equal to 10.
				// We could instead warn when a decimal point is detected...
				std::cout << "ERROR: Number contained a decimal value\n";
		}
	  else if ( (inputInteger < MinValue ) || (inputInteger > MaxValue) ) 
		{
 			if ( DEBUG ) {std::cout << "Numeric value l.181 = " << inputInteger 
				<< "num_tries = " << number_of_tries << "\n";}
   		std::cout << "ERROR: Value " << inputInteger << " is outside permitted range.\n";
			return(-1);
		}
		else
		{
					return(inputInteger);
		}
		notANumber = false;  // reset
	}
	while ( !number_of_tries || (number_of_tries < MaxTries) );

	std::cout << inputString << " is not an integer value, ignoring." <<std::endl;
	return(-1);	 // Hard to return an error code
}
