#include <iostream>
#include <string>

#include "Room.h"
#include "Container.h"
#include "Thing.h"
#include "BuildTheEnvironment.h"


//enum MenuChoice { N, S, E, W, unknown};
//char MenuOptions[] = {'N', 'S', 'E', 'W'};

#define P1Len	9


void UpdateGameState(int &Flags, int &GameClock, Holdall* PlayerBag, AbstractRoom* currentRoom);
void	CheckForTimers(AbstractRoom ** allRooms, int &GameClock, Holdall* PlayerBag);

MenuChoice pathOne[P1Len] = {W, N, S, E, E, N, E, S, N};
MenuChoice pathTwo[6] = {E, S, E, N, E, S}; // Two fails
MenuChoice pathThree[13] = {N, E, E, N, W, E, S, E, N, S, N, E, S};

std::string ActOne[100] = 
	{"S", "2", "N", "E", "4",
	 "W", "W", "N", "5", "6",
	 "8", "S", "E", "E", "N",
	 "2", "5", "6","11", "13", // 13 is the bowl, 10 is the oven
	 "10","7", "E", "6", "W",
	 "11"
	 };

// Test opening the tea chest
std::string ActTwo[15] = 
	{"E", "3",  "W", "6", "W", 
	 "5", "6",  "N", "7", "8",
	 "10", "S", "E", "E", "N", };

// Test baking scones
std::string ActThree[13] = 
	{"E", "N",  "3", "4", "9", 
	 "11", "8",  "T", "T", "T", 
	 "8", "S", "W"};

void PathTestOne(AbstractRoom * Start, bool Enigmatic);
void PathTestTwo(AbstractRoom * Start, bool Enigmatic);
void PathTestThree(AbstractRoom * Start, bool Enigmatic);
void Unlock();

void ActTest(AbstractRoom * Start, Holdall * PlayerBag, std::string *ActList, int numActs);

void FunctionPointerTest();
bool FunctionOne(Container * unused=NULL);
bool FunctionTwo(Container * unused=NULL);
bool UnlockTeaChest(Container * unused=NULL);
AbstractRoom* allRooms[24]; 

/*****************************************************************/
main()
{
	bool Enigmatic = false;
	int counter=0;
	AbstractRoom * currentRoom;
	AbstractRoom *Start = BuildTheHouse(allRooms);
 	FillTheRooms(allRooms);
	std::string nothing;

	Holdall PlayerBag("Linen bag");
	PlayerBag.Capacity = 10;
 
  currentRoom = Start;
	currentRoom->Print(Enigmatic);


	/* ***************************************/

	std::cout << std::endl;
	std::cout << "=================   Unit Tests  ==================" << std::endl;
	Container Bureau("Bureau", "It's a Chippendale");
	Bureau.Print();
	Container TeaChest("Tea chest", "It has an ornate silver escutcheon around a keyhole.");


	TeaChest.Examine(counter);

	Thing* SilverSpoon = new Thing("silver spoon", "");
	Thing* SilverCanister = new Thing("silver canister full of tea", "");

	TeaChest.Contents.push_back(SilverSpoon);
	TeaChest.Contents.push_back(SilverCanister);
	TeaChest.Print();
	TeaChest.Examine(counter);

	std::cout << "Hit <return> to continue: ";
	getline(std::cin, nothing);
//	ActTest(Start, &PlayerBag, ActOne, 15);
//	ActTest(Start, &PlayerBag, ActTwo, 13);
	ActTest(Start, &PlayerBag, ActThree, 13);
	std::cout << "Hit <return> to continue: ";
	getline(std::cin, nothing);

	PathTestOne(Start, Enigmatic);
	std::cout << "Hit <return> to continue: ";
	getline(std::cin, nothing);
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
/*****************************************************************/
void ActTest(AbstractRoom * Start, Holdall * PlayerBag, std::string *ActList, int numActs)
{
	int counter;
	AbstractRoom * currentRoom;
	Choice chosenAction;
	int GameClock = 0;
	int Flags = 0;
	std::string nothing;

	std::cout << "=================   Action Test  ==================" << std::endl;
	currentRoom = Start;
	for (counter = 0; counter < numActs; counter++)
	{
		currentRoom->Print(false);
		currentRoom = currentRoom->NextUserActionTest(PlayerBag, ActList[counter]);
		UpdateGameState(Flags,GameClock,PlayerBag, currentRoom);
		CheckForTimers(allRooms, GameClock,PlayerBag);
		if (counter > 3 )
		{
			std::cout << "Step " << counter << ", hit <return> to continue: ";
			getline(std::cin, nothing);
		}
	}
	if (currentRoom == Start)
		std::cout << "Congratulations, you're back where you started!" << std::endl;
	else 
	{
		std::cout << "Uh Oh. ActList failed. Better look into that..." << std::endl;
	}
}
/*****************************************************************/

void PathTestOne(AbstractRoom * Start, bool Enigmatic)
{
	int counter;
	AbstractRoom * currentRoom;

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

/*****************************************************************/

void PathTestTwo(AbstractRoom * Start, bool Enigmatic)
{
	int counter;
	AbstractRoom * currentRoom;

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

void PathTestThree(AbstractRoom * Start, bool Enigmatic)
{
	int counter;
	AbstractRoom * currentRoom;

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
bool NotgetUserYN(const char Default)
{
	enum YNMenuChoice { y, n, YNunknown};
	char YNMenuOptions[] = {'y', 'n'};
	char menuOption;
	char inputBuffer[1024];


  if (TEST) return true;

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
