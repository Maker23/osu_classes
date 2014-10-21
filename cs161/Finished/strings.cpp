/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/10/13
 *  Last Modification date: 2014/10/19
 *  Filename: strings.cpp
 *
 *  Overview:
 *		a. Include the string library (#include <string>),
 *		b. create a string variable (string my_str;),
 *		c. get user input for that string (cin >> my_str;),
 *		d. use a for loop to print the string one character at a time using 
 *			the at function (example: 
 *			for(int i = 0;i < my_str.length(); i++){cout << my_str.at(i) << endl;})
 *		e. use a for loop to print the string one character at a time in reverse 
 *			using the at function (example: 
 *			for(int i...){cout << my_str.at(i) << endl;})
 *		f. use a loop to count how many letters there are in the word, keeping 
 *			in mind that not all characters in the word need to be letters...
 *
 *		Discuss on Discussion Board: notice how the body in my example for loop 
 *		looks the same but that I hide the for loop's definition, how could I 
 *		use this to make this print the string in reverse?
 *
 *		Note: this exercise step asks you to count the number of letters in 
 *		the word rather than the number of characters that are in the word.
 *		Discuss on Discussion Board: the actual solution to the above is up to
 *		you, but let others know how you did this!. Find out how you might be 
 *		able to do this with multiple words in the input! (hint: using the 
 *		getline function is one way)(example: getline(cin, my_str);)
 *		Discuss on Discussion Board: what happens if you extract from cin 
 *		and use getline in the same code repeatedly? How can you fix this?
 *
 *  Input:
 *  	A string of characters (whitespace as the terminator)
 *
 *  Output:
 *		1. The string's characters printed one per line
 *		2. The string's characters printed backwards, one per line
 *		3. A count of how many letters [A-za-z] are in the string
 */

#include <iostream>
#include <string>

#define DEBUG false

int main () 
{
	std::string myString; // User input string
	int numLetters = 0;		// Keep track of how many letters there are 
	int i = 0;						// A counter
	char c;								// A temporary char for testing

	std::cout << "Enter a string for analysis: ";
	//std::cin >> myString; // Will grab everythign up to whitespace??
	std::getline(std::cin, myString); // Will grab the whole line

	if (DEBUG) std::cout << "Got this->" << myString << "<-" << std::endl;

 	for (i = 0;i < myString.length(); i++)
	{
		c = myString.at(i);
		std::cout << c << "  ";
		std::cout << myString.at(myString.length() - 1 - i) << std::endl;
		if ( ('A' <= c && c <= 'Z' )|| ('a' <= c && c <= 'z'))
		{
			numLetters++;
		}
	}

	std::cout << "Number of leters = " << numLetters << std::endl;

	return 0;
}
