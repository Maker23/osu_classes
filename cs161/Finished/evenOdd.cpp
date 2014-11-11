/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/11/02
 *  Last Modification date: 2014/11/09
 *  Filename: evenOdd.cpp
 *
 *  Overview:
 *		Write a function that takes as parameters an array of ints and the
 *		size of the array. It should return the (sum of the even values) –
 *		(sum of the odd values). In main you will need to query the user
 *		for the size of the array and the values in the array, then call the
 *		function and display the return value.
 */

#include <climits>
#include <sstream>
#include <iostream>

#define DEBUG false	 // More or less verbose

/* Function prototypes */

// Get some number of integers as user input
int *  getIntegerInput(int &arrayLen);
// Add up the even and odd numbers in intArray, print out the result
int sumIntArray(int *intArray, int arrayLen);
// Check a string, confirm it is an integer, return the int value
int validateIntegerInput (const std::string inputString,
	int MinValue=INT_MIN, int MaxValue=INT_MAX);

int main () 
{
	int * intArray;
	int arrayLen=0;

	intArray = getIntegerInput(arrayLen);

  std::cout << "The sum of even numbers minus the sum of odd numbers is: "
		<< sumIntArray(intArray, arrayLen) << std::endl;
}

/* ***************************************************************************
 * getIntegerInput (int &arrayLen)
 *
 * 		Purpose: Collect integers as input from the user. Return a pointer
 * 		 				 to an int[] array. 256 is used as a max input line length.
 * 	  Takes: 	 arrayLen, a reference to an integer
 * 		Returns: char *, a pointer to a char[] array created with new()
 * 		Side effects:  arrayLen is set to the size of the array
 *
 *****************************************************************************/
int * getIntegerInput(int &arrayLen)
{
	int * intArray;
	int i=0;
	char tmpInt[256];
	std::string inputString;


  std::cout << "Enter a list of integers, separated by commas: ";
  std::getline(std::cin,inputString);

	std::stringstream ss (inputString); // First copy 
	std::stringstream st (inputString); // Second copy

	while ( ss.getline(tmpInt,255,','))
	{
		arrayLen++; 
	}
	intArray = new int[arrayLen];// TODO: check if length is 0

	i=0;
	while ( st.getline(tmpInt,255,','))
	{
		//std::cout << "string is " << tmpInt << " int is "<< atoi(tmpInt)<< std::endl;
		intArray[i] = validateIntegerInput(tmpInt);
		i++;
	}
  return(intArray);
}
/* ***************************************************************************
 *	sumIntArray(int *intArray, int arrayLen)
 *
 * 		Purpose: Add the integers in a array according to the assignment
 * 						 (sum of even #s  minus the sum of odd #s)
 * 	  Takes:	 intArray, an int* pointing to an array of integers
 * 	  				 arrayLen, an integer length of the array
 * 		Returns: The value of evens - odds
 *
 *****************************************************************************/
int sumIntArray(int *intArray, int arrayLen)
{
	int sumEven = 0;
	int sumOdd = 0;

	for (int i=i; i < arrayLen; i++)
	{
		if ( intArray[i] % 2 )
		{
			sumOdd += intArray[i];
		}
		else
		{
			sumEven += intArray[i];
		}
	}

	return ( sumEven - sumOdd);
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
			std::cout << "Whoa nellie! no input??" << std::endl;
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
   		std::cout << "ERROR: Value is outside permitted range.\n";
		}
		else
		{
					return(inputInteger);
		}
		notANumber = false;  // reset
	}
	while ( !number_of_tries || (number_of_tries < MaxTries) );

	std::cout << inputString << " is not an integer value, setting to zero." <<std::endl;
	return(0);	 // Hard to return an error code

}
