/* vim:ts=2
 *
 * 			CS162, Lab3:  File I/O
 * 			Shoshana Abrass
 * 			abrasss@onid.oregonstate.edu
 * 			Jan 25, 2015
 *
 * Merge two files that each contains sorted integers
 * Write the results to a third file
 *
 * Input files should be read one line at a time.
 *
 * Design choices:
 * 	Silently supress duplicates
 * 	Silently supress blank lines 
 * 	Output numbers are CRLF separated even if input is not
 * 	Warn and continue if bad data is found
 * 	If one or both files are empty that's not an error; silently proceed
 * 	Command-line arguments are positional, not flag-defined
 * 	Decimal numbers with no value after the decimal point are converted to
 * 		integers.  For example, "13.0" will be treated as "13".
 * 		This is a design decision and not a bug.
 *
 * Tested scenarios:
 *  One or both files does not exist (program exits)
 *  File number ranges do not overlap, eg, one file is all lower than the other
 *  One or both files exists but not permitted to read; program exits
 *  One or both files exist but are empty; no error
 *  One file is much shorter than the other
 *  Input Numbers are either space delimited and CRLF delimited; both work
 *  Bad (non-integer) values exist (strings, decimal numbers); warn and skip
 *  Duplicate numbers occur in the same file
 *  Duplicate numbers are found in fileOne and fileTwo
 *  Swap input files one and two, output should be the same
 *  Negative numbers
 *  Very large positive numbers (< INT_MAX)
 *
 */
#include <fstream> 	// File I/O
#include <iostream>
#include <string>
#include <cstring>	// Because  strlen
#include <climits>  // INT_MAX, INT_MIN

#define DEBUG false

#define INPUT_FILE_ONE "infile.one" // must be a file of sorted integers
#define INPUT_FILE_TWO "infile.two" // must be a file of sorted integers
#define OUTPUT_FILE "outfile"

void SortTwoIntoOne(std::ifstream &inputStreamOne, 
	std::ifstream &inputStreamTwo, std::ofstream &outputStream);
void ReadOneInt(std::ifstream &Input, int ** Value, std::string Filename);
int validateIntegerInput(const char* inputString, int MinValue, int MaxValue);

/****************************************************************************
 * main()
 *
 * Check the command-line arguments (file names)
 *
 * Error and exit if the files are bad, otherwise run SortTwoIntoOne.
 *
 ***************************************************************************/

int main(int argc, char **argv) 
{
	/* We had command-line argument parsing here, but we got rid of that */
	/* See revision history at 
	 * https://github.com/Maker23/osu_classes/blob/6d30bb6dcb84087339e7bc7dbc73b0d7163cb523/cs162/FinishedLabs/Lab3/Lab3.cpp 
	 */


  // Declare and initialize input streams. 
	std::ifstream inputStreamOne(INPUT_FILE_ONE); // implicitly opens the input file
	std::ifstream inputStreamTwo(INPUT_FILE_TWO); // ditto
	int errorCount=0;

	// Test both input streams, make sure they're good 
	// before we open (and truncate) the output file.
	if (! inputStreamOne.good()) 
	{
		std::cout << "Error: Could not open file \""<< INPUT_FILE_ONE << "\" for read." <<std::endl;
		errorCount++;
	}
	if (! inputStreamTwo.good()) 
	{
		std::cout << "Error: Could not open file \""<< INPUT_FILE_TWO <<"\" for read."<<std::endl;
		errorCount++;
	}
	if (errorCount > 0 )
	{
		std::cout << "exiting...." << std::endl;
		exit(-1);
	}

  // Declare, initialize and test the output stream.
	std::ofstream outputStream(OUTPUT_FILE);  // implicitly opens the output file
	if (! outputStream.good()) 
	{
		std::cout << "Error: Could not open file \""<< OUTPUT_FILE <<"\" for write."<<std::endl;
		exit(-1);
	}

	// All good?  Run the useful function!
	SortTwoIntoOne(inputStreamOne, inputStreamTwo, outputStream);

	// Close the files. Extraneously.
	inputStreamOne.close();
	inputStreamTwo.close();
	outputStream.close();

}

/****************************************************************************
 * SortTwoIntoOne (inputStreamOne, inputStreamTwo, outputStream)
 *
 * Arguments:
 * 	inputStreamOne, inputStreamTwo:  std::ifstream
 * 	outputStream:  std::ofstream
 *
 * This function implements the sorting logic required by the assignment.
 * One integer at a time is read from the input files, and the results
 * are written to the outputStream in sorted order, with no buffering
 *
 ***************************************************************************/
