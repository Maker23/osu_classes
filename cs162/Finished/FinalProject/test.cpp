#include <iostream>
#include <string>

#include "Room.h"
#include "Container.h"
#include "Thing.h"
#include "BuildTheEnvironment.h"


//enum MenuChoice { N, S, E, W, unknown};
//char MenuOptions[] = {'N', 'S', 'E', 'W'};

#define P1Len	9

MenuChoice pathOne[P1Len] = {W, N, S, E, E, N, E, S, N};
MenuChoice pathTwo[6] = {E, S, E, N, E, S}; // Two fails
MenuChoice pathThree[13] = {N, E, E, N, W, E, S, E, N, S, N, E, S};

void PathTestOne(Room * Start, bool Enigmatic);
void PathTestTwo(Room * Start, bool Enigmatic);
void PathTestThree(Room * Start, bool Enigmatic);
void Unlock();

void FunctionPointerTest();
bool FunctionOne(Container * unused=NULL);
bool FunctionTwo(Container * unused=NULL);
bool UnlockTeaChest(Container * unused=NULL);

/*****************************************************************/
main()
{
	bool Enigmatic = false;
	int counter=0;
	Room * currentRoom;
	Room* allRooms[24]; 
	Room *Start = BuildTheHouse(allRooms);
 	FillTheRooms(allRooms);
 
  currentRoom = Start;

	currentRoom->Print(Enigmatic);

	std::cout << std::endl;
	Container Bureau("Bureau", "It's a Chippendale");
	Bureau.Print();

/* ***************************************/

	Container TeaChest("Tea chest", "It has an ornate silver escutcheon around a keyhole.");


	TeaChest.Examine(counter);

	Thing* SilverSpoon = new Thing("silver spoon", "");
	Thing* SilverCanister = new Thing("silver canister full of tea", "");

	TeaChest.Contents.push_back(SilverSpoon);
	TeaChest.Contents.push_back(SilverCanister);
	TeaChest.Print();
	TeaChest.Examine(counter);

	PathTestOne(Start, Enigmatic);
	FunctionPointerTest();
	//PathTestTwo(Start, Enigmatic);
	//PathTestTwo(Start, Enigmatic);

	for (int i=0; i < 8; i++)
	{
		delete(allRooms[i]);
	}
}

/*****************************************************************/
/*****************************************************************/


void FunctionPointerTest()
{

	int myInt =0 ;

	Container TeaChest("Tea chest", "Set up for testing.");
	Thing* oneThing = new Thing("silver spoon", "");
	TeaChest.Contents.push_back(oneThing);

	std::cout << "===   Test One: TeaChest is open" << std::endl;
	TeaChest.Examine(myInt);

	std::cout << "===   Test two: TeaChest is locked, no open function is set" << std::endl;
	TeaChest.Open = false;
	TeaChest.Examine(myInt);

	std::cout << "===   Test three: TeaChest is locked with an OpenFunc defined" << std::endl;
	TeaChest.OpenFunc = FunctionOne;
	TeaChest.Examine(myInt);

	std::cout << "===   Test four: TeaChest is locked, OpenFunc defined but fails" << std::endl;
	TeaChest.OpenFunc = FunctionTwo;
	TeaChest.Examine(myInt);

	std::cout << "===   Test four: TeaChest is locked, OpenFunc is UnlockTeaChest" << std::endl;
	TeaChest.OpenFunc = UnlockTeaChest;
	TeaChest.Examine(myInt);

}

bool FunctionOne(Container * unused)
{
	std::cout << "One!" << std::endl;
	return true;
}
bool FunctionTwo(Container * unused)
{
	std::cout << "Two!" << std::endl;
	return false;
}
/*****************************************************************/
/*****************************************************************/
void Unlock()
{
	std::cout << "let's pretend I've unlocked the container" << std::endl;
}
void PathTestOne(Room * Start, bool Enigmatic)
{
	int counter;
	Room * currentRoom;

	std::cout << "====================   Test one  =====================" << std::endl;
	currentRoom = Start;
	for (counter = 0; counter < P1Len; counter++)
	{
		currentRoom->Print(Enigmatic);
		currentRoom = currentRoom->getNextRoomFromDirection(pathOne[counter]); // TODO
	}
	if (currentRoom == Start)
		std::cout << "Congratulations, you're back where you started!" << std::endl;
	else 
	{
		std::cout << "Uh Oh. pathOne failed. Better look into that..." << std::endl;
	}
}


void PathTestTwo(Room * Start, bool Enigmatic)
{
	int counter;
	Room * currentRoom;

	std::cout << "====================   Test two  =====================" << std::endl;
	currentRoom = Start->North; // By convention
	for (counter = 0; counter < 6; counter++)
	{
		currentRoom->Print(Enigmatic);
		currentRoom = currentRoom->getNextRoomFromDirection(pathTwo[counter]); // TODO
	}
	if (currentRoom == Start)
		std::cout << "Congratulations, you escaped the maze!" << std::endl;
	else 
	{
		std::cout << "Uh Oh. pathTwo failed. Better look into that..." << std::endl;
	}
}

void PathTestThree(Room * Start, bool Enigmatic)
{
	int counter;
	Room * currentRoom;

	std::cout << "===================   Test three  ====================" << std::endl;
	currentRoom = Start->North; // By convention
	for (counter = 0; counter < 13; counter++)
	{
		currentRoom->Print(Enigmatic);
		currentRoom = currentRoom->getNextRoomFromDirection(pathThree[counter]); // TODO
	}
	if (currentRoom == Start)
		std::cout << "Congratulations, you escaped the maze!" << std::endl;
	else 
	{
		std::cout << "Uh Oh. pathThree failed. Better look into that..." << std::endl;
	}
}


/*****************************************************************/
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
