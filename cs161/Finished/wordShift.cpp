/* vim: ts=2
 *
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/11/02
 *  Last Modification date: 2014/11/09
 *  Filename: wordShift.cpp
 *
 *  Overview:
 *
 *		Write a program that asks the user for a C-style string and then allows
 *		the user to enter one of four commands.  
 *		=	“rev” should reverse the string.
 *		=	“Lx”, where x is some integer, should shift all the characters in the
 *					string left x spaces, with any characters that fall off the 
 *					beginning getting added on the end. For example, L3 would turn
 *					“hello world” into	“lo worldhel”. 
 *		=	“Rx”, where x is some integer, should shift all the characters in the
 *					string right x spaces, with any characters that fall off the end
 *					of the string getting added on the beginning. 
 *		=	“quit” should end the program.  Until the user enters “quit”, the
 *					program should loop, allowing the user to continue entering
 *					commands to manipulate the string and printing out the results of
 *					each command.
 *
 *		You should implement the first three commands in functions (be careful
 *		of the null terminator).	If the user enters a command string of the
 *		wrong format, you should print an error message and let them try again.
 *
 *		See examples below.
 */

#include <iostream>
#include <cstring>
#include <cstdlib>

#define MAX_STRING_LEN 256  // We'll truncate strings longer than this

// Menu item macros for code readability
#define REV 1				
#define LSHIFT 2
#define RSHIFT 3
#define QUIT 4

/* Function prototypes  */
// Collect a string of input from the user
std::string getUserString(int maxLen);
// Parse the command string entered by the user
int parseCommand(std::string command, int &cmdArgument);
// Shift the string left or right by some number of characters
int shiftString(char *myString, int shift);
// Reverse the string
int reverseString(char *myString);


int main () 
{
  std::string inputString;	// The initial word/phrase entered by the user
	std::string command;  		// The command string, entered by the user
	int stringLen=0;					// Length of string, max
	int nextAction=0;					// What command the user has chosen
	int cmdArgument=0;				// Argument to that command, if any
	char inputChars[MAX_STRING_LEN];  // A c-string, easier to manipulate

  // Get a word or phrase from user input
	inputString = getUserString(MAX_STRING_LEN);
  if (inputString.compare("") == 0 )
		return(-1);
	// Copy the c++ string into a c-string array.
	// Using strncpy and adding the null isn't necessary if the string
	// is shorter than MAX_LEN, but it isn't harmful either.
	std::strncpy(inputChars, inputString.c_str(), MAX_STRING_LEN - 1 );
	inputChars[MAX_STRING_LEN-1] = '\0';

  // Print the menu of options and enter a loop
	std::cout << "How do you want to tweak this phrase?" <<std::endl;
	do 
	{
		std::cout << "R#, L#, or rev: ";
  	getline(std::cin, command);
		nextAction = parseCommand(command, cmdArgument);
		switch(nextAction)
		{
			case REV:
				reverseString(inputChars);
				std::cout << "Reverse: " << inputChars << std::endl;
				break;
			case LSHIFT:
				shiftString(inputChars, cmdArgument);
				std::cout << "Left " << cmdArgument << ": " << inputChars << std::endl;
				break;
			case RSHIFT:
				shiftString(inputChars, -(cmdArgument));
				std::cout << "Right "<< cmdArgument << ": " << inputChars << std::endl;
				break;
			case QUIT:
				break;
			default:
				std::cout << "Didn't recognize that command, try again. (Type \"quit\" to quit)" << std::endl;
				break;
		}
	}
	while ( nextAction != QUIT ); 

}

/*****************************************************************
 * int parseCommand(std::string command, int &cmdArgument)
 *
 * 		Purpose: Reads the user-entered command line, checks whether
 * 						 it's valid, looks for an argument if there should
 * 						 be one
 * 		Takes:	 command (string), cmdArgument (int reference)
 * 		Returns: An integer corresponding to one of the valid commands
 * 						 or -1 if no valid command was found.
 * 						 cmdArgument is always updated.
 ****************************************************************/
