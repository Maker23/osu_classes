/* vim: ts=2
 *
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/11/17
 *  Last Modification date: 2014/11/23
 *  Filename: 
 *
 *  Overview:
 *	Write a function that takes as a parameter a vector of ints and returns a
 *	vector containing the mode(s) of that data. Remember that the mode is the
 *	value that appears most frequently. If there is just a single mode, then
 *	the vector you return will only contain one int, but if there is a tie,
 *	there will be more. The vector you return should not contain any duplicate
 *	values (each mode should only appear once). Your main method should prompt
 *	the user to keep entering another int until they want to stop. It should
 *	store these values into a vector and pass that to the function. Then it
 *	should print out the values in the returned mode vector.
 *
 *	Input validation: Verify that the user enters valid ints. If an input isn't
 *	valid, prompt the user to try again
 *
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include "_validateIntegerInput.cpp"

#define DEBUG true

std::vector <int> calculateMode(std::vector<int> inputNumbers);

//bool getIntegerInput(std::vector <int> intVector, int expectedSize, int minInt, int maxInt,std::string Prompt)


int main () 
{
	std::vector <int> inputIntegers;
	std::vector <int> intMode;
	bool goodData = false;

	std::cout  
		<< std::endl << std::endl
		<< "This program will find the mode (most commonly occurring member)"
		<< std::endl << "of a group of integers.  Enter any number of integers," 
		<< std::endl << "separated by blanks or commas.  End input with a blank line. "
		<< std::endl << std::endl;
	do
	{
  	goodData = getIntegerInput(&inputIntegers,0,-2048,2048, "");
	}
	while (goodData != true);

	if (inputIntegers.size() == 0)
	{
		std::cout << "ERROR: No valid integers found. Exiting..." << std::endl;
		return -1;
	}
	else
	{
		std::cout << "You entered these valid integers: ";
		for (int i=0;i< inputIntegers.size(); i++)
			std::cout << inputIntegers[i] << ", ";
		std::cout<< std::endl;
  }

	std::sort(inputIntegers.begin(), inputIntegers.end());	
	intMode = calculateMode(inputIntegers);

	std::cout << "Here are the mode(s) for your data set: ";
	std::cout << intMode[0];
	for (int i=1;i< intMode.size(); i++)
	{
		std::cout << ", " << intMode[i];
	}
	std::cout << std::endl;
}

/**********************************************
 * Use a comment block above the function definition
 *
 * 		Purpose:
 * 		Entry:
 * 		Exit:
 *
 *********************************************/
std::vector <int> calculateMode(std::vector<int> inputNumbers)
{
	int currValue;
	int lastValue;
	int highCount=0;
  int tmpCount=0;
	int size = inputNumbers.size();
	std::vector <int> Modes;	 // at least one member though it may be empty

  if (size == 0 ) 
	{
		std::cout << "ERROR, empty vector found\n";
		return Modes;
		// return an empty vector
	}
	else if (size == 1)
	{
		Modes.push_back(inputNumbers[0]);
		return Modes;
	}

	currValue=inputNumbers[0];
	tmpCount=1;
	highCount=1;
	for (int i=1; i<size; i++)
	{
		if (inputNumbers[i] == currValue)	{
			tmpCount += 1;
		}

		if (( i == size-1) || (inputNumbers[i] != currValue))
		{
			if (tmpCount > highCount)
			{
				Modes.clear();
				Modes.push_back(currValue);
				highCount = tmpCount;
			}
			else if (tmpCount == highCount)
			{
				Modes.push_back(currValue);
			}

			if ( i == size -1) 
			{
				// special case
				if (highCount == 1 )
					Modes.push_back(inputNumbers[i]);
			}
			else
			{
				currValue = inputNumbers[i];
				tmpCount=1;
			}
		}
	}
	return Modes;
}
