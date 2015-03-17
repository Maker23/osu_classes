#include <iostream>
#include <string>

#include "utilities.h"
#include "Room.h"
#include "BuildTheEnvironment.h"


//enum MenuChoice { N, S, E, W, unknown};
//char MenuOptions[] = {'N', 'S', 'E', 'W'};

/*****************************************************************/
void UpdateGameState(int &Flags, int &GameClock, Holdall* PlayerBag, AbstractRoom* currentRoom);
void	CheckForTimers(AbstractRoom ** allRooms, int &GameClock, Holdall* PlayerBag);
std::list<Thing*> EquipThePlayer();

main()
{
	bool Enigmatic = false; // TODO: convert this to flags
	AbstractRoom * currentRoom;
	AbstractRoom* allRooms[NumRooms];
	int GameClock = 0;
	int Flags = 0;

	Holdall PlayerBag("Linen bag");
	PlayerBag.Capacity = 10;
	std::cout << "Player bag capacity = " << PlayerBag.Capacity << std::endl;

	AbstractRoom* Start = BuildTheHouse(allRooms);
	FillTheRooms(allRooms);

	//PlayerBag.Contents = EquipThePlayer();

	currentRoom = Start;
	while (GameClock < GameLength)
	{
		std::cout << std::endl;
		currentRoom->Print(Enigmatic);
		currentRoom = currentRoom->NextUserAction(&PlayerBag);
		if (currentRoom == 0 ) break;
		UpdateGameState(Flags, GameClock, &PlayerBag, currentRoom);
		CheckForTimers(allRooms, GameClock, &PlayerBag);
	}
	int points = PlayerBag.getGameTaskStatus();
	if (points ==2)
		std::cout 
			<< "You met the rudimentary needs for a nice tea." << std::endl
			<< "Maybe next time you could do a little more to make it special." << std::endl
			<< "Your friends still like you. They'll come again." << std::endl;
	else if (points >2)
		std::cout << "Congratulations, you made a superbly nice tea!" << std::endl
			<< "Your friends tweet about it. Their pictures go viral." << std::endl
			<< "You're invited to BBC headquarters to meet the cast of" << std::endl
			<< "Pride&Prejudice. They hire you as a consulting writer."<< std::endl;
  else
		std::cout 
			<< "You didn't meet the rudimentary needs for a nice tea." << std::endl
			<< "Your Tea Party is a failure. Your friends tweet about it." << std::endl
			<< "You are banned for life from Jane Austen Society meetings." << std::endl
			<< "You start reading Edward Gorey and listening to emo music." << std::endl;

	for (int i=0; i < NumRooms; i++)
	{
		delete(allRooms[i]);
	}
}

