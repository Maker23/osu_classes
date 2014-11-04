/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/10/27
 *  Last Modification date: 2014/11/02
 *  Filename: recConvert.cpp
 *
 *  Overview:
 *		Your main function will allow the user to choose between
 *			1) converting a binary number to a decimal number;
 *			2) converting a decimal number to a binary number; or
 *			3) exiting the program. 
 *		This menu should be in a loop so the user can convert as many numbers as
 *		they wish before exiting. When the user selects either of the first two
 *		options, your program will ask the user for a number to convert. It
 *		should first check to make sure the input is valid, then call a function
 *		that returns the desired value, and then print it for the user (the
 *		printing happens in main, not the conversion functions). 
 *
 *		Both conversion functions must be recursive. Represent binary numbers as
 *		string values. Do not use any number base conversion functionality that
 *		is built into C++.
 *
 *		Checking for a valid binary number should be simple, since there are only
 *		two allowable characters. One way of validating values that aren't strings
 *		is to read them in as strings anyway, check to make sure the characters
 *		form a valid input, and then convert the string value to another type.
 *
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <climits>
#include <cstdio>
#include <sstream>

#define DEBUG false	 // More or less verbose

/* ***************************************************************************
 * Function prototypes
 ****************************************************************************/
// Convert a decimal number to a binary string
std::string convertDecToBinary(long myInt);

// Convert a binary string to a decimal number
long convertBinaryToDec(std::string myBin);

// Take one line of input from the user, confirm it is an integer number.
long validateIntegerInput (long MinValue=LONG_MIN+1, long MaxValue=LONG_MAX-1, 
	int MaxNumberOfTries=0, const std::string Prompt="");

// Take one line of input from the user, confirm it is a binary string. 
std::string validateBinaryInput ();

/* ***************************************************************************
 * main
 *
 * 		Runs an infinite loop asking the user to choose binary or decimal 
 * 		conversion,	or enter 'X' to exit
 ****************************************************************************/
int main () 
{
	int ch;					// top-level menu choice
	long myInt = 0; // integer representation
	std::string myBin = "";  // binary representation
	std::string toss; // throw away extra input from cin

  std::cout << 
		"This program will convert binary numbers to decimals, " << std::endl <<
		"and decimal numbers to binary.  For example, " << std::endl <<
		"   b 10111  -> 23" << std::endl <<
		"   d   25   -> 11001" << std::endl << std::endl  <<
  	"Enter 'b' to convert a binary, 'd' to convert decimal, or 'x' to exit" <<
		std::endl;

	while ( 1 )
	{
  	std::cout << "[bdx]: ";

  	ch = std::cin.get(); 
		getline(std::cin, toss);
		switch (ch){
			case 'b':
			case 'B':
				std::cout << "Found b" << std::endl;
				myBin = validateBinaryInput ();
				if ( myBin == "" ) 
				{
					std::cout << "\ttry again" << std::endl;
				}
				else
				{
					myInt = convertBinaryToDec(myBin);
					std::cout << "\t" << myBin << " -> " << myInt << std::endl;
				}
				break;
			case 'd':
			case 'D':
				std::cout << "Found d" << std::endl;
				myInt = validateIntegerInput (0, LONG_MAX-1, 1, "");
				if ( myInt < 0 )
				{
					std::cout << "\ttry again" << std::endl;
				}
				else
				{
  				myBin = convertDecToBinary( myInt );
					std::cout << "\t" << myInt << " -> " << myBin << std::endl;
				}
				break;
			case 'x':
			case 'X':
				std::cout << "Exiting..." << std::endl;
				return(1);
			default:
				std::cout << "Error, not 'b' or 'd'" << std::endl;
		}
	}
}

/* ***************************************************************************
 * convertDecToBinary
 *
 * 		Purpose: Convert a non-negative integer to a binary string
 * 		Input: A long integer
 * 		Returns: A binary string of the form 10011
 ****************************************************************************/
