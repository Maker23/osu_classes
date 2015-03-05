/* vim: ts=2
 *
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2015/01/01
 *  Assignment:  Lab9
 *
 *  Overview:
 *
 *
 */
#include <stdexcept>
#include <climits>

#define DEBUG false
#include "Stack.h"
#include "Queue.h"

#define SPACE 32
#define COMMA 44

// Prototypes
void IntegerQueueTests(myQueue<int> &IntQueue, std::string Input);
void IntegerStackTests(myStack<int> &IntStack, std::string Input);
void StringStackTests(myStack<std::string> &StrStack, std::string Input);
void getAnInteger(std::string Input, int* value, int *stringPosition);
void getAWord(std::string Input, std::string* value, int *stringPosition);
std::string getInputFromUser(std::string TypeWanted);

//  Main
int main()
{
	std::cout << std::endl;
  std::string userInput = getInputFromUser("integer values");
	std::cout << "Bonus template round!" << std::endl;
  std::string userInputTwo = getInputFromUser("words (text strings)");

	myStack<int> IntStack;
	IntegerStackTests(IntStack, userInput);

	myQueue<int> IntQueue;
  IntegerQueueTests(IntQueue, userInput);

	myStack<std::string> StrStack;
	StringStackTests(StrStack, userInputTwo);

}

/* *********************************************************
 * IntegerStackTests (&Stack, string)
 *
 * Parse the given string into integers, 
 * pop those integers onto the stack and then remove them.
 * *********************************************************/
void IntegerStackTests(myStack<int> &IntStack, std::string Input)
{
	bool endOfInput = false;
	int tmpInt=0;
	int inputPosition=0;

	std::cout 
		<< "Testing myStack<int>  =======================" << std::endl;
  if (DEBUG) std::cout << "USER INPUT = " << Input;

	while(! endOfInput)
	{
		try
		{
			getAnInteger(Input, &tmpInt, &inputPosition);
			std::cout << "Pushing " << tmpInt << " onto stack" << std::endl;
			IntStack.push(tmpInt);
		}
		catch (std::invalid_argument &e) 
			{ std::cout << e.what() << std::endl;	}
		catch (std::out_of_range &o)
			{ endOfInput = true; }
	}

	while ( ! IntStack.isEmpty() )
	{
		std::cout << "Peeking: " << IntStack.peek();
		std::cout << "     Popping." << std::endl;
		IntStack.pop();
	}

	// Test the exception cases
	std::cout << std::endl<< "Peeking should fail: ";
	try {IntStack.peek();}
	catch (std::logic_error &e) 
		{ std::cout << e.what() << std::endl; }
	std::cout << "Popping should fail: ";
	try {IntStack.pop();}
	catch (std::logic_error &e) 
		{ std::cout << e.what() << std::endl; }

	std::cout << std::endl
		<< "Testing myStack<int> complete  ==============" << std::endl;
}
/* *********************************************************
 * StringStackTests (&Stack, string)
 *
 * Parse the given string into integers, 
 * pop those integers onto the stack and then remove them.
 * *********************************************************/
void StringStackTests(myStack<std::string> &StrStack, std::string Input)
{
	std::string tmpWord;
	int inputPosition=0;

	std::cout
		<< "Testing myStack<std::string>  ===============" << std::endl;
  if (DEBUG) std::cout << "USER INPUT = " << Input;

	getAWord(Input, &tmpWord, &inputPosition);
  while (tmpWord.compare("") != 0)
	{
		std::cout << "Pushing " << tmpWord << " onto stack" << std::endl;
		StrStack.push(tmpWord);
		getAWord(Input, &tmpWord, &inputPosition);
	}

	while ( ! StrStack.isEmpty() )
	{
		std::cout << "Peeking: " << StrStack.peek();
		std::cout << "     Popping." << std::endl;
		StrStack.pop();
	}

  // Test the exception cases
	std::cout << std::endl<< "Peeking should fail: ";
	try { StrStack.peek(); }
	catch (std::logic_error &e) 
		{ std::cout << e.what() << std::endl; }
	std::cout << "Popping should fail: ";
	try { StrStack.pop(); }
	catch (std::logic_error &e) 
		{ std::cout << e.what() << std::endl; }

	std::cout << std::endl
		<< "Testing myStack<std::string> complete  ======" << std::endl;
}

