/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/10/13
 *  Last Modification date: 2014/10/19
 *  Filename:  name.cpp
 *
 *  Overview:
 *		“Write a program that reads a person’s name in the following format: 
 *		first name, then middle name or initial, and then last name. The program 
 *		then outputs the name in the following format: 
 *		Last_Name, First_Name, Middle_Initial.
 *		For example, the input Mary Average User should produce the output
 *		User, Mary A.
 *		The input Mary A. User should also produce the output 
 *		User, Mary A.
 *		Your program should place a period after the middle initial even if the 
 *		input did not contain a period. Your program should allow for users who
 *		give no middle name or middle initial. In that case, the output, of 
 *		course, contains no middle name or initial. For example, the input
 *		Mary User
 *		should produce the output
 *		User, Mary
 *		If you are using C-strings, assume that each name is at most 20 chars 
 *		long. Alternatively, use the class string. (Hint: You may want to use 
 *		three string variables rather than one large string variable for the 
 *		input. You may find it easier to not use getline.)”
 *		(hint: I personally still find it easier to use getline...)
 *
 *  Input:  
 *  	The user's full name,  "First Middle [Middle] Last" (or "First Last")
 *
 *  Output:
 *    The name in standardized form, "Last, First M. [M.]"
 *
 */

#include <iostream>
#include <string>

#define DEBUG false
#define SPACE 32  	// The ASCII value of the space character, our delimiter
#define MAXIMUM_NAMES 30	// Let's be reasonable



int main () 
{
	std::string inputString = "";	// What the user types in
	std::string fullName = "";		// A cleaned-up version for parsing
	std::string firstName = "";		// User's first name
	std::string lastName = "";		// User's last name
	int  i = 0;										// Used for counting
	int wordStart = 0;						// position in string of a word start			
	char lastChar = NULL;					// the last character we read from the string
	char thisChar = NULL;					// the current character read from the string
	std::string Name[MAXIMUM_NAMES];	  // Store all names separately
	std::string middleInitial[MAXIMUM_NAMES];	 // Store middle initials
	int numNames = 0;							// How many names there are
	int numInitials = 0;					// How many middle initials there are

	std::cout << "Please enter your full name (First Middle Last): ";

	std::getline(std::cin, inputString);
	i = inputString.length();
	if ( i == 0 ) {
		std::cout << "ERROR: empty string" << std::endl;
		return 1;
		// or we could retry. But we don't.
	}
	// ************************************************************
	// Strip any trailing spaces to simplify the parser
	// cin already strips leading spaces
	while (inputString.at(i-1) == SPACE ) { i--; }
	// TODO: check if we can get away without a temp variable here
	fullName = inputString.substr(0,i);
	
	// ************************************************************
	// Parse the full name, extracting all the individual words
	for (i=0; i < fullName.length(); i++)
	{
		thisChar = fullName.at(i);
		if((thisChar == SPACE) && (lastChar == SPACE)) 
		{
			// ignore multiple spaces
			// space is our delimiter between names
		}
		else if((thisChar == SPACE) && (lastChar != SPACE)) 
		{
			// Since we stripped all the trailing spaces, we know we are now
			// at the end of a word
			Name[numNames++] = fullName.substr(wordStart,i-wordStart); 
		}
		else if ((thisChar != SPACE) && (lastChar == SPACE))
		{
			wordStart = i;
		}
		if( (	thisChar < 65 && thisChar != SPACE)
						||(thisChar >=91 && thisChar <=96)
						||(thisChar > 122)
					 )
		{
			// non-letter character is a warning, not an error
			// Because ... weird names
			std::cout << "warning: encountered non-letter character \'" 
				<< fullName.at(i) << "\'" << std::endl;
		}
		lastChar = thisChar;
		// TODO: test for more than MAX names
	}
	Name[numNames++] = fullName.substr(wordStart,i-wordStart); 

  if (DEBUG) 
		for (i=0; i<numNames; i++) {
			std::cout << "Name # " << i << " = " << Name[i] << std::endl;
		}
	// ************************************************************
	// Depending on the number of names entered, find the lastName
	// and any firstNames and middle initials

  if (numNames > 0 ) 
	{
		lastName = Name[numNames-1];
		if (numNames > 1)
			firstName = Name[0];
		for (i=1; i < (numNames - 1); i++ )
			middleInitial[numInitials++] = (Name[i]).substr(0,1);
	}
	else 
	{
		// This should never happen
		std::cout << "Fatal error: no names found in string ->" << fullName << "<-" << std::endl;
		return 1;
	}

	// ************************************************************
	// Pretty print
	std::cout << lastName << ", ";
	if ( firstName != "" )
	{
		std::cout << firstName;
		for (i = 0; i < numInitials; i++)
		{
			std::cout << " " << middleInitial[i] << ".";
		}
	}
	else {
		std::cout << "<none>";
	}
	std::cout << std::endl;
}
