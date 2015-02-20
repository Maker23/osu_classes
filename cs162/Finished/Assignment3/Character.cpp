#include <cstdlib> // rand()
#include <iostream> // for debugging statements
#include <climits>
#include <string> 

#include "Flags.h"
#include "Character.h"
#include "Dice.h"

Character::Character(std::string Na, CharType Ty)
{
	Name = Na;
	Type = Ty;
	Armor = 0;
	Strength = 0;
	AchillesFactor = 0;
}
void Character::Reset()
{}

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
	if (DEBUG) std::cout << "setting strength to " << St << std::endl;
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

/* GOBLIN constructor and special attack. */

Goblin::Goblin(std::string Name): Character(Name, (CharType)GOBLIN)
{
	AttackDice.set(2,6);
	DefendDice.set(1,6);
	Armor = 3;
	Strength = 8;
	AchillesFactor = 1.0;
}

int Goblin::attack()
{
	int _attack = AttackDice.roll();

	if (_attack == 12 && this->AchillesFactor == 1.0 )
	{
		AchillesFactor = 0.5;
		if (DEBUG) std::cout << "Setting achilles factor for "
			<< this->getName() << " to 0.5 ***************" << std::endl;
	}
	return (_attack);
}

/* BARBARIAN constructor */
Barbarian::Barbarian(std::string Name): Character(Name, (CharType)BARBARIAN)
{
	AttackDice.set(2,6);
	DefendDice.set(2,6);
	Armor = 0;
	Strength = 12;
}

/* REPTILE constructor */
ReptilePeople::ReptilePeople(std::string Name): Character(Name, (CharType)REPTILE)
{
	AttackDice.set(3,6);
	DefendDice.set(1,6);
	Armor = 7;
	Strength = 18;
}

/* BLUE CHIX constructor */
BlueChix::BlueChix(std::string Name): Character(Name, (CharType)BLUECHIX)
{
	AttackDice.set(2,10);
	DefendDice.set(3,6);
	Armor = 3;
	Strength = 12;
}

/* THE SHADOW constructor and special defense */
Shadow::Shadow(std::string Name): Character(Name, (CharType)SHADOW)
{
	AttackDice.set(2,10);
	DefendDice.set(1,6);
	Armor = 0;
	Strength = 12;
}

int Shadow::defend()
{
	// The random number generated is already seeded, since instantiating
	// a Shadow causes the Dice constructor to run
	if ( rand() % 2 ) 
	{
		// The Shadow avoids the attack 50% of the time
		if (DEBUG) std::cout << "The shadow evades the attack!" << std::endl;
	 	return(INT_MAX); // hm.
	}
	else
	{
		return (DefendDice.roll());
	}
}

/* RESET functions for each derivative type.  These are used for
 * testing, to set a character back to normal after a combat round
 */
void Goblin::Reset()
{
	Strength = 8;
	AchillesFactor = 1.0; // Set in the attacking Goblin
}
void ReptilePeople::Reset()
{
	Strength = 18;
}
void BlueChix::Reset()
{
	Strength = 12;
}
void Barbarian::Reset()
{
	Strength = 12;
}
void Shadow::Reset()
{
	Strength = 12;
}
