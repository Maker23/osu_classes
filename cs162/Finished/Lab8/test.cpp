#include <iostream>
#include <string>

#include "Functions.h"


//enum MenuChoice { N, S, E, W, unknown};
//char MenuOptions[] = {'N', 'S', 'E', 'W'};

/*****************************************************************/
main()
{
	bool Enigmatic = false;
	int counter;
	Room * currentRoom;
	Room* allRooms[8]; 

	MenuChoice pathOne[5] = {N, W, N, S, S};
	MenuChoice pathTwo[6] = {E, S, E, N, E, S}; // Two fails
	MenuChoice pathThree[13] = {N, E, E, N, W, E, S, E, N, S, N, E, S};

	Room *Outside = BuildTheMaze(allRooms);

	/* *************
	 * TEST ONE
	 *
	 * *************/
	std::cout << "====================   Test one  =====================" << std::endl;
	currentRoom = Outside->North; // By convention
	for (counter = 0; counter < 5; counter++)
	{
		PrintRoom(currentRoom, Enigmatic);
		currentRoom = getNextRoomFromDirection(currentRoom, pathOne[counter]); // TODO
	}
	if (currentRoom == Outside)
		std::cout << "Congratulations, you escaped the maze!" << std::endl;
	else 
	{
		std::cout << "Uh Oh. pathOne failed. Better look into that..." << std::endl;
	}
	/* *************
	 * TEST TWO
	 * *************/
	std::cout << "====================   Test two  =====================" << std::endl;
	currentRoom = Outside->North; // By convention
	for (counter = 0; counter < 6; counter++)
	{
		PrintRoom(currentRoom, Enigmatic);
		currentRoom = getNextRoomFromDirection(currentRoom, pathTwo[counter]); // TODO
	}
	if (currentRoom == Outside)
		std::cout << "Congratulations, you escaped the maze!" << std::endl;
	else 
	{
		std::cout << "Uh Oh. pathTwo failed. Better look into that..." << std::endl;
	}
	/* *************
	 * TEST THREE
	 *
	 * *************/
	std::cout << "===================   Test three  ====================" << std::endl;
	currentRoom = Outside->North; // By convention
	for (counter = 0; counter < 13; counter++)
	{
		PrintRoom(currentRoom, Enigmatic);
		currentRoom = getNextRoomFromDirection(currentRoom, pathThree[counter]); // TODO
	}
	if (currentRoom == Outside)
		std::cout << "Congratulations, you escaped the maze!" << std::endl;
	else 
	{
		std::cout << "Uh Oh. pathThree failed. Better look into that..." << std::endl;
	}

	for (int i=0; i < 8; i++)
	{
		delete(allRooms[i]);
	}
}

/*****************************************************************/
