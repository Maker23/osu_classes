/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/10/27
 *  Last Modification date: 2014/11/02
 *  Filename:  refFun.cpp
 *
 *  Overview:
 *		Write a simple function that accepts two references to strings and returns
 *		whether they have the same contents with the use of a loop to check each
 *		character individually.
 *
 */

#include <iostream>
#include <string>

#define DEBUG false

// Compare two strings by passing their references
bool TwoStringsAreTheSame(std::string &myStringOne, std::string &myStringTwo);


int main () 
{
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
 * Description: Compares two strings passed as reference arguments
 * Input: Two std::string references
 * Output: a boolean, 1 if the strings are identical, 0 if not
 *
 *****************************************************************************/
bool TwoStringsAreTheSame(std::string &myStringOne, std::string &myStringTwo)
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
