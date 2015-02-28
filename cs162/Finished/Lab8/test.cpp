#include <iostream>
#include <string>

#include "Functions.h"

enum RoomIDs {A, B, C, D, F, G, H, Done };
Room* allRooms[8]; 

//enum MenuChoice { N, S, E, W, unknown};
//char MenuOptions[] = {'N', 'S', 'E', 'W'};

/*****************************************************************/
main()
{
	bool Enigmatic = false;
	int counter;
	Room * currentRoom;

	MenuChoice pathOne[5] = {N, W, N, S, S};
	MenuChoice pathTwo[4] = {E, N, E, S};
	MenuChoice pathThree[13] = {N, E, E, N, W, E, S, E, N, S, N, E, S};

	Room *Outside = BuildTheMaze();

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
	for (counter = 0; counter < 4; counter++)
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
Room * BuildTheMaze()
{
	Room* Outside = new Room("Outside");

	allRooms[A] = new Room("A");
	allRooms[B] = new Room("B");
	allRooms[C] = new Room("C");
	allRooms[D] = new Room("D");
	allRooms[F] = new Room("F");
	allRooms[G] = new Room("G");
	allRooms[H] = new Room("H");
	allRooms[Done] = Outside;
	
	Outside->North = allRooms[A];

	allRooms[A]->North = allRooms[B];
	allRooms[A]->East = allRooms[C];

	allRooms[B]->West  = allRooms[H];
	allRooms[B]->East  = allRooms[F];
	allRooms[B]->South = allRooms[A];

	allRooms[C]->North = allRooms[F];
	allRooms[C]->West  = allRooms[A];

	allRooms[D]->West  = allRooms[F];
	allRooms[D]->North = allRooms[G];
	allRooms[D]->South = allRooms[Done];

	allRooms[F]->West  = allRooms[B];
	allRooms[F]->East  = allRooms[D];
	allRooms[F]->South = allRooms[C];

	allRooms[G]->West  = allRooms[H];
	allRooms[G]->South = allRooms[D];

	allRooms[H]->East  = allRooms[B];
	allRooms[H]->North = allRooms[G];

	return Outside;
}

