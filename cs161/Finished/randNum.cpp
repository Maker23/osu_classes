/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/10/13
 *  Last Modification date: 2014/10/19
 *  Filename: randNum.cpp
 *
 *  Overview: 
 *  	Print some random numbers using a loop (say 10 of them),
 *		Visit http://www.cplusplus.com/reference/cstdlib/rand/, 
 *		my sample code directory, the tutorials I mention, and any searches 
 *		you want (including the book if you can find something good in 
 *		there :) )
 *
 *  Input:
 *		Nothing
 *  Output:
 *		Ten random numbers
 */

#include <iostream>
#include <cstdlib>
#include <time.h>

#define NUM_RANDS 10

int main () 
{
	int r; // The random number

	srand(time(NULL)); // Seed the random generator with time in msec

	for(int i=0; i< NUM_RANDS; i++)
	{
  	r = rand();
		std::cout << "Your random number is " << r << std::endl;
	}
}
