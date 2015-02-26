#include <iostream> // for debugging printouts
#include <iomanip>
#include <string> 
#include <list>

#include "Flags.h"
#include "Dice.h"
#include "Player.h"

/*

#include <list>
#include "Character.h"

class Player 
{
public:
	std::string Name;
	std::list<Character*> LineUp;
	std::stack<Character*> Graveyard;
	std::list<Character*>::iterator CurrentFighter;

	Player() {};
	Player(std::string Na);
	void RetireCharacter(Character * DeadFighter);
	void Print();
	Character* NextFighter();
};
*/
Player::Player(std::string Na)
{
	Name = Na;
	CurrentFighter = LineUp.end();
}

void Player::RetireFighter (Character * DeadFighter)
{
	bool found = false;
	std::list<Character*>::iterator tmpIter;
	std::cout << "Removing dead fighter " << DeadFighter->getName() << " from Lineup" << std::endl;

	// Pop DeadFighter off the list
	for (tmpIter = LineUp.begin(); tmpIter != LineUp.end(); tmpIter++)
	{
		if (*tmpIter == DeadFighter)
		{
			CurrentFighter = LineUp.erase(tmpIter);
			CurrentFighter--;
			found = true;
			break;
		}
	}
	if (found == false )
	{
		std::cout << "Bad error here in RetireFighter land." << std::endl;
	}
	
	Graveyard.push(DeadFighter);
	// Push DeadFighter onto the stack
}

void Player::Print()
{

	std::list<Character*>::iterator i;

	std::cout << std::left << std::setw(30) << Name + " Lineup: ";
	std::cout << std::setw(8) <<  "Health" 
		<< std::setw(6) <<  "Score" 
		<< std::setw(6) <<  "Bouts" 
		<< std::setw(6) <<  "Wins" 
		<< std::setw(8) <<  "Losses" 
		<< std::endl; 
	for (i = LineUp.begin(); i != LineUp.end(); i++)
	{
		std::cout << "     " << std::left << std::setw(25) << (*i)->getName() 
			<< std::setw(8) << (*i)->getHealth()
			<< std::setw(6) << (*i)->getScore()
			<< std::setw(6) << (*i)->Bouts	
			<< std::setw(6) << (*i)->Wins
			<< std::setw(8) << (*i)->Losses
			<< std::endl; 
		// (" << *i << ")" << std::endl;
	}
}

Character * Player::NextDeadFighter()
{
	Character * myChar;
	if ( Graveyard.empty() ) 
	{
		return NULL;
	}
	else 
	{
		myChar = Graveyard.top();
		Graveyard.pop();
		return myChar;
	}
}

void Player::PrintGraveyard()
{
	Character * myChar;
	std::cout << std::left << std::setw(29) << Name + " Graveyard:";
	std::cout << std::setw(8) <<  "Health" 
		<< std::setw(6) <<  "Score" 
		<< std::setw(6) <<  "Bouts" 
		<< std::setw(6) <<  "Wins" 
		<< std::setw(8) <<  "Losses" 
		<< std::endl; 

	while ( myChar = NextDeadFighter()) 
	{
		std::cout << "     " << std::left << std::setw(25) << myChar->getName() 
			<< std::setw(8) << myChar->getHealth()
			<< std::setw(6) << myChar->getScore()
			<< std::setw(6) << myChar->Bouts	
			<< std::setw(6) << myChar->Wins
			<< std::setw(8) << myChar->Losses
			<< std::endl; 
		//Graveyard.pop();
	}
}

Character* Player::NextFighter()
{
	std::list<Character*>::iterator next;

	//std::cout << "In nextfighter" << std::endl; //DEBUG
	if (LineUp.size() == 0 ) 
	{
		//std::cout << "In nextfighter, returning null" << std::endl; //DEBUG
		return NULL;
	}

	if (CurrentFighter == LineUp.end() )
	{
		//std::cout << "In nextfighter, Current = End " << std::endl; //DEBUG
		CurrentFighter = LineUp.begin();
		return *CurrentFighter;
	}
	else {
		next = CurrentFighter;
		next++;
	}

	//else if (LineUp.size() !=0  && (CurrentFighter == NULL || CurrentFighter == LineUp.end() ))
	if (LineUp.size() !=0  && CurrentFighter == LineUp.end() )
	{
		//std::cout << "In nextfighter, Current = End " << std::endl; //DEBUG
		CurrentFighter = LineUp.begin();
		return *CurrentFighter;
	}
	else if (LineUp.size() !=0  && next == LineUp.end() )
	{
		//std::cout << "In nextfighter, returning Begin " << std::endl; //DEBUG
		CurrentFighter = LineUp.begin();
		return *CurrentFighter;
	}
	else 
	{
		//std::cout << "In nextfighter, returning CurrentFighter++ " << std::endl; //DEBUG
		CurrentFighter++;
		return *CurrentFighter;
	}
}