void SortTwoIntoOne(std::ifstream &inputStreamOne, std::ifstream &inputStreamTwo, std::ofstream &outputStream)
{
	bool uniq = true; // set to false to allow duplicate integers
	int *inputOne = new (int);
	int *inputTwo = new (int);
	int *prevInputOne = new int (INT_MIN); 
	int *prevInputTwo = new int (INT_MIN);


	ReadOneInt(inputStreamOne, &inputOne, INPUT_FILE_ONE);
	ReadOneInt(inputStreamTwo, &inputTwo, INPUT_FILE_TWO);
	while ( inputOne && inputTwo )
	{
		// Good values from both files
		if ( *inputOne < *inputTwo) 
		{
			if (DEBUG) std::cout << "Writing inputOne, recycling One" 
				<< "	" << *inputOne << std::endl;
			if ( (!uniq)
			 	|| (uniq && (*inputOne != *prevInputOne)))
			{
				outputStream << *inputOne << std::endl;
				*prevInputOne = *inputOne;
			}
			ReadOneInt(inputStreamOne, &inputOne, INPUT_FILE_ONE);
		}
		else if (*inputOne > *inputTwo)
		{
			if (DEBUG) std::cout << "Writing inputTwo, recycling Two" 
				<< "	" << *inputTwo << std::endl;
			if ( (!uniq)
			 	|| (uniq && (*inputTwo != *prevInputTwo)))
			{
				outputStream << *inputTwo << std::endl;
				*prevInputTwo = *inputTwo;
			}
			ReadOneInt(inputStreamTwo, &inputTwo, INPUT_FILE_TWO);
		}
		else if (*inputOne == *inputTwo) 
		{
			if (DEBUG) std::cout << "Writing inputOne, recycling both" 
				<< "	" << *inputOne << std::endl
				<< "	" << *inputTwo << std::endl;
			if (! uniq)
			{
				outputStream << *inputOne << std::endl << *inputTwo << std::endl;
			}
			else if (( *inputOne != *prevInputOne) && (*inputTwo != *prevInputTwo))
			{
				// uniq is true
				outputStream << *inputOne << std::endl;
				*prevInputOne = *inputOne;
				*prevInputTwo = *inputTwo;
			}
			ReadOneInt(inputStreamOne, &inputOne, INPUT_FILE_ONE);
			ReadOneInt(inputStreamTwo, &inputTwo, INPUT_FILE_TWO);
		}
	}
	// Now one of both files are empty of integers

	// Both files are finished; nothing more to do
  if ( ! (inputOne || inputTwo) ) 
	{ 
	}
	// One file is finished
	else if ( ! inputOne )
	{
		// InputFileOne has no more valid numbers in it, just speed through File Two
		while ( inputTwo)
		{
			outputStream << *inputTwo << std::endl;
			ReadOneInt(inputStreamTwo, &inputTwo, INPUT_FILE_TWO);
		}
	}
	else if ( ! inputTwo )
	{
		// InputFileTwo has no more valid numbers in it, just speed through File One
		while ( inputOne)
		{
			outputStream << *inputOne << std::endl;
			ReadOneInt(inputStreamOne, &inputOne, INPUT_FILE_ONE);
		}
	}
}

/****************************************************************************
 * ReadOneInt (Input,  Value, Filename)
 *
 * Arguments: 
 * 	Input: is a reference to an input filestream. 
 * 		If it isn't good() the function exits.
 * 	Filename is the string name associated with Input, 
 * 		used for printing better error messages
 *
 * This function will perform repeated reads of whitespace-separated text
 * from the Input stream until a valid integer, or eof(), is found.
 *
 * Value is a pointer to a int*.  If this function succeeds in reading
 * an integer from the Input stream then **Value will be set to that integer.
 * Otherwise *Value will be set to NULL.  We use an int* because there's no
 * "illegal" value for testing an integer, but there is for a pointer.
 *
 ***************************************************************************/
void ReadOneInt(std::ifstream &Input, int ** Value, std::string Filename)
{
	if (DEBUG) std::cout << "Entering ReadOneInt" << std::endl;

	std::string Line;
	int tmpInt;

	if ( Input.eof() )
	{
		if (DEBUG) std::cout << "Setting the pointer to Null to indicate EOF" << std::endl;
		*Value = NULL;
		return;
	}
	else if ( Input.good() )
	{
		do
		{
	  	Input >> Line;
			tmpInt = validateIntegerInput(Line.c_str(), INT_MIN + 1, INT_MAX);
			if (tmpInt == INT_MIN)
			{
				// Skip silently unless we're debugging; 
				// a warning will be printed by the validate function
				if (DEBUG) 
				{
					std::cout << "Warning: bad input found in file " << Filename << std::endl;
			 		std::cout << "getline = \"" << Line << "\"" << std::endl;
					std::cout << "validate = \"" << tmpInt << "\"" << std::endl;
				}
			}
		  if (DEBUG) std::cout << "tmpInt = " << tmpInt << std::endl;
		}
		while ( Input.good() && tmpInt == INT_MIN);
		if (tmpInt != INT_MIN)
		{
			**Value = tmpInt;
			return;
		}
		else 
		{
			if (DEBUG) std::cout << "I think I'm setting the pointr to Null" << std::endl;
			*Value = NULL;
			return;
		}
	}
	else
	{
		std::cout << "ERROR: Can't read input from "<< Filename <<std::endl;
		*Value = NULL;
		return;
	}

	if (DEBUG) std::cout << "End of ReadOneInt - we should never get here" << std::endl;
}

#define ZERO 48
#define NINE 57
#define DASH 45
#define DOT 46
#define SPACE 32

/* ***************************************************************************
 *  validateIntegerInput (InputString, MinValue, MaxValue);
 *
 *  Purpose: Confirm that a string is a valid integer number
 *  Arguments: 
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
	const char* inputString,
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

	if (DEBUG) std::cout << "_validateIntegerInput function two" << std::endl;
	
	do {
	  number_of_tries++;

		// Confirm that all the character in the input string are legal 
		// as part of a number
		length_of_input = std::strlen(inputString);
		if (length_of_input == 0 ) 
		{
			if (DEBUG) std::cout << "Whoa nellie! no input??" << std::endl;
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
   		std::cout << "ERROR: Value " << inputInteger << " is outside permitted range ["
				<< MinValue << "-" << MaxValue << "]" << std::endl;
			return(MinValue-1);
		}
		else
		{
					return(inputInteger);
		}
		notANumber = false;  // reset
	}
	while ( !number_of_tries || (number_of_tries < MaxTries) );

	std::cout << "Warning: \"" << inputString << "\" is not an integer value; skipping..." <<std::endl;
	return(MinValue-1);	 // Hard to return an error code
}

