#include <iostream>
#include <cstdlib>

#include "Dice.h"
#include "Character.h"

void Combat (Character & PlayerOne, Character & PlayerTwo);

int main() 
{
	Dice myDice(2,6);
	//Barbarian myBarb ("Red Sonja", 2, 6, 2, 4, 0, 22);
	Barbarian myBarb ("Red Sonja");
	Shadow myShadow ("The Shadow", 2, 6, 1, 4, 0, 20);

	Combat (myBarb, myShadow);

	/*
	std::cout << "Rolling two dice: " << myDice.roll() << std::endl;

	std::cout << myBarb.getName() << " attack roll: " << myBarb.attack() << std::endl;
	std::cout << myBarb.getName() << " defend roll: " << myBarb.defend() << std::endl;

	std::cout << myShadow.getName() << " defend roll: " << myShadow.defend() << std::endl;
	std::cout << myShadow.getName() << " defend roll: " << myShadow.defend() << std::endl;
	std::cout << myShadow.getName() << " defend roll: " << myShadow.defend() << std::endl;
	*/


}

void Combat (Character & PlayerOne, Character & PlayerTwo)
{
	int flip = rand() % 2; // 0 or 1
	int defend, attack, damage;

	int i=0;

	do
	{
  	if (flip == 0 ) 
		{
			std::cout << PlayerOne.getName() << " attacks " << PlayerTwo.getName() << "!"  << std::endl;
			attack = PlayerOne.attack();
			defend = PlayerTwo.defend();
			damage = attack - (defend + PlayerTwo.getArmor());
			if (damage > 0 ) {
				std::cout << PlayerTwo.getName() << " takes " << damage << " damage!" << std::endl;
				PlayerTwo.setStrength(PlayerTwo.getStrength() - damage);
				if (PlayerTwo.getStrength() <= 0 )
				{
					std::cout << PlayerTwo.getName() << " is hors de combat :( " << std::endl;
				}
			}
			else 
			{
				std::cout << "No damage was done!" << std::endl;
			}
		}
		else 
		{
			std::cout << PlayerTwo.getName() << " attacks " << PlayerOne.getName() << "!"  << std::endl;
			attack = PlayerTwo.attack();
			defend = PlayerOne.defend();
			damage = attack - (defend + PlayerOne.getArmor());
			if (damage > 0 ) {
				std::cout << PlayerOne.getName() << " takes " << damage << " damage!" << std::endl;
				PlayerOne.setStrength(PlayerOne.getStrength() - damage);
				if (PlayerOne.getStrength() <= 0 )
				{
					std::cout << PlayerOne.getName() << " is hors de combat :( " << std::endl;
				}
			}
			else 
			{
				std::cout << "No damage was done!" << std::endl;
			}
		}
		flip = abs(flip - 1);
		i++;
	}
	while ( PlayerOne.getStrength() > 0 && PlayerTwo.getStrength() > 0 );
}
