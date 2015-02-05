#include <string> 

#include "Dice.h"

class Character{

protected:
	std::string Name;
	Dice Attack;
	Dice Defend;
	int Armor;
	int Strength;

public:
	Character() {};
	Character(std::string Name);
	Character(std::string Name, int DAq, int DAs, int DDq, int DDs, int Ar, int St);
	int getArmor();
	int getStrength();
	std::string getName() {return Name;};
	void setStrength(int St);
	virtual int attack();
	virtual int defend();
	//Phrases * getPhrase(std::string);
};

class Barbarian:public Character
{
public:
	Barbarian(std::string Name): Character(Name)
	{
		Attack.set(2,6);
		Defend.set(2,6);
		Armor = 0;
		Strength = 22;
	};
	// static Phrases * Phrase;
};

class Shadow:public Character
{
public:
	Shadow(std::string Name, int DAq, int DAs, int DDq, int DDs, int Ar, int St):
		Character(Name, DAq, DAs, DDq, DDs, Ar, St)
	{};
	int defend();
};
