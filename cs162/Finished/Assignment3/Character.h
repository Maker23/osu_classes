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
	int Strength;

public:
	Character() {};
	Character(std::string Name, CharType Type);
	int getArmor();
	int getStrength();
	void setStrength(int St);
	std::string getName() {return Name;};
	CharType getType() {return Type;};
	virtual int attack();
	virtual int defend();
	virtual void Reset();
	float AchillesFactor;
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
