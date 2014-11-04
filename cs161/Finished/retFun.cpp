/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/10/20
 *  Last Modification date: 2014/10/26
 *  Filename: retFun.cpp
 *
 *  Overview:
 * 		Write a simple function that accepts two strings and returns whether they
 * 		have the same contents with the use of a loop to check each character individually. 
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

/* Return 1 (true) if the strints are identical, 0 (false) otherwise */
bool TwoStringsAreTheSame(std::string myStringOne, std::string myStringTwo);

int main () 
{
	// The error string
	std::string myStringOne; 	// First string input by the user
	std::string myStringTwo; 	// Second string input by the user
	bool isEqual = false;

	// Get two strings from the user
	std::cout << "Type two strings separated by a space or <return>" << std::endl;
	std::cin >> myStringOne >>  myStringTwo;

  if (DEBUG) std::cout << "MAIN:    StringOne = " << myStringOne 
		<< "   String Two = " << myStringTwo << std::endl;
  
	if ( TwoStringsAreTheSame(myStringOne, myStringTwo) )
	{
		std::cout << "Those two strings are identical" << std::endl;
		return 0;
	}
	else
	{
		std::cout << "Those two strings are not identical" 
			<< " (" << myStringOne << ", " << myStringTwo << ")" << std::endl;
		return 1;
	}

}

/* **************************************************************************
 * Description: Compares two strings passed as arguments
 * Input: Two std::string objects
 * Output: a boolean, 1 if the strings are identical, 0 if not
 *
 *****************************************************************************/
bool TwoStringsAreTheSame(std::string myStringOne, std::string myStringTwo)
{
	int len;									// The length of the first string
	int i;										// A counter
	
  if (DEBUG) std::cout << "FUNCTION: StringOne = " << myStringOne 
		<< "   String Two = " << myStringTwo << std::endl;
	// Check the basics: are the strings the same length?
	len = myStringOne.length();
  if ( myStringTwo.length() != len )
	{
		return 0;
	}

	// If the strings are the same length, check each character
  for (i=0; i < len; i++) 
	{
		if ( myStringOne.at(i) != myStringTwo.at(i) )
		{
			return 0;
		}
	}
	return 1;
}
