#include <climits>
#include <cstdio>		// Because sprintf
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <time.h>

#ifndef DEBUG
#define LIB_DEBUG false	 // More or less verbose
#else
#define LIB_DEBUG DEBUG	
#endif

#define ZERO 48
#define NINE 57
#define DASH 45
#define DOT 46
#define SPACE 32


/* Take one line of input from the user, confirm it is an integer number. */
int validateIntegerInput (int MinValue=INT_MIN+1, int MaxValue=INT_MAX, 
	int MaxNumberOfTries=0, const std::string Prompt="");

/* Take a string argument, confirm it is an integer number */
int validateIntegerInput(char *inputString, int MinValue, int MaxValue);



/***************************************************************************** 
 * TODO: refactor the two definitions of validateIntegerInput
 *       to eliminate code redundancy
 *****************************************************************************/

/* ***************************************************************************
 *  validateIntegerInput (MinValue, MaxValue, MaxNumberOfTries, Prompt);
 *
 *  Purpose: Reads a value from cin, confirm it is an integer
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

	if (LIB_DEBUG) std::cout << "_validateIntegerInput function one" << std::endl;
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
			// This should never happen, because of the way getline works :)
		}
		for (int i=0; i < length_of_input; i++) 
		{
			// Digits [0-9], negative signs, and decimal points are ok
			if(!( ((inputString.at(i) >= ZERO) && (inputString.at(i) <= NINE ))
						|| ( i == 0 && inputString.at(i)==DASH)
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
		//std::stringstream ss (inputCopy); // stringstream is not allowed
		//ss >> inputDouble;
		inputDouble = (double)atof(inputString.c_str());
		inputInteger = inputDouble;
		if (LIB_DEBUG) std::cout << "inputDouble = " << inputDouble << ", inputInteger = " 
			<< inputInteger << std::endl;

		if ( notANumber )
		{
			std::cout << "ERROR: Part of your input was not a number." << std::endl;
			if (number_of_tries < MaxTries)
				std::cout << "Try again: ";
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
 			if ( LIB_DEBUG ) {std::cout << "Numeric value l.110 = " << inputInteger 
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
	
	if (MinValue > INT_MIN)
	{
		return (MinValue - 1); // Return an illegal value to signal a parsing error
	}
	else
	{
		exit(1);	 // Hard to return an error code.
	}

}

/* ***************************************************************************
 *  validateIntegerInput (InputString, MinValue, MaxValue);
 *
 *  Purpose: Confirm that a string is a valid integer number
 *  Input: 
 *  	InputString:  char* c-string
 *  	MinValue: the low end of the valid number range
 *  	Maxvalue: the high end of the valid number range
 *
 *  Note that acceptable integers
 *  	* Can begin with a minus sign (negative)
 *  	* Can not have any characters other than [0-9] and "."
 *  		* If "." appears, test the string as a float. It may be a number.00;
 *  		  this is accepted as an integer by this function (eg, 43.0,  109.00)
 *
 * ***************************************************************************/

