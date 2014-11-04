/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/10/20
 *  Last Modification date: 2014/10/26
 *  Filename: finalist.cpp
 *
 *  Overview: 
 *
 *		You have four identical prizes to give away and a pool of 25 finalists.
 *		The finalists are assigned numbers from 1 to 25. Write a program to
 *		randomly select the numbers of 4 finalists to receive a prize. Make sure 
 *		not to pick the same number twice. For example, picking finalists 
 *		3, 15, 22, and 14 would be valid but picking 3, 3, 31, and 17 would be 
 *		invalid, because finalist number 3 is listed twice and 31 is not a valid
 *		finalist number
 *
 *  Input:
 *		Nothing
 *  Output:
 *		The numbers of four unique finalists chosen at random
 */

#include <iostream>
#include <cstdlib>
#include <time.h>

#define DEBUG false
#define NUM_RANDS 4
#define CONTESTANTS 25

int main () 
{
	bool finalists[CONTESTANTS] = { false } ;
	int r; // The random number
	int numbersFound = 0;

	srand(time(NULL)); // Seed the random generator with time in msec

	do
	{
		r = rand() % CONTESTANTS;
		if (DEBUG) std::cout << "random number is " << r << std::endl;
		if ( finalists[r] ) {
			if (DEBUG) std::cout << "We already had that, trying again" << std::endl;
			continue; // try again
		}
		else {
			finalists[r] = true;
			numbersFound++;
		}
	}
	while (numbersFound < NUM_RANDS);

	std::cout << "And the winners are: ";
	for (int i=0; i< CONTESTANTS; i++) {
		if (finalists[i])
		{
			std::cout << " " << i+1;
		}
	}
	std::cout << std::endl;

}
