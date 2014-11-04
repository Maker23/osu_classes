/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/10/20
 *  Last Modification date: 2014/10/26
 *  Filename: mpg.cpp
 *
 *  Overview:
 * 		A liter is 0.264179 gallons. Write a program that will read in the 
 * 		number of liters of gasoline consumed by the user's car and the
 * 		number of miles traveled by the car and will then output the number
 * 		of miles per gallon the car delivered. Your program should allow the
 * 		user to repeat this calculation as often as the user wishes. Define
 * 		a function to compute the number of miles per gallon. Your program
 * 		should use a globally defined constant for the number of liters per
 * 		gallon.
 *
 *  Input:
 *    Miles travelled
 *    Litres of fuel consumed
 *
 *  Output:
 *    Miles Per Gallon
 *
 */

#include <iostream>
#include <iomanip>
#include <sstream>

#define DEBUG false
const double gallonsPerLiter= 0.264179;

/* Calculate MPG from miles and Litres */
double calculateMPG(double myMiles, double myLiters);

/* Validate user input is a number, return it as a double */
double convertStringToDouble(std::string myInput);

int main () 
{
	char answer = 'n';
	double miles = 0.0;
	double liters = 0.0;
	double mpg = 0.0;
	std::string inputString;
 
  do
	{
		do
		{
			std::cout << "Number of miles travelled: ";
			getline(std::cin, inputString);
  		miles = convertStringToDouble(inputString);
			if (miles < 0 ) 
				{ std::cout << "Error, please enter a valid positive number" << std::endl; }
		}
		while (miles < 0 );
		if (DEBUG) { std::cout << "I got " << miles << std::endl;}
	
		do
		{
			std::cout << "Liters of fuel consumed: ";
			getline(std::cin, inputString);
  		liters = convertStringToDouble(inputString);
			if (liters < 0 ) 
				{ std::cout << "Error, please enter a valid positive number" << std::endl; }
		}
		while (liters < 0 );
	
  	mpg = calculateMPG(miles, liters);
	
  	std::cout << std::setprecision(3) << "You got " << mpg  << " miles per gallon."  << std::endl;

		std::cout << std::endl << "Calculate again? [y|n] ";
		std::cin.get(answer);
  	std::cin.ignore(1000,'\n');
	}
	while ( answer == 'y' || answer == 'Y' );

  return 0;

}

/**********************************************
 * Use a comment block above the function definition
 *
 * 		Purpose:
 * 		Entry:
 * 		Exit:
 *
 *********************************************/
double calculateMPG(double myMiles, double myLiters)
{
	double myGallons = myLiters * gallonsPerLiter;
	return ( myMiles / myGallons);
}

double convertStringToDouble(std::string inputString)
{
	int lengthOfInput = 0;
	int numberOfTries = 0;
	int maxTries = 3;
	double myDouble;
	std::string whatsLeft = "";

	if (DEBUG) std::cout << "Entering function with string " << inputString << std::endl;
  std::stringstream ss ( inputString );

	if ( ! (ss >> myDouble))
	{
		// Can't convert our string to a double
		if (DEBUG) {std::cout << "Oh no, a terrible accident has occurred!" << std::endl;}
		return -1.0;
	}
	if (DEBUG) std::cout << "myDouble is " << myDouble << std::endl;
 	ss >> whatsLeft;
	if ( whatsLeft != "")
	{
	  // Something else was entered besides a number. 
		if (DEBUG) { std::cout << "Oh no, an astonishing travesty has taken place!" << std::endl;}
		return -1.0;
	}

  return myDouble;
	
}
