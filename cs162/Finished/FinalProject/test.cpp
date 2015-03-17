/* vim:ts=2:
 *
 *                     Shoshana Abrass
 *                  CS162 Final Project
 *                     March 17, 2015
 *
 * File name: test.cpp
 *
 *
 * Overview:
 *   Automated testing of the program. 
 *
 *
 *
 */
#include <iostream>
#include <string>

#include "Room.h"
#include "Container.h"
#include "Thing.h"
#include "BuildTheEnvironment.h"


//enum MenuChoice { N, S, E, W, unknown};
//char MenuOptions[] = {'N', 'S', 'E', 'W'};


void UpdateGameState(int &Flags, int &GameClock, Holdall* PlayerBag, AbstractRoom* currentRoom);
void	CheckForTimers(AbstractRoom ** allRooms, int &GameClock, Holdall* PlayerBag);

MenuChoice pathOne[9] = {W, N, S, E, E, N, E, S, N};
MenuChoice pathTwo[6] = {E, S, E, N, E, S}; // Should fail
MenuChoice pathThree[13] = {N, E, E, N, W, E, S, E, N, S, N, E, S};

// Wins the game
std::string ActOne[31] = 
	{"S", "2", "N", "7", 			// Pick the roses, fill the vase
	 "E", "3", 								// Get the silver key
	 "W", "W", "5", 					// Get the watch
	 "N", "5", "6", "8", 			// Get the tea and the teapot
	 "S", "E", "E", "N",			// Move to the kitchen
	 "2", 										// Brew the tea
	 "5", "6","11", "13", 		// Mix the scones
	 "10", 										// put the scones in the oven
	 "7", "E", "6", "W",			// Get the honey
	 "11", "S", "W", "Q"};

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

// Test overfilling the player's bag
std::string ActFour[10] = 
	{"3", "5", "6", "W", "6", 
	 "7", "N", "8", "10", "Q",} ;

void PathTest(AbstractRoom * const Start, bool Enigmatic, MenuChoice *path, int numSteps);
void ActTest(AbstractRoom * Start, Holdall &PlayerBag, std::string *ActList, int numActs);
void UnitTests();

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
 

  PathTest(Start, false, pathOne, 9);
	std::cout << "Hit <return> to continue: ";
	getline(std::cin, nothing);


	ActTest(Start, PlayerBag, ActOne, 31);
	// Only one action test can be run at a time for now,
	// since the game state changes and isn't reset.
	// Simply uncomment the test you want to run.
	//
	//  ActTest(Start, PlayerBag, ActFour, 10);
	//	ActTest(Start, &PlayerBag, ActTwo, 13);
	//	ActTest(Start, &PlayerBag, ActThree, 13);
	std::cout << std::endl << "Hit <return> to continue: ";
	getline(std::cin, nothing);

	UnitTests();
	std::cout << "Hit <return> to continue: ";
	getline(std::cin, nothing);


	FunctionPointerTest();

	for (int i=0; i < 8; i++)
	{
		delete(allRooms[i]);
	}
}

/*****************************************************************/
/*****************************************************************/

void UnitTests()
{
	std::cout << "=================   Unit Tests  ==================" << std::endl;
	int counter=0;

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
}

void FunctionPointerTest()
{

	int myInt =0 ;

	std::cout << "=========== Function Pointer Tests  ==============" << std::endl;
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
/*****************************************************************/
/*****************************************************************/

void PathTest(AbstractRoom * const Start, bool Enigmatic, MenuChoice *path, int numSteps)
{
	int counter;
	AbstractRoom * currentRoom;
	currentRoom = Start;

	std::cout << "====================  Path Test  =====================" << std::endl;
	for (counter = 0; counter < numSteps; counter++)
	{
		currentRoom->Print(Enigmatic);
		currentRoom = currentRoom->getNextRoomFromDirection(path[counter]); 
	}
	if (currentRoom == Start)
		std::cout << "Congratulations, you're back where you started!" << std::endl;
	else 
	{
		std::cout << "Uh Oh. pathOne failed. Better look into that..." << std::endl;
	}
}

/*****************************************************************/
/*****************************************************************/
/*****************************************************************/

void ActTest(AbstractRoom * Start, Holdall &PlayerBag, std::string *ActList, int numActs)
{
	bool Enigmatic = false; // TODO: convert this to flags
	AbstractRoom * currentRoom;
	//AbstractRoom* allRooms[NumRooms];
	int GameClock = 0;
	int Flags = 0;

	PlayerBag.Capacity = 10;
	std::cout << "Player bag capacity = " << PlayerBag.Capacity << std::endl;

	//AbstractRoom* Start = BuildTheHouse(allRooms);
	//FillTheRooms(allRooms);

	//PlayerBag.Contents = EquipThePlayer();

	int MoveCounter = 0;
	std::string nothing;
	currentRoom = Start;

	while (GameClock < GameLength)
	{
		std::cout << std::endl;
		currentRoom->Print(Enigmatic);
		currentRoom = currentRoom->NextUserActionTest(&PlayerBag, ActList[MoveCounter++]);
		//currentRoom = currentRoom->NextUserAction(&PlayerBag);
		if (currentRoom == 0 ) break;
		if (MoveCounter >= numActs) break;
		if ( 0 )
		{
			// Turn this on for step-by-step walkthroughs
			std::cout << "Step " << MoveCounter << ", hit <return> to continue: ";
			getline(std::cin, nothing);
		}
		UpdateGameState(Flags, GameClock, &PlayerBag, currentRoom);
		CheckForTimers(allRooms, GameClock, &PlayerBag);
	}
	if (GameClock >= GameLength)
		std::cout << "It's 4:00. Your friends have arrived. You are out of time." << std::endl;

	int points = PlayerBag.getGameTaskStatus();

	std::cout << std::endl;
	if (points ==2)
		std::cout 
			<< "Success!" << std::endl
			<< "You met the rudimentary needs for a nice tea." << std::endl
			<< "Maybe next time you could do a little more to make it special." << std::endl
			<< "Your friends still like you. They'll come again." << std::endl;
	else if (points >2)
		std::cout 
			<< "Success!" << std::endl
		 	<< "Congratulations, you made a superbly nice tea!" << std::endl
			<< "Your friends tweet about it. Their pictures go viral." << std::endl
			<< "You're invited to BBC headquarters to meet the cast of" << std::endl
			<< "Pride&Prejudice. They hire you as a consulting writer."<< std::endl;
  else
		std::cout 
			<< "You did not succeed :(" << std::endl
			<< "You didn't meet the rudimentary needs for a nice tea." << std::endl
			<< "Your Tea Party is a failure. Your friends tweet about it." << std::endl
			<< "You are banned for life from Jane Austen Society meetings." << std::endl
			<< "You start reading Edward Gorey and listening to emo music." << std::endl;

}
