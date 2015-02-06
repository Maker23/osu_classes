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
	AchillesFactor = 1.0;
}

/*
Character::Character(std::string Na, int DAq, int DAs, int DDq, int DDs, int Ar, int St)
{
	Name = Na;
	AttackDice.set(DAq, DAs);
	DefendDice.set(DDq, DDs);
	Armor = Ar;
	Strength = St;
}
*/

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
	return (AttackDice.roll());
}

int Character::defend()
{
	return (DefendDice.roll());
}


Goblin::Goblin(std::string Name): Character(Name)
{
	AttackDice.set(2,6);
	DefendDice.set(1,6);
	Armor = 3;
	Strength = 8;
}

int Goblin::attack()
{
	int _attack = AttackDice.roll();

	if (_attack == 12) 
	{
		AchillesFactor = 0.5;
		if (DEBUG) std::cout << "Setting achilles factor to 0.5" << std::endl;
	}
	return (_attack);
}

Barbarian::Barbarian(std::string Name): Character(Name)
{
	AttackDice.set(2,6);
	DefendDice.set(2,6);
	Armor = 0;
	Strength = 22;
}

ReptilePeople::ReptilePeople(std::string Name): Character(Name)
{
	AttackDice.set(3,6);
	DefendDice.set(1,6);
	Armor = 7;
	Strength = 18;
}

BlueChix::BlueChix(std::string Name): Character(Name)
{
	AttackDice.set(2,10);
	DefendDice.set(3,6);
	Armor = 3;
	Strength = 12;
}

Shadow::Shadow(std::string Name): Character(Name)
{
	AttackDice.set(2,10);
	DefendDice.set(1,6);
	Armor = 0;
	Strength = 22;
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
		return (DefendDice.roll());
	}
}