int validateIntegerInput(
	char* inputString,
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
	//std::string inputCopy;

	if (LIB_DEBUG) std::cout << "_validateIntegerInput function two" << std::endl;
	
	do {
	  number_of_tries++;

		// Confirm that all the character in the input string are legal 
		// as part of a number
		length_of_input = std::strlen(inputString);
		if (length_of_input == 0 ) 
		{
			//std::cout << "Whoa nellie! no input??" << std::endl;
			return(MinValue-1);
		}
		for (int i=0; i < length_of_input; i++) 
		{
			// Digits [0-9], negative signs, and decimal points are ok
			// We should really strip spaces
			if(!( ((inputString[i] >= ZERO) && (inputString[i] <= NINE ))
						|| ( i == 0 && inputString[i]==DASH)
						|| ( i == 0 && inputString[i]==SPACE)
						|| ( i == length_of_input - 1 && inputString[i]==SPACE)
						|| ( inputString[i] == DOT )
					))
			{
				// THIS IS NOT A NUMBER
				// TODO: Support Octal, binary, and Hex
				notANumber = true;
			}
		}

		// Now that we know the string is a number, convert it to a double
		// Copy the double into an integer; then test if they are equal
		//inputCopy = inputString;
		//std::stringstream ss (inputCopy); // stringstream is not allowed
		//ss >> inputDouble;
		inputDouble = (double)atof(inputString);
		inputInteger = inputDouble; // if inputDouble is a floating point value,
		                            // inputInteger will be truncated
																// and the will not be equal when tested below
		if (LIB_DEBUG) std::cout << "inputDouble = " << inputDouble << ", inputInteger = " 
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
 			if ( LIB_DEBUG ) {std::cout << "Numeric value l.181 = " << inputInteger 
				<< "num_tries = " << number_of_tries << "\n";}
   		std::cout << "ERROR: Value " << inputInteger << " is outside permitted range.\n";
			return(MinValue-1);
		}
		else
		{
					return(inputInteger);
		}
		notANumber = false;  // reset
	}
	while ( !number_of_tries || (number_of_tries < MaxTries) );

	std::cout << inputString << " is not an integer value." <<std::endl;
	return(MinValue-1);	 // Hard to return an error code
}

/* ***************************************************************************
 * getIntegerInput
 *
 * 		Purpose: Take an arbitrary number of numbers, confirm they're integers,
 * 						 put them into an array.
 * 	  Takes: 	 A pointer to an array of integers; an integer arrayLen
 * 		Returns: False for bad data, True for good data
 *
 *    Note:    non-integer numbers are skipped, the function keeps going
 *
 *****************************************************************************/
#define SPC 32
#define COM 44
bool getIntegerInput(int *intArray, int arrayLen, int minInt, int maxInt,std::string Prompt)
{
	int inputLetter=0;
	int inputInt=0;
	int wordCount=0;
	char inputWord[256];
	int  wordLetter=0;
	std::string inputLine = "";
	std::string inputString = "";

	if (LIB_DEBUG) std::cout << "_validateIntegerInput function three" << std::endl;
	// Get input from the user
  if ( Prompt.compare(""))
  	std::cout << "Enter " << arrayLen 
		<< " integer values separated by commas or spaces: ";
	std::getline(std::cin,inputString);
	inputString += ",";
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
	if (LIB_DEBUG) std::cout << "Word count is " << wordCount << std::endl;

  if ( wordCount != arrayLen )
	{
		std::cout << "ERROR: was expecting " << arrayLen << " array elements, got " 
			<< wordCount << std::endl;
		return(false);
	}

  wordCount=0;
	// Now check whether each value is an integer in the right range
	for (inputLetter=0; inputLetter < inputLen; inputLetter++)
	{
		if  (inputString[inputLetter] == SPC || inputString[inputLetter] == COM )
		{
			if (wordLetter != 0)
			{
				inputWord[wordLetter] = NULL;
				inputInt = validateIntegerInput(inputWord,minInt,maxInt);
				if ( inputInt >=minInt )
				{
					intArray[wordCount] = inputInt;
					wordCount++;
				}
			}
			wordLetter=0;
		}
    else
		{
			inputWord[wordLetter++] = inputString[inputLetter];
		}
	}
  if ( wordCount != arrayLen )
	{
		return(false);
	}
	else
	{
  	return(true);
	}
}
bool getIntegerInput(int *intArray, int arrayLen, int minInt, int maxInt)
{
	if (LIB_DEBUG) std::cout << "_validateIntegerInput function four" << std::endl;
	return (getIntegerInput(intArray, arrayLen, minInt, maxInt, ""));
}
bool getSmallIntegerInput(int *intArray, int arrayLen)
{
	if (LIB_DEBUG) std::cout << "_validateIntegerInput function five" << std::endl;
	return (getIntegerInput(intArray, arrayLen, 1, 100, " "));
}
