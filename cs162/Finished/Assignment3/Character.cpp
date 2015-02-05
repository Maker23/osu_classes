#include <cstdlib> // rand()
#include <iostream> // for debugging statements
#include <climits>
#include <string> 

#include "Flags.h"
#include "Character.h"
#include "Dice.h"


/*
class Character{

private:
	std::string Name;
	Dice Attack;
	Dice Defend;
	int Armor;
	int Strength;

public:
	Character() {};
	Character(std::string Name, int DAq, int DAs, int DDq, int DDs, int Ar, int St);
	int getArmor();
	int getStrength();
	void setStrength(int St);
	virtual int attack();
	virtual int defend();
	//Phrases * getPhrase(std::string);
};

*/
Character::Character(std::string Na)
{
	Name = Na;
	Armor = 0;
	Strength = 0;
}

Character::Character(std::string Na, int DAq, int DAs, int DDq, int DDs, int Ar, int St)
{
	Name = Na;
	Attack.set(DAq, DAs);
	Defend.set(DDq, DDs);
	Armor = Ar;
	Strength = St;
}

int Character::getArmor() 
{
	return(Armor);
}

int Character::getStrength() 
{
	return(Strength);
}

void Character::setStrength(int St) 
{
	std::cout << "setting strength to " << St << std::endl;
	Strength = St;
}

int Character::attack()
{
	return (Attack.roll());
}

int Character::defend()
{
	return (Defend.roll());
}

int Shadow::defend()
{
	// The random number generated is already seeded, since instantiating
	// a Shadow causes the Dice constructor to run
	
	if ( rand() % 2 ) 
	{
		// The Shadow avoids the attack!
		std::cout << "The shadow escapes!" << std::endl;
	 	return(INT_MAX); // hm.
	}
	else
	{
		return (Defend.roll());
	}
}
