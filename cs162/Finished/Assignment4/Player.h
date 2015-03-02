#include <list>
#include <stack>
#include "Character.h"

class Player 
{
	int TotalScore;
	std::string Name;
	std::stack<Character*> Graveyard;
	std::list<Character*>::iterator CurrentFighter;
	std::list<Character*> LineUp;

public:

	Player() {};
	Player(std::string Na);
	std::string getName();
	int getScore();
	void setScore(int Scr);
	void AddFighter(Character * NewFighter);
	void RetireFighter(Character * DeadFighter);
	void Print();
	void PrintGraveyard();
	Character* NextFighter();
	Character* NextDeadFighter();
};