/* *********************************************************
 * IntegerQueueTests (&Queue, string)
 *
 * Parse the given string into integers, 
 * add those integers to the queue and then remove them.
 * *********************************************************/
void IntegerQueueTests(myQueue<int> &IntQueue, std::string Input)
{
	bool endOfInput = false;
	int tmpInt;
	int inputPosition=0; // Char position in the input string

	std::cout
		<< "Testing myQueue<int>  =======================" << std::endl;
  if (DEBUG) std::cout << "USER INPUT = " << Input;

	while(!endOfInput)
	{
		try
		{
			getAnInteger(Input, &tmpInt, &inputPosition);
			std::cout << "Adding " << tmpInt << " to the back of the queue" << std::endl;
			IntQueue.addBack(tmpInt);
		}
		catch (std::invalid_argument &e) 
			{ std::cout << e.what() << std::endl;	}
		catch (std::out_of_range &o)
			{ endOfInput = true;}
	}

	while ( ! IntQueue.isEmpty() )
	{
		std::cout << "getFront: " << IntQueue.getFront();
		std::cout << "     RemoveFront" << std::endl;
		IntQueue.removeFront();
	}

  // Test the exception cases
	std::cout << std::endl << "getFront should fail: ";
	try {IntQueue.getFront();}
	catch (std::logic_error &e) 
		{ std::cout << e.what() << std::endl; }
	std::cout << "removeFront should fail: ";
	try {IntQueue.removeFront();}
	catch (std::logic_error &e) 
		{ std::cout << e.what() << std::endl; }

	std::cout << std::endl
		<< "Testing myQueue<int> complete  ==============" << std::endl;
}

/* *********************************************************
 *
 *
 *
 * *********************************************************/
std::string getInputFromUser(std::string TypeWanted)
{
	std::string inputLine="";
	std::string allLines="";

	std::cout << "Input " << TypeWanted << " for the test." << std::endl 
		<< "Separate the values with spaces or commas: ";
	std::getline(std::cin, inputLine);
	return inputLine + ",";
}


/* *********************************************************
 *
 *	getAnInteger (string Input, int* value, int* stringPosition)
 *
 *	Input: A string, hopefully of space- and comma-separated integers
 *	int*  : This integer will hold the return value
 *	int*  : This integer tracks our position in the string.
 *	      
 * *********************************************************/
void getAnInteger(std::string Input, int* value, int *stringPosition)
{
	int inputLength = Input.length();
	int wordLetter = 0;
	int tmpInteger;
	char inputWord[256];
	std::string::size_type sz;
	std::string eString;

	for ( ; (*stringPosition) < inputLength; (*stringPosition)++)
	{
		if (Input[*stringPosition] == SPACE || Input[*stringPosition] == COMMA )
		{
			if ( wordLetter !=0 )
			{
				inputWord[wordLetter] = NULL; 
				try {
					tmpInteger = std::stoi(inputWord, &sz);
					*value = tmpInteger;
					return;
				}
				catch(const std::invalid_argument& ia)
				{
					eString = (std::string) inputWord + " is not a valid integer";
					throw std::invalid_argument(eString);
					//*value = 0;	
					return;
				}
			}
			wordLetter = 0; // Begin a new "word"
		}
		else
		{
			inputWord[wordLetter++] = Input[*stringPosition];
		}
	}
	throw std::out_of_range("eof");
}

/* *********************************************************
 *
 *	getAWord (string Input, string* value, int* stringPosition)
 *
 *	Input: A string, hopefully of space- and comma-separated integers
 *	string* : This string will hold the return value
 *	int*    : This integer tracks our position in the string.
 *	      
 * *********************************************************/
void getAWord(std::string Input, std::string* value, int *stringPosition)
{
	int inputLength = Input.length();
	int wordLetter = 0;
	char inputWord[256];

	for ( ; (*stringPosition) < inputLength; (*stringPosition)++)
	{
		if (Input[*stringPosition] == SPACE || Input[*stringPosition] == COMMA )
		{
			if ( wordLetter !=0 )
			{
				inputWord[wordLetter] = NULL; 
				*value = inputWord;
				return;
			}
			wordLetter = 0; // Begin a new word
		}
		else
		{
			inputWord[wordLetter++] = Input[*stringPosition];
		}
	}
	*value = "";
}
