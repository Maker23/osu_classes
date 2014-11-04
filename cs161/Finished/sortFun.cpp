/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/10/27
 *  Last Modification date: 2014/11/02
 *  Filename: sortFun.cpp
 *
 *  Overview:
 *		Write a function that takes three integer parameters by reference.
 *		The function should rearrange the parameter values so that the first
 *		parameter gets set to the smallest value, the second parameter gets
 *		set to the second smallest value, and the third parameter gets set
 *		to the largest value. For example, given the variable assignments
 *		a = 30; b = 10; c = 20; then the function call sort(a,b,c) should result
 *		in a =10, b =20, and c =30. Or if you call sort(c,a,b), this should
 *		result in c=10, a=20 and b=30.
 *
 */

#include <iostream>
#include <climits>
#include <cstdio>	
#include <cstdlib>
#include <sstream>

#define DEBUG false	 // More or less verbose
#define MAX 5192
#define MIN -5192

// Reassign three int references to sort in ascending order
int sortInts(int &A, int &B, int &C);

// Confirm that a value grabbed from cin is a valid integer
int validateIntegerInput (int MinValue=INT_MIN, int MaxValue=INT_MAX, 
	int MaxNumberOfTries=0, const std::string Prompt="");

int main () 
{
	int a, b, c;

	std::cout << "This program will sort three integers in ascending order"
		<< std::endl << std::endl;

	a = validateIntegerInput(MIN, MAX, 3, "");
	b = validateIntegerInput(MIN, MAX, 3, "");
	c = validateIntegerInput(MIN, MAX, 3, "");

  std::cout << "You entered: " << a << " " << b << " " << c << std::endl;
  sortInts(a,b,c);
	std::cout << "Sorted:   " << a << " " << b << " " << c << std::endl;

}

/* ***************************************************************************
 * sortInts
 *
 * 		Purpose: Reassign integer arguments to sort them in ascending order
 * 		Input: Three int references
 * 		Returns: 0, but return value is not used.
 ****************************************************************************/
int sortInts(int &A, int &B, int &C)
{
	int tmp;

  // If the numbers are equal we don't do anything
	if ( C < B ) { tmp=C; C=B; B=tmp; }
	if ( B < A ) { tmp=B; B=A; A=tmp; }
	if ( C < B ) { tmp=C; C=B; B=tmp; }

  return(0); // return value is not used by anything
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
