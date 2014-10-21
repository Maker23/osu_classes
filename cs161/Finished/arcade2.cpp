/*
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/10/06
 *  Last Modification date: 2014/10/12
 *  Filename: arcade2.cpp
 *
 *  Overview:
 *    The video game machines at your local arcade output coupons depending 
 *    on how well you play the game. You can redeem 
 *          10 coupons for a candy bar, or 
 *           3 coupons for a gumball. 
 *    You prefer candy bars to gumballs. Write a program that inputs the 
 *    number of coupons you win and outputs how many candy bars and gumballs 
 *    you can get if you spend all of your coupons on candy bars first 
 *    and any remaining coupons on gumballs.
 *
 *  Input:
 *    numCoupons, an integer number of coupons you've won
 *
 *  Output:
 *    numCandyBars and numGumballs, optimizing for most candy bars
 *    numCoupons left after buying everything
 *    ASCII art!!
 */

#include <iostream>
#include <iomanip>


// These are globals, this program is tiny so I think it's ok
const int CandyBarCost = 10;	// Cost of a Candy Bar, in coupons
const int GumBallCost  =  3;  // Cost of a Gumball, in coupons

// Print the results of the main() function in user-readable form
int PrintResults(int numCandyBars, int numGumballs, int numCoupons); 

int main () 
{
	int numCoupons, 	// Input by the user: Number of coupons won
			numCandyBars, // Number of candy bars the user can buy
			numGumballs;  // Number of gumballs the user can buy
	// The book uses this initialization method (below)
	// but I don't like it and wouldn't use it again.
  numCoupons = numCandyBars = numGumballs = 0;

	std::cout << "How many coupons did you win today? " << std::endl;
	std::cin >> numCoupons;

	while (numCoupons >= GumBallCost)
	{
		if (numCoupons < CandyBarCost)
		{
			numGumballs += 1;
			numCoupons -= GumBallCost;
		}
		else
		{
			numCandyBars += 1;
			numCoupons -= CandyBarCost;
		}
	}

	PrintResults(numCandyBars, numGumballs, numCoupons);

}

/****************************************************************************
 * Purpose: Print the results of the main() function in user-readable form
 *
 * Inputs: numCandyBars, numGumballs, numCoupons
 *         Numbers will be printed out and used to create ASCII art
 *
 * Outputs: Information about how the users should spend coupons,
 *          enhanced with ASCII art
 *
 ***************************************************************************/
int PrintResults(int numCandyBars, int numGumballs, int numCoupons) 
{
	int i; 

  const std::string Bar1 = " _____ ";	 // ASCII art for candy bar, line 1
  const std::string Bar2 = "{_____}";  // ASCII art for candy bar, line 2

  const std::string Gum1 = " _ ";	// ASCII art for gumball, line 1
  const std::string Gum2 = "(_)"; // ASCII art for gumball, line 2

  const std::string Coup1 = " ___ ";  //ASCII art for coupon, line 1
  const std::string Coup2 = "|___|";  //ASCII art for coupon, line 2

  if ( ! (numCandyBars || numGumballs) )
	{
		std::cout << "You don't have enough coupons to buy anything :(" <<
			std::endl << "Try again later." << std::endl;
		return 0; // exit the function
	}

	std::cout << "You can buy " << numCandyBars << " candy bars and " <<
		numGumballs << " gumballs." << std::endl;
  if (numCoupons) 
	{
		std::cout << "You will have " << numCoupons << " coupons "
			"left for tomorrow." << std::endl;
	}
	// Print the ascii art
	// TODO: This will not work if the printed line length exceeds the 
	// terminal width. Something to be coded later.
	if (numCandyBars)
	{
		for (i=0; i<numCandyBars; i++) std::cout << Bar1;  std::cout << std::endl;
		for (i=0; i<numCandyBars; i++) std::cout << Bar2;  std::cout << std::endl;
	}
	if (numGumballs)
	{
		for (i=0; i<numGumballs;  i++) std::cout << Gum1;  std::cout << std::endl;
		for (i=0; i<numGumballs;  i++) std::cout << Gum2;  std::cout << std::endl;
	}
	if (numCoupons)
	{
		for (i=0; i<numCoupons;   i++) std::cout << Coup1; std::cout << std::endl;
		for (i=0; i<numCoupons;   i++) std::cout << Coup2; std::cout << std::endl;
	}
}
