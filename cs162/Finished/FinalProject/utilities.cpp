/* vim:ts=2:
 *
 *                     Shoshana Abrass
 *                  CS162 Final Project
 *                     March 17, 2015
 *
 * File name: utilities.cpp
 *
 * Overview: 
 *   General functions used by both main.cpp and test.cpp to run 
 *   the game.
 *
 *
 *
 */

#include <iostream>
#include <string>

#include "utilities.h"
#include "Room.h"
#include "BuildTheEnvironment.h"


/* ***************************************************************
 * UpdateGameState - runs after every player turn
 *************************************************************** */
void UpdateGameState(int &Flags, int &GameClock, Holdall* PlayerBag, AbstractRoom* currentRoom)
{
  int points = PlayerBag->getGameTaskStatus();
	if (points == 2)
		std::cout << "You've prepared a minimalist Tea Party, but it could be nicer." << std::endl;

	GameClock++;
	// If the player is carrying the watch, print the time
  if ( CheckTheTime(PlayerBag) )
	{
		std::cout << "You have " << (GameLength - GameClock) * 5 << " minutes until 4:00" << std::endl;
	}
	// If the player is carrying a hat, update the game goal
  if ( HatInHand(PlayerBag) )
	{
		PlayerBag->GameTask[HatIsChosen] = true;
	}
	else
	{
		PlayerBag->GameTask[HatIsChosen] = false; // Don't put the hat down!
	}

}

/* ***************************************************************
 * CheckForTimers - runs after every player turn
 * TODO: could be called by UpdateGameState instead of from main()?
 *************************************************************** */
void	CheckForTimers(AbstractRoom ** allRooms, int &GameClock, Holdall * PlayerBag) 
{
	int timerLimit;
	int timer;
	for (int i=0; i < NumRooms; i++)
	{
		timerLimit = allRooms[i]->getTimerLimit();
		if (timerLimit)
		{
			// First increment for this turn
			allRooms[i]->setTimer(allRooms[i]->getTimer() + 1);

			// Then check the limit
			if (allRooms[i]->getTimer() >= timerLimit)
			{
				//std::cout << "ALARM: A timer is going off in the " << allRooms[i]->getName() << std::endl;
				if ( allRooms[i]->TimerFunc )
					allRooms[i]->TimerFunc(allRooms[i], GameClock);

				if ((allRooms[i]->getName()).compare("the Kitchen") == 0)
				{
					Container * OvenPtr = allRooms[i]->FindByName("Oven");
					OvenPtr->UseFunc((Room *)allRooms[i], PlayerBag);
				}
			}
		}
	}
}

/* ***************************************************************
 * Get Yes or No answer from user
 *************************************************************** */
bool getUserYN(const char Default)
{
	enum YNMenuChoice { y, n, YNunknown};
	char YNMenuOptions[] = {'y', 'n'};
	char menuOption;
	char inputBuffer[1024];

	if (TEST) 
	{
		std::cout << "TESTING getUserYN is always Yes" << std::endl;
		return true; // Always Yes for testing
	}

	bool Result=false;

	YNMenuChoice menuChoice = YNunknown;


  do {
  	menuOption = std::cin.get(); // get the first character
		std::cin.getline(inputBuffer,1024); // throw away anything else they typed

	  if ( ! menuOption )
			menuOption = Default; // TODO: Doesn't work, fix.
	
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
