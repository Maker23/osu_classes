/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/10/20
 *  Last Modification date: 2014/10/26
 *  Filename: size.cpp
 *
 *  Overview:
 *  	Calculates user's clothing sizes
 *
 *  Input:  Height, weight, and age
 *
 *  Output:  Hat size, Jacket size, and Waist size
 *
 */

#include <iostream>
#include <sstream>
#include <iomanip>

#define DEBUG false
#define TXT_FORMAT std::setprecision(3)

/* Calculate hat size from Weight and Height */
/* Calculate jacket size from Height, Weight, and Age */
/* Calculate waist size from Weight and Age */
double calculateHatSize(double myWeight, double myHeight);
double calculateJacketSize(double myHeight, double myWeight, double myAge);
double calculateWaistSize(double myWeight, double myAge);

double convertStringToDouble(std::string myInput);

int main () 
{
	int height = 0;
	int weight = 1;
	int age = 2;
	std::string metricName[3] = {"height", "weight", "age"};
	std::string metricNotes[3] = {" in inches", " in pounds", " in years"};
	double metricValue[3] = { 0.0, 0.0, 0.0 };

	char answer = 'n';
	double hatSize = 0.0;
	double jacketSize = 0.0;
	double waistSize = 0.0;
	std::string inputString;
	
 
  do
	{
  	for (int i=0; i<3; i++)
		{
		 	// Get user input values for all three metrics, Height/Weight/Age
			do
			{
				std::cout << "Enter your " << metricName[i] << metricNotes[i] << ": ";
				getline(std::cin, inputString);
  			metricValue[i] = convertStringToDouble(inputString);
				if (metricValue[i] <= 0 ) 
					{ std::cout << "Error, please enter a valid positive number" 
						<< std::endl; }
			}
			while (metricValue[i] <= 0 );

			if (DEBUG) { std::cout << "I got " << metricValue[i] << " for " 
				<< metricName[i] << std::endl;}
		}

  	// Calculate clothing sizes from metrics	
  	hatSize    = calculateHatSize(metricValue[height], metricValue[weight]);
  	jacketSize = calculateJacketSize(metricValue[height], metricValue[weight],
									metricValue[age]);
  	waistSize  = calculateWaistSize(metricValue[weight], metricValue[age]);
	
	  // Print everything out
	  std::cout << std::endl;
  	std::cout << TXT_FORMAT << "Hat Size is " << hatSize  << std::endl;
  	std::cout << TXT_FORMAT << "Jacket Size is " << jacketSize 
			<< " inches (chest diameter)"  << std::endl;
  	std::cout << TXT_FORMAT << "Waist is " << waistSize << " inches"  << std::endl;

		// Run again?
		std::cout << std::endl << "Calculate again? [y|n] ";
		std::cin.get(answer);
  	std::cin.ignore(1000,'\n');
	}
	while ( answer == 'y' || answer == 'Y');

  return 0;

}

/**********************************************
 * calculateHatSize
 *
 * 		Purpose: Calculate hat size given Height and weight
 * 		Input: doubles Height and Weight 
 * 		Output: double HatSize
 *
 *********************************************/
double calculateHatSize(double myHeight, double myWeight)
{
	return ( (myWeight / myHeight) * 2.9 );
}

/**********************************************
 * calculateJacketSize
 *
 * 		Purpose: Calculate jacket size given Height, weight and age
 * 		Input: doubles Height, Weight and age
 * 		Output: double JacketSize
 *
 *********************************************/
double calculateJacketSize(double myHeight, double myWeight, double myAge)
{
	double inches;

	inches = (myHeight * myWeight)/288 ;
	if (myAge > 40 )
	{
	  int intAge = myAge; // force to a truncated int
		inches += (((intAge % 10 ) / 4) * 0.125);
	}
	return inches;
}

/**********************************************
 * calculateWaistSize
 *
 * 		Purpose: Calculate waist size given weight and age
 * 		Input: doubles weight and age
 * 		Output: double WaistSize
 *
 *********************************************/
double calculateWaistSize(double myWeight, double myAge)
{
	double inches;

	inches = (myWeight)/5.7;
	if (myAge > 28 )
	{
	  int intAge = myAge; // force to a truncated int
		inches += (((intAge - 28) / 2 ) * 0.1);
	}

	return inches;
}

/**********************************************
 * Convert a string into a number
 *
 * 		Purpose: Convert a string (probably cin input) into a number, making
 * 			sure what the user typed is valid
 * 		Input: a string inputString
 * 		Output: a double 
 *
 *********************************************/
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
		if (DEBUG) {std::cout << "Oh no, a terrible accident has occurred!"
			<< std::endl;}
		return -1.0;
	}
	if (DEBUG) std::cout << "myDouble is " << myDouble << std::endl;


 	ss >> whatsLeft;
	if ( whatsLeft != "")
	{
		if (DEBUG) { std::cout << "Oh no, an astonishing travesty has taken place!"
			<< std::endl;}
		return -1.0;
	}

  return myDouble;
	
}
