// vim: ts=2

#include <climits> // INT_MIN and _MAX
#include <cstdio>		// Because sprintf
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <time.h>
#include <vector>

#ifndef DEBUG
#define LIB_DEBUG false	 // More or less verbose
#else
#define LIB_DEBUG DEBUG	
#endif

#define ZERO 48
#define NINE 57
#define DASH 45
#define DOT 46
#define COM 44
#define SPACE 32

/* ***************************************************************************
 * Take a string argument, confirm it is an integer number, or a floating
 * point number. Return the numeric value, or MinValue - 1 to indicate failure
 *
 * TODO: explore better ways to indicate failure
 *
 *****************************************************************************/
int validateIntegerInput(char *inputString, int MinValue, int MaxValue);
double validateFloatInput(char *inputString, float MinValue, float MaxValue);

/* ***************************************************************************
 * getIntegerInput version 1
 *
 * Prompt for and read in one line of input from the user, 
 * confirm it is an integer number. 
 * 
 *****************************************************************************/
int getIntegerInput (int MinValue=INT_MIN+1, int MaxValue=INT_MAX, 
	int MaxNumberOfTries=0, const std::string Prompt="");


/* ***************************************************************************
 * getIntegerInput  version 2
 *
 * 		Purpose: Prompt for and read in an arbitrary number of numbers, 
 * 						 confirm they're integers, put them into a vector.
 *  					 Users can enter data separated by spaces or newlines.
 *  					 A blank line ends the input.
 * 	  Takes: 	 A pointer to a vector of integers; an integer arrayLen
 * 		Returns: False for bad data, True for good data
 *
 *    Note:    non-integer numbers are skipped, the function keeps going
 *
 *****************************************************************************/
bool getIntegerInput(std::vector <int> *intVector, int expectedSize, 
	int minInt, int maxInt, std::string Prompt);

/* A simplified wrapper around getIntegerInput, collects numbers from 0-100  */
bool getSmallIntegerInput(int *intArray, int arrayLen);
