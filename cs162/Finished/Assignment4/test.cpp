#include <iostream>
#include <cstdlib>
#include <typeinfo>

#include "Flags.h"
#include "Dice.h"
#include "Character.h"

#ifndef TEST
#define TEST false
#endif

int Combat (Character & PlayerOne, Character & PlayerTwo);
void runStatisticsTests(Character &PlayerOne, Character & PlayerTwo);
void runTests();

int main()
{
	runTests();
	// This is all we do. For now we're just using test drivers
	// to make sure the classes are working properly
}