int parseCommand(std::string command, int &cmdArgument)
{
	cmdArgument = 0; // reset each time

	// This is a bit tedious but it works
	if ((command.compare("Rev") == 0 ) ||(command.compare("rev") == 0 ))	// Reverse
		return(REV);
  else if ((command.compare("Quit") == 0) || (command.compare("quit") ==0))	// Quit
		return(QUIT);
  else if (command[0] == 'R' || command[0] == 'r') 	// Right shift
	{
		// Everything after the R or L should be an integer
		cmdArgument = atoi((char *)&(command[1]));
		if (cmdArgument > 0 )
			return(RSHIFT);
	  else
			std::cout << "'R' command requires a positive integer argument" <<std::endl;
	}
  else if (command[0] == 'L' || command[0] == 'l')		// Left shift
	{
		// Everything after the R or L should be an integer
		cmdArgument = atoi((char *)(&(command[1])));
		if (cmdArgument > 0 )
			return(LSHIFT);
	  else
			std::cout << "'L' command requires a positive integer argument" <<std::endl;
	}

  return(-1); // Failed to find a valid command
}

/*****************************************************************
 * int shiftString(char *myString, int shift)
 *
 * 		Purpose: Shifts all the characters in myString to the left 
 * 						 or right by "shift" positions. (negative shift 
 * 						 is used to move right)
 * 		Takes:	 myString (pointer to a char array), shift (int)
 * 		Returns: 0. myString is updated in-place.
 ****************************************************************/
int shiftString(char *myString, int shift)
{
	char tmpString[MAX_STRING_LEN];
  int len=0; 	// index, capture the length of the string
	int l=0; 		// a counter for string copying

  // Make a copy of the string, and count the characters
	while (myString[len] != '\0') 
	{
		tmpString[len] = myString[len];	
		len++;
	}
	len--; // the last character of the string is a null; drop it

	// Shifting right?  translate that into the appropriate left-shift
	if ( shift < 0 )
		shift = (len+1) + (shift % (len+1));
	
	for (l=0; l<=len; l++) 
	{
		myString[l] = tmpString [(l+shift) % (len+1)];
	}
	myString[l+1] = '\0'; // Put the null-terminator back

	return 0;
}

/*****************************************************************
 * int reverseString(char *myString)
 *
 * 		Purpose: Reverses myString
 * 		Takes:	 myString (pointer to a char array)
 * 		Returns: 0. myString is updated in-place.
 ****************************************************************/
int reverseString(char *myString)
{
	char tmpString[MAX_STRING_LEN];
  int len=0;
	int r=0;

  // Make a copy of the string, and count the characters
	while (myString[len] != '\0') 
	{
		tmpString[len] = myString[len];	
		len++;
	}
	len--; // drop the null terminator

	while ( len >= 0 )
	{
		// Reverse the letters
		myString[r++] = tmpString[len--];
	}
	myString[r] = '\0'; // Put the null-terminator back

	return 0;
}

/*****************************************************************
 * std::string getUserString(int maxLen);
 *
 * 		Purpose: Reverses myString
 * 		Takes:	 myString (pointer to a char array)
 * 		Returns: 0. myString is updated in-place.
 ****************************************************************/
std::string getUserString(int maxLen)
{
	int stringLen=0;
	std::string inputString;

  // Get a word or phrase from user input
  std::cout << "Enter a word or a phrase to randomize: ";
  getline(std::cin, inputString);
	stringLen = inputString.length();
	if (stringLen == 0 ) {
		std::cout << "Didn't get a word or phrase. Exiting..."
			<< std::endl;
		return("");
	}
	else if (stringLen > (maxLen - 1)) 
	{
		std::cout << "String exceeds maximum length of " << maxLen - 1
			<< " characters. It will be truncated." << std::endl;
	}
	return(inputString);
}
/*		For example:
 *
 *			Please enter a string.
 *			perpendicular
 *			Please enter a command.
 *			L5
 *			New string: ndicularperpe
 *			Please enter a command.
 *			rev
 *			New string: eprepralucidn
 *			Please enter a command.
 *			F6
 *			Invalid command.
 *			Your string is: eprepralucidn
 *			Please enter a command.
 *			R21
 *			New string: ralucidneprep
 *			Please enter a command.
 *			rev
 *			New string: perpendicular
 *			quit
 *
 */
