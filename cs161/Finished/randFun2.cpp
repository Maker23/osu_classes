/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/10/13
 *  Last Modification date: 2014/10/19
 *  Filename: randFun.cpp
 *
 *  Overview:
 *		Write a simple function that acts like a random number generator with
 *		the following behavior:
 *
 *			a. its definition looks like the following:
 *					void rand_int(const int &min, const int &max, int &val),
 *			b. it accepts references to two int values and a reference to a third
 *					value (one for the bottom of the random range, one for the top
 *					of the random range, and one to store the final value), generates
 *					a number within that range, and then sets the value of the third
 *					number to that generated value,
 *  Input:
 *
 *  Output:
 *
 */

#include <cstdlib>
#include <iostream>
#include <limits>
#include <time.h>
#include <climits>
#include <cstdio>
#include <sstream>
#include <string>

#define DEBUG false	 // More or less verbose


// Return a random integer between Min and Max values
int RandInt(const int &Min, const int &Max, int &randVal);

// Take one line of input from the user, confirm it is an integer number.
int validateIntegerInput (int MinValue=INT_MIN, int MaxValue=INT_MAX, 
	int MaxNumberOfTries=0, const std::string Prompt="");


int main () 
{
	int maxVal = 50;	//  Hardcoded for function demonstration purposes only
	int minVal = -50; //  Hardcoded for function demonstration purposes
	int randVal = 0;	// 	The random number

	srand(time(NULL)); // Seed the random generator with time in msec

	maxVal = validateIntegerInput(INT_MIN, INT_MAX, 3, "Enter the max value: ");
	minVal = validateIntegerInput(INT_MIN, INT_MAX, 3, "Enter the min value: ");

	if (DEBUG)
	{ std::cout << "Using hardcoded Max of " << maxVal << " and Min of " 
		<< minVal << std::endl;}

  RandInt(maxVal, minVal, randVal);
	std::cout << "Rand Val = " << randVal << std::endl;
}

/**********************************************
 * RandInt
 *
 * 		Find a random integer between Max and Min values
 * 		Input: 
 * 			int Min, int Max: minumum and maximum of range, inclusive
 * 			int randVal: will be set to a random integer
 * 		Returns: <none>
 *
 *********************************************/
int RandInt(const int &Min, const int &Max, int &randVal)
{
	randVal = (rand() % (abs(Max - Min) + 1)) + (Min < Max? Min : Max);
}

/* ***************************************************************************
 *  validateIntegerInput (MinValue, MaxValue, MaxNumberOfTries, Prompt);
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

int validateIntegerInput(
	int MinValue,
	int MaxValue,
	int MaxTries,
	std::string Prompt)
{
  std::string inputString;		// Users's input from the terminal
	double inputDouble = 0.0; 	// The input string, as a double
	int  length_of_input = 0;		// Length of the users's input string
	int  inputInteger = 0;			// The input string, as an integer
	int  number_of_tries = 0;		// Number of times user has tried to enter data
	char buffer[256];						// A buffer for creating the prompt string
	bool notANumber = false;

	if ( Prompt == "" )
	{
		sprintf(buffer, "\tEnter an integer between %d and %d: ", MinValue, MaxValue);
		Prompt = buffer;
	}
	
	do {
	  number_of_tries++;
		std::cout << Prompt;
	  std::getline(std::cin,inputString);

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
			if(!( ((inputString.at(i) >= 48) && (inputString.at(i) <= 57 ))
						|| ( i == 0 && inputString.at(i)==45)
						|| ( inputString.at(i) == 46 )
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
			std::cout << "ERROR: Part of your input was not a number\n";
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
   		std::cout << "ERROR: Value is outside permitted range.\n";
		}
		else
		{
					return(inputInteger);

		}
		notANumber = false;  // reset
	}
	while ( !number_of_tries || (number_of_tries < MaxTries) );

	std::cout << "Sorry, you've reached the maximum number of attempts (" << MaxTries << ")\n";
	exit(1);	 // Hard to return an error code.

}
