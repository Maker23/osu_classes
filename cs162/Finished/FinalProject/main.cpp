#include <iostream>
#include <string>

#include "main.h"
#include "Room.h"
#include "BuildTheEnvironment.h"


//enum MenuChoice { N, S, E, W, unknown};
//char MenuOptions[] = {'N', 'S', 'E', 'W'};

/*****************************************************************/
void UpdateGameState(int &Flags, int &GameClock, Holdall* PlayerBag, Room* currentRoom);
std::list<Thing*> EquipThePlayer();

main()
{
	bool Enigmatic = false; // TODO: convert this to flags
	Room * currentRoom;
	Room* allRooms[26];
	int GameClock = 0;
	int Flags = 0;

	Holdall PlayerBag("Linen bag");
	PlayerBag.Capacity = 10;
	std::cout << "Player bag capacity = " << PlayerBag.Capacity << std::endl;

	Room *Start = BuildTheHouse(allRooms);
	FillTheRooms(allRooms);

	//PlayerBag.Contents = EquipThePlayer();

	currentRoom = Start;
	while (GameClock < 24)
	{
		std::cout << std::endl;
		currentRoom->Print(Enigmatic);
		currentRoom = currentRoom->NextUserAction(&PlayerBag);
		UpdateGameState(Flags, GameClock, &PlayerBag, currentRoom);
	}
	std::cout << "Congratulations, you escaped the maze!" << std::endl;

	for (int i=0; i < 8; i++) // TODO : Seriously,how many rooms?  :)
	{
		delete(allRooms[i]);
	}
}

void UpdateGameState(int &Flags, int &GameClock, Holdall* PlayerBag, Room* currentRoom)
{
  
	GameClock++;
	// If the player is carrying the watch, print the time
  if ( CheckTheTime(PlayerBag) )
	{
		std::cout << "You have " << (24 - GameClock) * 5 << " minutes until 4:00" << std::endl;
	}
}

/* ***************************************************************
 * Utility functions
 *************************************************************** */
bool getUserYN(const char Default)
{
	enum YNMenuChoice { y, n, YNunknown};
	char YNMenuOptions[] = {'y', 'n'};
	char menuOption;
	char inputBuffer[1024];

	bool Result=false;

	YNMenuChoice menuChoice = YNunknown;

  do {
  	menuOption = std::cin.get(); // get the first character
		std::cin.getline(inputBuffer,1024); // throw away anything else they typed

	  if ( ! menuOption )
			menuOption = Default;
	
		for (int i=0; i<2; i++)
		{
			if (tolower(menuOption) == YNMenuOptions[i])
			{
				menuChoice = (YNMenuChoice) i;
			}
		}
		switch (menuChoice){
			case y:
				Result = true;
				break;
			case n:
				break;
			case YNunknown:
				std::cout << "Please enter Y or N: ";
				break;
		}
	}
	while (menuChoice == YNunknown);
	return (Result);
}
/*****************************************************************/
