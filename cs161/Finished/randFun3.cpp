/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/11/02
 *  Last Modification date: 2014/11/09
 *  Filename: randFun2.cpp
 *
 *  Overview:
 *		Write a write a simple function that acts like a random number generator
 *		with the following behavior: 
 *		◦ its definition looks like the following:
 *			void rand_int(const int *min, const int *max, int *val) 
 *		◦ it accepts the addresses of three int values (one for the bottom 
 *			of the random range, one for the top of the random range, and one 
 *			to store the final value), generates a number within that range,
 *			and stores it in the variable pointed to by the third parameter.  
 *
 *		In main you should ask the user for the min and max values and store them
 *		in variables, pass the addresses of those variables (and that of a third
 *		variable) to the function, then print out the (new) value of the third
 *		variable.  
 *
 */

#include <iostream>
#include <climits>
#include <cmath>
#include <time.h>
#include "_validateIntegerInput.cpp"

#define DEBUG false

// This function is in an include file
// validateIntegerInput (MinValue, MaxValue, MaxNumberOfTries, Prompt);
// Calculate a random number within a range of min-max
void randInt(int *minVal, int *maxVal, int *randVal);

int main () 
{
	int maxVal = 0;
	int minVal = 0;
	int randVal = 0;

  std::cout << "Please set the maximum and minimum ends of the range"
		<< std::endl;
	maxVal = validateIntegerInput(0,exp2(16),1);
	minVal = validateIntegerInput(0,exp2(16),1);

	randInt(&maxVal, &minVal, &randVal);
	std::cout << "Random number between " << minVal << " and " << maxVal << " = " << randVal << std::endl;
}

/******************************************************************
 *	void randInt(int *minVal, int *maxVal, int *randVal)
 *
 * 		Purpose: Calculate a random number between min & max
 * 		Takes: Three pointers to integers
 *****************************************************************/
void randInt(int *minVal, int *maxVal, int *randVal)
{
  long Range = abs(*maxVal - *minVal) + 1;

	// This is a simplified variant of the XORSHIFT algorithm as described by Wikipedia
	// It uses time() as one of the seeds, along with an unchanging seed ('w') that
	// is bit-shifted by a varying number of bits.  Seems random enough for this
	// exercise.
	
	// Time in seconds since Jan 1,2014. This is still a 28-bit number.
  ulong x = time(NULL) - 1388534401;  
  long shift = x % 17; // Bit shift 'w' 0-16 bits, depending on time x
  ulong w = 88675123; // This is a 27-bit number 
  ulong t;

  t = x ^ (x << 5); // XOR 'x' with a bit shifted version of itself
  w = w ^ (w >> shift) ^ (t ^ (t >> 8)); // more XOR'ing and bit shifting

  // Dereference randVal, we're setting the value, not the pointer
  *randVal = (w % (Range)) +  (*minVal < *maxVal? *minVal : *maxVal);
}

