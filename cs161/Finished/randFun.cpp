/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/10/20
 *  Last Modification date: 2014/10/26
 *  Filename: randFun.cpp
 *
 *  Overview: 
 * 		a. I say that your final answer (function prototype) should look like: 
 * 			int rand_int(int min, int max),
 * 		b. I say that it should accept two int values (one for the minimum value
 * 			for some random number in a range and one for the maximum number in the
 * 			range), generate a number within that range, and then return that number,
 * 			though the exact details on how it generates the number are up to you,
 *
 *  Input:
 *		Two integers from user input
 *  Output:
 *		one random number between the two values entered
 */

#include <climits>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <cstdio>		// Because sprintf

#define NUM_RANDS 1	 // It's easier to debug with a higher number here
#define DEBUG false	 // More or less verbose


/* Generate a random integer within a given range, inclusive */
int rand_int(int lowNum, int highNum);

/* Take one line of input from the user, confirm it is an integer number. */
int validate_integer_input (int MinimumValue=INT_MIN, int MaximumValue=INT_MAX, 
	int MaximumNumberOfTries=0, const std::string Prompt="");

int main () 
{
	int highNum = 0;	// One end of the number range, from user input
	int lowNum = 0;		// The other end of the number range, from user input
	int r; 						// The random number

	srand(time(NULL)); // Seed the random generator with time in msec

	highNum = validate_integer_input(INT_MIN,RAND_MAX,2, "Highest value: ");
	lowNum = validate_integer_input(INT_MIN,RAND_MAX,2, "Lowest value: ");

	if (highNum == lowNum) 
	{
		std::cout << "Can't find a range between two equal numbers" << std::endl;
		//return 1;
	}

  // Print user-friendly output
  if (NUM_RANDS > 1)
  	std::cout << "Generating " << NUM_RANDS << " random numbers "
			<< "between " << lowNum << " and " << highNum << std::endl;
	else 
		std::cout << "Here is your random number "
			<< "between " << lowNum << " and " << highNum << ": ";

  // Print our random numbers`
	for(int i=0; i< NUM_RANDS; i++)
	{
		r = rand_int (lowNum, highNum);
		std::cout << r << std::endl;
	}
}


/* ***************************************************************************
 *	int rand_int(int lowNum, int highNum)
 *
 *  Purpose: Return a random number betwen lowNum and highNum, inclusive of both ends
 *  		of the range
 *  Input:  Two integer values. It does not really matter which one is larger
 *  Output: One random integer between highNum and lowNum, inclusive
 *
 * ***************************************************************************/
int rand_int(int lowNum, int highNum)
{
	if (highNum == lowNum) 
	{ 
		// This would cause a core dump. Don't have a good way to signal error
		// though, since 0 can be a valid return value. Ideally check for this
		// before calling the function
		exit(1); 
	} 

 	return ((rand() % (abs(highNum - lowNum) + 1)) + (lowNum < highNum? lowNum : highNum));
}
/* ***************************************************************************
 *  validate_integer_input (MinimumValue, MaximumValue, MaximumNumberOfTries, Prompt);
 *
 *  Purpose: Confirm that a value grabbed from cin is an integer
 *  Input: 
 *  	MinimumValue: the low end of the valid number range
 *  	Maximumvalue: the high end of the valid number range
 *  	MaximumNumberOfTries: how many tries the user has to enter a valid integer
 *  	Prompt: what we use to prompt the user with
 *
 *  Note that acceptable integers
 *  	* Can begin with a minus sign (negative)
 *  	* Can not have any characters other than [0-9] and "."
 *  		* If "." appears, test the string as a float. It may be a number.00;
 *  		  this is accepted as an integer by this function (eg, 43.0,  109.00)
 *
 * ***************************************************************************/

int validate_integer_input(
	int MinRange,
	int MaxRange,
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
		sprintf(buffer, "\tEnter an integer between %d and %d: ", MinRange, MaxRange);
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
	  else if ( (inputInteger < MinRange ) || (inputInteger > MaxRange) ) 
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
