#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Dice.h"


/*
class Dice
{
public:
 Dice();
 Dice(int numDice, int numSides);
 virtual int roll() const;

protected:
 int numDice;
 int numSides;
};
*/


Dice::Dice(int numDice, int numSides)
{
	this->numDice = numDice;
	this->numSides = numSides;
	srand(time(NULL)); // Seeds random number generator
}

int Dice::roll() const
{
	int Total = 0;
	for (int i=0; i< numDice; i++)
	{
		Total += ((rand() % numSides) + 1);
	}
		
	return (Total);
}

void Dice::set (int numDice, int numSides)
{
	this->numDice = numDice;
	this->numSides = numSides;
}

void Dice::debug () const
{
	std::cout << "Dice.numDice = " << numDice << ", Dice.numSides = " << numSides << std::endl;
}
