/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/11/02
 *  Last Modification date: 2014/11/09
 *  Filename: stringMix.cpp
 *
 *  Overview:
 *		Write a function that takes as parameters two C-style strings of the same
 *		length. Upon completion of the function, the second string should be a
 *		random rearrangement of the characters in the first string. The first
 *		string should remain unchanged. 
 *
 *		In main ask the user for a string, pass that and another (empty) string
 *		to the function, then display the value of the second (formerly empty)
 *		string. The function call in main should be in a loop that will keep
 *		asking the user if they want another random rearrangement (of the same
 *		string - it doesn't ask the user for a new string).
 *
 */

#include <iostream>
#include <cstring>
#include <cstdlib>

// Create outString with the randomized characters from inString
void randomizeString(char *inputString, char *outputString);

#define DEBUG false
#define MAX_STR_LEN 256

int main () 
{
	char * inputString;
	char * randomString;
	int stringLength=0;
	char answer = 'n';

	// Silently drop characters beyond MAX. This is just an exercise.
	inputString = new char[MAX_STR_LEN];
	std::cout << "Enter a word or phrase to randomize: ";
	std::cin.getline(inputString, MAX_STR_LEN);
  randomString = new char [strlen(inputString)];

	do 
	{
		randomizeString(inputString, randomString);
		std::cout << "input  is: " << inputString << std::endl;
		std::cout << "output is: " << randomString << std::endl;
		std::cout << "Randomize again? [y|n] ";
		std::cin.get(answer);
		std::cin.ignore(1000,'\n');
	}
	while (answer == 'y' || answer == 'Y');
 
}

/*****************************************************************
 * randomizeString(char *inputString, char *outputString)
 *
 * 		Purpose: Randomly scramble the characters in a string
 * 		Takes: Two char* string pointers
 ****************************************************************/
void randomizeString(char *inputString, char *outputString)
{
  int strLen = strlen(inputString);
  bool randomize[strLen];
	int r;
	int c=0;

	for (int i=0; i<strLen; i++)
	{
		// Remember which positions we've already shifted
		randomize[i]=false;
	}

	do
	{
		r = rand() % strLen;
		if (DEBUG) std::cout << "random number is " << r << std::endl;
		if ( randomize[r]) {
			if (DEBUG) std::cout << "We already had that, trying again" << std::endl;
			continue; // try again
		}
		else {
			if (DEBUG) std::cout << "Copying inStr[" << c << "] " << inputString[c]
				<< "  into outStr[" << r <<"]" <<std::endl;
			outputString[r] = inputString[c];
			randomize[r] = true;
			c++;
		}
	}
	while (c < strLen);
}
