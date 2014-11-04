/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/10/27
 *  Last Modification date: 2014/11/02
 *  Filename:  hailstone.cpp
 *
 *  Overview:
 *		A hailstone sequence starts with a given integer. If that integer is
 *		even, then you divide it by two to get the next integer in the sequence,
 *		but if it is odd, then you multiply it by three and add one to get the
 *		next integer in the sequence. Then you use the value you just generated
 *		to find out the next value, according to the same rules. Your recursive
 *		function should take as input the starting integer and count how many
 *		steps it takes to reach 1 (technically you could keep going
 *		1, 4, 2, 1, 4, 2, etc. but we will stop when you first reach 1). If the 
 *		starting integer is 1, the output should be 0, since it takes no steps
 *		to reach one (we're already there). If the starting integer is 3, then
 *		the sequence would go: 3, 10, 5, 16, 8, 4, 2, 1, and the output should be 7.
 *
 */

#include <iostream>
#define DEBUG false

// The following are for validateIntegerInput
#include <climits>
#include <cstdio>		// Because sprintf
#include <cstdlib>
#include <sstream>
#include <string>

// Input an integer, return number of steps to hailstone that integer to 1
int hailstoneToOne(int i);

// Take one line of input from the user, confirm it is an integer number. 
int validateIntegerInput (int MinValue=INT_MIN, int MaxValue=INT_MAX, 
	int MaxNumberOfTries=0, const std::string Prompt="");

int main () 
{
	int i = 0;
	int steps = 0;

  std::cout << "This program calculates the steps required to go from a"
		<< std::endl << "positive integer to 1, using the hailstone sequence"
		<< std::endl;

  i = validateIntegerInput(1,1000,2, "Enter a positive integer between 1 and 1000: ");

  if (DEBUG) std::cout << "Progression: " << i;
  steps = hailstoneToOne(i);
  if (DEBUG) std::cout << std::endl << "steps to 1 = " ;
	std::cout << steps << std::endl;
}

/* ***************************************************************************
 * 		hailstoneToOne (int i)
 *
 * 		Purpose: Return the number of steps to get a given integer to "1" 
 * 			following  a hailstone sequence
 * 		Entry: A positive integer
 * 		Exit:  Number of steps to 1 (integer)
 *
 ****************************************************************************/
int hailstoneToOne(int i)
{
	if ( i == 1 ) 
	{
		return (0);
	}
	if ( ( i % 2 ) == 0 )
	{
		if (DEBUG) std::cout << "," << i/2;
		return ( 1 + hailstoneToOne(i/2));
	}
	else {
		if (DEBUG) std::cout << "," << 3*i+1;
		return ( 1 + hailstoneToOne(3*i+1));
	}
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
