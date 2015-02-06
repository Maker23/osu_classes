#include <string> 

#include "Dice.h"

class Character{

protected:
	std::string Name;
	Dice AttackDice;
	Dice DefendDice;
	int Armor;
	int Strength;
	float AchillesFactor;

public:
	Character() {};
	Character(std::string Name);
	int getArmor();
	int getStrength();
	std::string getName() {return Name;};
	void setStrength(int St);
	virtual int attack();
	virtual int defend();
	//Phrases * getPhrase(std::string);
};

class Goblin:public Character
{
public:
	Goblin(std::string Name);
	int attack();
};

class Barbarian:public Character
{
public:
	Barbarian(std::string Name);
	// static Phrases * Phrase;
};

class ReptilePeople:public Character
{
public:
	ReptilePeople(std::string Name);
};

class BlueChix:public Character
{
public:
	BlueChix(std::string Name);
};

class Shadow:public Character
{
public:
	Shadow(std::string Name);
	int defend();
};
