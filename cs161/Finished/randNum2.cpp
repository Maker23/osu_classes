/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/10/13
 *  Last Modification date: 2014/10/19
 *  Filename: randNum.cpp
 *
 *  Overview: 
 *		Write a piece of code that acts like a random number generator with 
 *		the following behavior:
 *
 *		File must be called: randNum2.cpp
 *		a. it should ask for two int values (one for the minimum value for some
 *		random number in a range and one for the maximum number in the range),
 *		b. check that the values entered were int values,
 *		c. generate a number within that range,
 *		d. assign the number generated to some variable,
 *		e. and print out the value along with some explanation so the user
 *		knows what the value is for (you will not always want to print values
 *		out, but in this case we want to see that our code is working)
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

#define NUM_RANDS 1

#define DEBUG false

/* Take one line of input from the user, confirm it is an integer number. */
int validate_integer_input (int MinimumValue=INT_MIN, int MaximumValue=INT_MAX, 
	int MaximumNumberOfTries=0, const std::string Prompt="");

int main () 
{
	int highNum = 0;	// One end of the number range, from user input
	int lowNum = 0;		// The other end of the number range, from user input
	int r; 						// The random number

	srand(time(NULL)); // Seed the random generator with time in msec

	highNum = validate_integer_input(INT_MIN,INT_MAX,2, "Highest value: ");
	lowNum = validate_integer_input(INT_MIN,INT_MAX,2, "Lowest value: ");

	if (highNum == lowNum) 
	{
		std::cout << "Can't find a range between two equal numbers" << std::endl;
		return 1;
	}

  if (NUM_RANDS > 1)
	{
  	std::cout << "Generating " << NUM_RANDS << " random numbers "
			<< "between " << lowNum << " and " << highNum << std::endl;
	}
	else 
	{
		std::cout << "Here is your random number "
			<< "between " << lowNum << " and " << highNum << ": ";
	}

	for(int i=0; i< NUM_RANDS; i++)
	{
  	r = (rand() % abs(highNum - lowNum)) + (lowNum < highNum? lowNum: highNum);
		std::cout << r << std::endl;
	}
}







/* ***************************************************************************
 *
 *  validate_integer_input (MinimumValue, MaximumValue, MaximumNumberOfTries, Prompt);
 *
 *  Validate that the string is an integer number
 *  	* Can begin with a minus sign (negative)
 *  	* Can not have any characters other than [0-9] and "."
 *  		* If "." appears, test the string as a float. It may be a number.00;
 *  		  this is accepted as an integer (eg, 43.0,  109.00)
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
		if (DEBUG) std::cout << "inputDouble = " << inputDouble << ", inputInteger = " << inputInteger << std::endl;

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
 			if ( DEBUG ) {std::cout << "Numeric value l.49 = " << inputInteger << "num_tries = " << number_of_tries << "\n";}
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
