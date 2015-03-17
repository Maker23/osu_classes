/* vim:ts=2:
 *
 *                     Shoshana Abrass
 *                  CS162 Final Project
 *                     March 17, 2015
 *
 * File name: main.cpp
 *
 * Overview:
 *   This file initializes the environment and the player, 
 *   and runs the outer game loop.  The outer loop moves the
 *	 player from room to room until the GameClock runs out or
 *	 the player chooses "Quit".  It ends by printing out the
 *	 GamePoints results and freeing all memory.
 *
 */

#include <iostream>
#include <string>

#include "utilities.h"  // Global settings and functions declared here
#include "Room.h"
#include "BuildTheEnvironment.h"


/***************************/
main()
{
	bool Enigmatic = false; // TODO: convert this to flags
	AbstractRoom * currentRoom;
	AbstractRoom* allRooms[NumRooms];
	int GameClock = 0;
	int Flags = 0;

	Holdall PlayerBag("Linen bag");
	PlayerBag.Capacity = 10;
	//PlayerBag.Contents = EquipThePlayer();
	std::cout << "Player bag capacity = " << PlayerBag.Capacity << std::endl;

	AbstractRoom* Start = BuildTheHouse(allRooms);
	FillTheRooms(allRooms);

  // The top-level game loop. Stop when the GameClock reaches the limit,
	// or when a NULL nextroom is returned (the Quit option does this)
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
	if (GameClock >= GameLength)
		std::cout << "It's 4:00. Your friends have arrived for tea. You are out of time." 
			<< std::endl;

	// Game over!
	// Count up points based on GameTasks completed; print the results
	int points = PlayerBag.getGameTaskStatus();
	PrintResults(points);

 	// Free ALL the memory!
	for (int i=0; i < NumRooms; i++)
	{
		delete(allRooms[i]);
	}
}

/* ************************************************************ */
void PrintResults (int GamePoints)
{
	std::cout << std::endl;
	if (GamePoints ==2)
		std::cout 
			<< "Success!" << std::endl
			<< "You met the rudimentary needs for a nice tea." << std::endl
			<< "Maybe next time you could do a little more to make it special." << std::endl
			<< "Your friends still like you. They'll come again." << std::endl;
	else if (GamePoints >2)
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