std::string convertDecToBinary(long myInt)
{
	if (myInt < 0) {
		// This should not happen if we validate our inputs properly
	  std::cout << "\tERROR: can't convert a negative int to a binary"
			<< std::endl;
		return("");
	}
	if (myInt == 0) 
	{
		return("0");
	}
	else if (myInt == 1) 
	{
		return("1");
	}
	else if ((myInt % 2) == 0 )
	{
		return ( convertDecToBinary(myInt/2) + "0" );
	}
	else if ((myInt % 2) == 1)
	{
		return ( convertDecToBinary(myInt/2) + "1" );
	}
}

/* ***************************************************************************
 * convertBinaryToDec
 *
 * 		Purpose: Convert a binary string to a positive integer
 * 		Input:  A binary string of the form 10011 (63 bits max)
 * 		Returns: A long integer
 ****************************************************************************/
long convertBinaryToDec(std::string myBin)
{
	long tmpInt = 0;
	int twosFactor=0;

  if (myBin.length() <= 0)  // Should not need this if input is validated
	{
		return 0;
	}

	twosFactor  = myBin.length() - 1;
	tmpInt  = (exp2(twosFactor) * (myBin.at(0) == '1' ? 1 : 0 ));

	if (twosFactor ) 
	{
		return tmpInt + convertBinaryToDec(myBin.substr(1,twosFactor));
	}
	else {
		return tmpInt;
  }
}

/* ***************************************************************************
 * validateBinaryInput
 *
 * 		Purpose: Confirm a string grabbed from cin is a binary
 * 		Input:  no arguments
 * 		Returns: A string: binary if valid; an empty string if not
 ****************************************************************************/
std::string validateBinaryInput ()
{
	int len = 0;
	char c = NULL;
	std::string inputString = "";

	std::cout <<  "\tEnter a binary number: ";
	std::getline(std::cin,inputString);
	len = inputString.length();
	if ( len > 63 ) {
		std::cout << "Sorry, only 63 bits allowed." << std::endl;
		return ("");
	}
	for (int i=0; i < len ; i++) 
	{
		c = inputString.at(i);
		// Digits [0-9], negative signs, and decimal points are ok
		if(! (( c == '1') || (c == '0' )))
		{
			// This is not a binary string
			// TODO: Support Octal, binary, and Hex
			std::cout << "\tERROR: non-binary character " << c 
				<< " found. " << std::endl;
			return ("");
		}
	}
	return(inputString);
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

long validateIntegerInput(
	long MinValue,
	long MaxValue,
	int MaxTries,
	std::string Prompt)
{
  std::string inputString;		// Users's input from the terminal
	long inputDouble = 0.0; 	// The input string, as a double
	long  inputInteger = 0;			// The input string, as an integer
	int  length_of_input = 0;		// Length of the users's input string
	int  number_of_tries = 0;		// Number of times user has tried to enter data
	char buffer[256];						// A buffer for creating the prompt string
	bool notANumber = false;

	if ( Prompt == "" )
	{
		sprintf(buffer, "\tEnter an integer between %Lu and %Lu: ", MinValue, MaxValue);
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
		if (DEBUG  && ss ) std::cout << "stringstream (double) may have an error" << std::endl;
		if (DEBUG) std::cout << "inputDouble = " << inputDouble << ", inputInteger = " 
			<< inputInteger << std::endl;

		if ( notANumber )
		{
			std::cout << "\tERROR: Part of your input was not a number\n";
			// TODO 'non-numeric character X found'
		}
		else if ( inputDouble != static_cast<double>(inputInteger) )
		{
				// Number is a float with a fractional part
				// TODO: this is subject to the accuracy limits of the double, 
				// for example, 10.0000000000000001  is equal to 10.
				// We could instead warn when a decimal point is detected...
				std::cout << "\tERROR: Number contained a decimal value\n";
		}
	  else if ( (inputInteger < MinValue ) || (inputInteger > MaxValue) ) 
		{
 			if ( DEBUG ) {std::cout << "Numeric value l.181 = " << inputInteger 
				<< "num_tries = " << number_of_tries << "\n";}
   		std::cout << "\tERROR: Value is outside permitted range.\n";
		}
		else
		{
					return(inputInteger);

		}
		notANumber = false;  // reset
	}
	while ( !number_of_tries || (number_of_tries < MaxTries) );

	return(-1);

}
