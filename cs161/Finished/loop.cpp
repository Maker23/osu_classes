/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/10/13
 *  Last Modification date: 2014/10/19
 *  Filename: loop.cpp
 *
 *  Overview:
 * 		Write a piece of code using a loop that accepts two strings 
 * 		and returns whether they have the same contents with the 
 * 		use of a loop to check each character individually,
 *		File must be called: loop.cpp 	(hint: you can compare individual 
 *		characters with the <, ==, and > operators)
 *
 *  Input:
 * 		Two strings from the user
 *
 *  Output:
 *		An error if the two strings are different from each other,
 *		Otherwise a message that the strings are identical
 */

#include <iostream>
#include <string>

#define DEBUG false	 // More or less verbose

int main () 
{
	// The error string
	const std::string errorString = "Those two strings are not identical";
	std::string myStringOne; 	// First string input by the user
	std::string myStringTwo; 	// Second string input by the user
	int len;									// The length of the first string
	int i;										// A counter

	// Get two strings from the user
	std::cout << "Type two strings separated by a space or <return>" << std::endl;
	std::cin >> myStringOne >>  myStringTwo;

  if (DEBUG) std::cout << "StringOne = " << myStringOne 
		<< "   String Two = " << myStringTwo << std::endl;

	// Check the basics: are the strings the same length?
	len = myStringOne.length();
  if ( myStringTwo.length() != len )
	{
		std::cout << errorString
			<< " (" << myStringOne << ", " << myStringTwo << ")" << std::endl;
		return 1;
	}

	// If the strings are the same length, check each character
  for (i=0; i < len; i++) 
	{
		if ( myStringOne.at(i) != myStringTwo.at(i) )
		{
			std::cout << errorString 
				<< " (" << myStringOne << ", " << myStringTwo << ")" << std::endl;
			return 1;
		}
	}
	
	// If the strings are identical, print success and exit
	std::cout << "Those two strings are identical" << std::endl;
	return 0;

}

