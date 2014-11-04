/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/10/27
 *  Last Modification date: 2014/11/02
 *  Filename: 
 *
 *  Overview:
 *		Recursion: write a recursive function that takes one parameter n of
 *		type int and returns the nth Fibonacci number. The Fibonacci numbers
 *		are as follows: F0 is 1, F1 is 1, F2 is 2, F3 is 3, F4 is 5, and in
 *		general Fi+2 = Fi + Fi+1 for i = 0, 1, 2, â¦ (you get the next number
 *		by adding the previous two). The naive way of writing this function
 *		is inefficient because it ends up calculating the same numbers multiple
 *		times. It's fine for you to do it this way for now, since you're just
 *		learning recursion. If you get done with your assignment early, you might 
 *		try to figure out a recursive approach that doesn't have this problem.
 *
 */

#include <iostream>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <sstream>
#include <cstdio>

#define DEBUG false // More or less verbose
#define HIGHNUM 91 	// The 91st number in the fibonacci sequence is
										// the highest value we can hold in a long

// Two functions that return the Num'th number in the Fibonacci sequence
long calculateFib(int Num); // The naive implementation
long calculateAltFib(int Num, long (&calculated)[HIGHNUM+1]);

// Take one line of input from the user, confirm it is an integer number.
int validateIntegerInput (int MinValue=INT_MIN, int MaxValue=INT_MAX, 
	int MaxNumberOfTries=0, const std::string Prompt="");



int main () 
{
	int i=0;
	long myLong=0;
	long calculated[HIGHNUM+1]; //  ~100 * 4 bytes = 0.4KB
	for (i=0; i< HIGHNUM; i++) {
		calculated[i] = 0;
	}

  std::cout << "This program calculates the nth number in the"
		" Fibonacci sequence,"  << std::endl << "starting with 0th=1"
		" and 1st=1" << std::endl;

  i = validateIntegerInput(0,HIGHNUM,2,""); 
	std::cout << "The Fibonacci sequence at " << i << " =     " 
		<< calculateAltFib(i,calculated) << std::endl;
}

/**********************************************
 * Use a comment block above the function definition
 *
 * 		Purpose:
 * 		Entry:
 * 		Exit:
 *
 *********************************************/
long calculateFib(int Num)
{
	if ( Num < 0 ) {
		return(0);
	}
	if ( Num == 1 || Num == 0 )
	{
		return(1);
	}
  else 
	{
		return ( calculateFib(Num-1) + calculateFib( Num-2));
	}
}

long calculateAltFib(int Num,long (&calculated)[HIGHNUM+1])
{
	if ( Num < 0 ) {
		calculated[0] = 0;
		return(0);
	}
	if ( Num == 1 || Num == 0 )
	{
		calculated[1] = 1;
		return(1);
	}
  else 
	{
		if ( ! calculated[Num-1] ) {
			if (DEBUG) std::cout << "	calculating " << Num -1 << std::endl;
			calculated[Num-1] = calculateAltFib(Num-1, calculated);
		}
		if ( ! calculated[Num-2] ) {
			if (DEBUG) std::cout << "	calculating " << Num -2 << std::endl;
			calculated[Num-2] = calculateAltFib(Num-2, calculated);
		}
		return(calculated[Num-1] + calculated[Num-2]);
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
