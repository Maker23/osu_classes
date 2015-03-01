#include <list>
#include <stack>
#include "Character.h"

class Player 
{
public:
	int TotalScore;
	std::string Name;
	std::list<Character*> LineUp;
	std::stack<Character*> Graveyard;
	std::list<Character*>::iterator CurrentFighter;

	Player() {};
	Player(std::string Na);
	void RetireFighter(Character * DeadFighter);
	void Print();
	void PrintGraveyard();
	Character* NextFighter();
	Character* NextDeadFighter();
};
