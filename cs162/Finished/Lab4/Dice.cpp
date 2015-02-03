#include <cstdlib>
#include <ctime>
#include "Dice.h"


/*
class Dice
{
public:
 Dice();
 Dice( int numSides);
 virtual int rollDice() const;

protected:
 int numSides;
};
*/


Dice::Dice(int numSides)
{
	this->numSides = numSides;
	srand(time(NULL)); // Seeds random number generator
}

int Dice::rollDice() const
{
	return (rand() % numSides) + 1;
}

LoadedDice::LoadedDice(int numSides) : Dice (numSides)
{
	//this->numSides = numSides;
	//srand(time(NULL)); // Seeds random number generator
}

int LoadedDice::rollDice() const
{
	int Random = rand();

	if (Random < RAND_MAX/2 ){
		return numSides;
	}
	else {
		return (rand() % numSides) + 1;
  }
}
