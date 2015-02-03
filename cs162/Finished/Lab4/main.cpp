/* vim:ts=2
 *
 * CS 162, Lab4
 * Shoshana Abrass
 * abrasss@onid.oregonstate.edu
 * Feb 1, 2015
 *
 * No comments here.  See accompanying PDF file.
 *
 *
 */

#include <algorithm>  // for std::sort
#include <iostream>
#include <vector>

#include "Dice.h"

#define DEBUG false

#define NUM_ROLLS 500
#define NUM_SIDES 6

// Prototypes
int rollTwoDice(const Dice& die1, const Dice& die2);
void analyzeResults (int Results[], int ArrSize );
void calculateMode(int inputNumbers[], int ArrSize);

// And now the program
int main()
{
	int LoadedResults[NUM_ROLLS]; // Array of integers to store resuls
	int FairResults[NUM_ROLLS];
	Dice fairDie_1(NUM_SIDES);		// Declare and initialize fair dice
	Dice fairDie_2(NUM_SIDES);
	LoadedDice loadedDie_1(NUM_SIDES); // Declare and initialize loaded dice
	LoadedDice loadedDie_2(NUM_SIDES);

	// Roll the dice and store the results
	for (int i=0; i < NUM_ROLLS; i++) 
	{
		FairResults[i] = rollTwoDice(fairDie_1, fairDie_2);
		LoadedResults[i] = rollTwoDice(loadedDie_1, loadedDie_2);
	}

  // Analyze and print reults
	std::cout << NUM_ROLLS << " rolls, of two " << NUM_SIDES << "-sided dice" << std::endl;
	std::cout << "Fair dice results: " << std::endl;
	analyzeResults (FairResults, NUM_ROLLS);  // yes, printing occurs in the function
	std::cout << "Loaded dice results: " << std::endl;
	analyzeResults (LoadedResults, NUM_ROLLS); // meh
}


int rollTwoDice(const Dice& die1, const Dice& die2)
{
 int One = die1.rollDice();
 int Two = die2.rollDice();

 if (DEBUG) std::cout << "One: " << One << ", Two: "<< Two << std::endl;
 return One + Two;
 //return die1.rollDice() + die2.rollDice(); // Can't do useful debugging this way....
}

void analyzeResults (int Results[], int ArrSize )
{
	int sumAll = 0;

  std::sort(Results, Results + ArrSize); // sort in place

	for (int i=0; i< ArrSize; i++)
	{
		sumAll += Results[i];
	}
	std::cout << "	average = " << (float) sumAll / ArrSize << std::endl;
	if (ArrSize % 2)
	{
		if (DEBUG) std::cout << "Returning the " << ArrSize/2 << "th number as the median" << std::endl;
		// Even number? the median is the average of the two middle numbers
		std::cout << "	 median = " <<
			(Results[((int)ArrSize/2)] +
			 Results[((int)ArrSize/2) +1]) / 2
			 << std::endl;
	}
	else
	{
		if (DEBUG) std::cout << "Returning the " << ArrSize/2 +1 << "th number as the median" << std::endl;
		std::cout << "	 median = " << Results [((int)ArrSize/2)+1] << std::endl;
	}

	calculateMode(Results, ArrSize);

}

void calculateMode(int inputNumbers[], int ArrSize)
{
	int currValue;
	int lastValue;
	int highCount=0;
  int tmpCount=0;
	int size = ArrSize;
	std::vector <int> Modes;	 // at least one member though it may be empty

  if (size == 0 ) 
	{
		return;
	}
	else if (size == 1)
	{
		Modes.push_back(inputNumbers[0]);
	}
	else {
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
	}
	std::cout << "	   mode = ";
	for (int j=0; j< Modes.size(); j++)
	{
		std::cout << Modes[j] << " ";
	}
	std::cout << std::endl;
}
