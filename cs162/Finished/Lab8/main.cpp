#include <iostream>
#include <string>

#include "Functions.h"


//enum MenuChoice { N, S, E, W, unknown};
//char MenuOptions[] = {'N', 'S', 'E', 'W'};

/*****************************************************************/
main()
{
	bool Enigmatic = false;
	Room * currentRoom;
	Room* allRooms[8];

	std::cout << 
		"Do you want to turn on Enigmatic mode? No labels, no hints. (Y/N): ";
  Enigmatic = getUserYN();

	Room *Outside = BuildTheMaze(allRooms);
	currentRoom = Outside->North; // By convention
	while (currentRoom != Outside)
	{
		PrintRoom(currentRoom, Enigmatic);
		currentRoom = getNextRoom(currentRoom);
	}
	std::cout << "Congratulations, you escaped the maze!" << std::endl;

	for (int i=0; i < 8; i++)
	{
		delete(allRooms[i]);
	}
}

/*****************************************************************/
/*
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

*/
