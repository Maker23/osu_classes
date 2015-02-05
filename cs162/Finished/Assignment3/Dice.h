#include "Flags.h"

#ifndef DICE_H
#define DICE_H

class Dice
{
public:
 Dice() {};
 Dice(int numDice, int numSides);
 void set (int numDice, int numSides);
 //void setNumSides(int numSides);
 //void setNumDice(int numDice);
 void debug() const;
 virtual int roll() const;

private:
 int numDice;
 int numSides;
};

#endif
