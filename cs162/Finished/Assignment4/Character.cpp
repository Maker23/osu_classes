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
	Health = 0;
	Strength = 0; // Never changes
	Score = 0;
	Bouts = 0;
	Wins = 0;
	Losses = 0;
	AchillesFactor = 0;
	Player = NULL;
}
void Character::Reset()
{
	Health = Strength;
}

int Character::getArmor() 
{
	return(Armor);
}

int Character::getHealth() 
{
	return(Health);
}

void Character::setHealth(int He) 
{
	if (He < 0) He=0;
	if (DEBUG) std::cout << "setting " << Name << "'s health to " << He << std::endl;
	Health = He;
}

int Character::getScore()
{
	return(Score);
}

void Character::setScore(int Sc)
{
	if (DEBUG) std::cout << "Setting " << Name << "'s score to " << Sc << std::endl;
	Score = Sc;
}

void Character::setPlayer(void * PlaPtr)
{
	Player = PlaPtr;
}
void * Character::getPlayer()
{
	return Player;
}

void Character::scoreAgainst(Character * Ch)
{
	this->setScore (this->getScore() + 3); // Three points for the win
 	// One point for nearly dying: leave it all on the battlefield!
	//if (this->Health < 3) this->setScore(this->getScore() + 1);
	// Extra points if the loser is stronger than the winner
	if (this->Strength < Ch->Strength) {
		this->setScore ( this->getScore() + (Ch->Strength - this->Strength));
	}
}


void Character::Recover()
{
	if (Health == Strength) return;

  // Differential recovery helps balance the inequity for 
	// more interesting results (fewer ties)
	if (Strength < 10 )
		Health += (int)((float)Strength * (0.5)); 
	else if (Strength > 16)
		Health += (int)((float)Strength * (0.4));
	else 
		Health += (int)((float)Strength * (0.3));

	// Health can't be below 0 or greater than Strength
	if (Health < 0) 
		Health = 0;
	if (Health > Strength) 
		Health = Strength;

	if (VVERBOSE) std::cout << "** Recovery: " << Name << "'s health is now " << Health << std::endl;
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
	Health = Strength;
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
	Health = Strength;
}

/* REPTILE constructor */
ReptilePeople::ReptilePeople(std::string Name): Character(Name, (CharType)REPTILE)
{
	AttackDice.set(3,6);
	DefendDice.set(1,6);
	Armor = 7;
	Strength = 18;
	Health = Strength;
}

/* BLUE CHIX constructor */
BlueChix::BlueChix(std::string Name): Character(Name, (CharType)BLUECHIX)
{
	AttackDice.set(2,10);
	DefendDice.set(3,6);
	Armor = 3;
	Strength = 12;
	Health = Strength;
}

/* THE SHADOW constructor and special defense */
Shadow::Shadow(std::string Name): Character(Name, (CharType)SHADOW)
{
	AttackDice.set(2,10);
	DefendDice.set(1,6);
	Armor = 0;
	Strength = 12;
	Health = Strength;
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
	Health = Strength;
	AchillesFactor = 1.0; // Set in the attacking Goblin
}
void ReptilePeople::Reset()
{
	Health = Strength;
}
void BlueChix::Reset()
{
	Health = Strength;
}
void Barbarian::Reset()
{
	Health = Strength;
}
void Shadow::Reset()
{
	Health = Strength;
}
