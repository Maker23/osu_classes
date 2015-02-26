#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream> // for debugging printouts
#include <string> 

#include "Flags.h"
#include "Dice.h"

class Character{

protected:
	std::string Name;
	CharType Type;
	Dice AttackDice;
	Dice DefendDice;
	int Armor;
	int Health;
	int Strength;
	int Score;

public:
	float AchillesFactor;
	int Bouts;  // Should make these private if I have time
	int Wins;
	int Losses;

	Character() {};
	Character(std::string Name, CharType Type);
	int getArmor();
	int getHealth();
	int getScore();
	int getStrength();
	void setScore(int Sc);
	void setHealth(int St);
	void scoreAgainst(Character * Ch);
	void Recover();
	virtual void Reset(); // Used in testing
	std::string getName() {return Name;};
	CharType getType() {return Type;};
	virtual int attack();
	virtual int defend();
	//Phrases * getPhrase(std::string);
};

class Goblin:public Character
{
public:
	Goblin(std::string Name);
	void Reset();
	int attack();
};

class Barbarian:public Character
{
public:
	Barbarian(std::string Name);
	void Reset();
	// static Phrases * Phrase;
};

class ReptilePeople:public Character
{
public:
	ReptilePeople(std::string Name);
	void Reset();
};

class BlueChix:public Character
{
public:
	BlueChix(std::string Name);
	void Reset();
};

class Shadow:public Character
{
public:
	Shadow(std::string Name);
	void Reset();
	int defend();
};
#endif //CHARACTER_H
