#include <iostream>
#include <string>

#include "Functions.h"

/*****************************************************************/
Room * getNextRoomFromDirection( Room * currentRoom, MenuChoice nextChoice)
{
	bool error = false;
	Room * nextRoom = NULL;

  	if (currentRoom == NULL ) 
		{
			std::cout << "Can't proceed from a NULL room" << std::endl;
			return NULL;
		}
		switch (nextChoice) {
			case N:
				nextRoom = currentRoom->North;
				std::cout << "  Going North" << std::endl;
				break;
			case S:
				nextRoom = currentRoom->South;
				std::cout << "  Going South" << std::endl;
				break;
			case E:
				nextRoom = currentRoom->East;
				std::cout << "  Going East" << std::endl;
				break;
			case W:
				nextRoom = currentRoom->West;
				std::cout << "  Going West" << std::endl;
				break;
			case unknown:
				std::cout << "Unrecognized direction" << std::endl;
				error=true;
				break;
		}
		if ( error == false && nextRoom == NULL )
			std::cout << "Sorry, you can't go that way." << std::endl;

	return(nextRoom);
}
/*****************************************************************/
Room * getNextRoom( Room * currentRoom)
{
	bool error = false;
	MenuChoice nextChoice;
	Room * nextRoom = NULL;

	do 
	{
		error=false;
		nextChoice = getUserMenuChoice();
		switch (nextChoice) {
			case N:
				nextRoom = currentRoom->North;
				break;
			case S:
				nextRoom = currentRoom->South;
				break;
			case E:
				nextRoom = currentRoom->East;
				break;
			case W:
				nextRoom = currentRoom->West;
				break;
			case unknown:
				std::cout << "Unrecognized direction, try again" << std::endl;
				error=true;
				break;
		}
		if ( error == false && nextRoom == NULL )
			std::cout << "Sorry, you can't go that way. ";
	}
	while (nextRoom == NULL);
	return(nextRoom);
}

/*****************************************************************/
void PrintRoom(Room * currentRoom, bool Enigmatic)
{
	std::string Conjunction = "";
  
	std::cout << "You are in ";
	Enigmatic? std::cout << "a room": std::cout << "room " + currentRoom->Name;
	std::cout << ".  ";

	if (! Enigmatic ){
		std::cout << "You can move ";
		if (currentRoom->North != NULL)
		{
			std::cout << Conjunction + "North"; 
			Conjunction=" or ";
		}
		if (currentRoom->East != NULL)
		{
			std::cout << Conjunction + "East"; 
			Conjunction=" or ";
		}
		if (currentRoom->South != NULL)
		{
			std::cout << Conjunction + "South"; 
			Conjunction=" or ";
		}
		if (currentRoom->West != NULL)
		{
			std::cout << Conjunction + "West"; 
		}
	}
	std::cout << std::endl << "Which way do you want to go?";
}

/*****************************************************************/
MenuChoice getUserMenuChoice()
{

	char MenuOptions[] = {'N', 'S', 'E', 'W'};
	char menuOption;
	MenuChoice menuChoice;
	char inputBuffer[1024];

	std::cout << "(N, S, E, W):  ";
  menuOption = std::cin.get(); // get the first character
	std::cin.getline(inputBuffer,1024); // throw away anything else they typed

	for (int i=0; i<5; i++)
	{
		if (toupper(menuOption) == MenuOptions[i])
		{
			menuChoice = (MenuChoice) i;
			return (menuChoice);
		}
	}
	return (unknown);
}
/*****************************************************************/
bool getUserYN()
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
