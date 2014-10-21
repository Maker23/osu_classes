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
#define MAXIMUM_MIDDLE_NAMES 5	// Let's be reasonable



int main () 
{
	std::string inputString = "";	// What the user types in
	std::string fullName = "";		// A cleaned-up version for parsing
	std::string firstName = "";		// User's first name
	std::string middleName = "";	// User's middle names. If there are multiple
																// middle names they all end up in this string,
																// concatenated with spaces between them.
	std::string lastName = "";		// User's last name
	char middleInitials[MAXIMUM_MIDDLE_NAMES];	// Middle initials
	int numInitials;			// How many middle initials there are
	int middleNameStart;	// Location in fullName where middle names start
	int lastNameStart;		// Location in fullName where the last name starts
	int i;								// Used for counting

	std::cout << "Please enter your full name (First Middle Last): ";

	// ************************************************************
	// Strip any trailing spaces to simplify the parser
	// cin already strips leading spaces
	std::getline(std::cin, inputString);
	i = inputString.length();
	while (inputString.at(i-1) == SPACE ) { i--; }
	fullName = inputString.substr(0,i);
	
	// ************************************************************
	// Parse the full name, extracting First, Last and Middle(s)
	for (i=0; i < fullName.length(); i++)
	{
		// space is our delimiter between names
		if(fullName.at(i) == SPACE ) {
			// Since we stripped all the trailing spaces, we know we are now
			// at the end of a word
			if ( firstName == "" )
			{
				// The first word of the string as the first name.
				firstName = fullName.substr(0,i); 
				middleNameStart = i+1; 
				// Note i+1 could be a bad reference, but we don't end up using it
				// if i is the end of the string.
			}
			else
			{
				middleName = fullName.substr(middleNameStart, i - middleNameStart);
				// Note that middleNameStart is always the beginning of the
				// second word. As we find more middle names we simply extend
				// the string.
			}
		}
		else if(	(fullName.at(i) <65)
						||(fullName.at(i) >=91 && fullName.at(i) <=96)
						||(fullName.at(i) > 122)
					 )
		{
			// non-letter character is a warning, not an error
			std::cout << "warning: encountered non-letter character \'" 
				<< fullName.at(i) << "\'" << std::endl;
		}
	}

	// ************************************************************
	// lastName is one of:
	// 	The last word, if three or more words were entered
	// 	The second word, if two words were entered
	// 	The first word, if only one word was entered
	//
	// TODO: Deal with the special cases "Jr.", "Sr.", "III", etc
	// 			 But we won't have time for this assignment
	//
	lastNameStart = (firstName.length()? firstName.length() + 1: 0) 
		+ (middleName.length()?middleName.length() +1: 0);
	if (lastNameStart >= i) {
		// Field ended on a blank.  Halp! All trailing blanks should have been stripped
		if (DEBUG) std::cout << "This should never happen" << std::endl;
		return 1;
	}
	else {
		lastName = fullName.substr(lastNameStart, i - lastNameStart);
	}

	if (DEBUG) std::cout << "first name is ->" << firstName 
		<< "<-  middle name is  ->" << middleName << "<-" << std::endl
		<< "last name is ->" << lastName << "<-" << std::endl;

	// ************************************************************
	// Parse the Middle name, extracting initials
	// TODO: find a way to incorporate this into the main loop if we have time.
	if (middleName.length() > 0 ) 
	{
		middleInitials[numInitials++] = middleName.at(0);
  	for (i=1; i< middleName.length(); i++) 
		{
			if((middleName.at(i) == SPACE ) && middleName.at(i+1)) 
			{
				middleInitials[numInitials++] = middleName.at(i+1);
				if (DEBUG) 
					std::cout << "Initial " << i << " equals " 
						<< middleInitials[i] << std::endl;
			}
		}
	}


	// ************************************************************
	// Pretty print
	std::cout << lastName << ", ";
	if ( firstName != "" )
	{
		std::cout << firstName;
		for (i = 0; i < numInitials; i++)
		{
			// TODO: test for more than MAX middle names
			std::cout << " " << middleInitials[i] << ".";
		}
	}
	else {
		std::cout << "<none>";
	}
	std::cout << std::endl;
}
