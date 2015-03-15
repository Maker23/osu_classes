#include <iostream>
#include <cstring>
#include <string>
#include <list>

#include "main.h"
#include "Room.h"


/* ***********************************************************
 * Constructor
 * ********************************************************* */
Room::Room(std::string Na, std::string St) {
	Name=Na;
	Story=St;
	North = NULL;
	East = NULL;
	South = NULL;
	West = NULL;

	firstView = true;
	entryFunc = NULL;
}

/*************************************************************
 * NextUserAction is the primary public function for Room:: 
 *
 * ********************************************************* */
Room * Room::NextUserAction(Holdall *PlayerBag)
{
	int counter = 1; // Begin each turn with 1
	std::vector<Thing*> backpackContents;
	Actions possibleActions;
	Choice 	chosenAction;
	Room *nextRoom;

	backpackContents = PlayerBag->Examine(counter, true);
	possibleActions = this->Examine(counter);
	possibleActions.Things.insert(possibleActions.Things.begin(), backpackContents.begin(),backpackContents.end());
	chosenAction = getUserMenuChoice(&possibleActions);

	if ( chosenAction.ActOnThing != NULL )
	{
		ChangeAThing(chosenAction.ActOnThing, PlayerBag);
	}

	return chosenAction.nextRoom;
}

/*************************************************************
 *
 * This is where all the game logic takes place. In this function
 * we have access to the currentRoom and the PlayerBag so we
 * can move items around and test a wide range of conditions.
 *
 *	 First we collect the state of the Object the user has chosen
 *	 to act on; we run FindByPtr() against the Room and PlayerBag
 *	 to determine where the object is.
 *	
 *	 If the object has an open function, offer to open.
 *	 If the object has an use function, offer to use.
 *	 If the object is in the room, offer to pick it up.
 *	 If the object is in the player bag, offer to put it down
 *
 *  From here we can call the UseFunctions and OpenFunctions
 *  and pass all the necessary info.
 *
 *  This function has no return value
 * ********************************************************* */
void Room::ChangeAThing(Thing* ActOnThing, Holdall * PlayerBag)
{
	Container * ActOnCont; // Unbelievable
	
	if (DEBUG_ROOM) std::cout << "DEBUG: Here's where the magic happens!" << std::endl
		<< "DEBUG: Doing something to " << ActOnCont->Name << " in Room " << this->Name 
		<< " with holdall " << PlayerBag->Name << std::endl;

	bool OpenSuccess = false;
	bool UseSuccess = false;
	std::list<Container*>::iterator iterCont;
	std::vector<Thing*> backpackContents;
	std::vector<Thing*>::iterator iterThing;
	bool Answer;
	Room * InRoom = this->FindByPtr(ActOnCont);
	Container * OnPerson = PlayerBag->FindByPtr(ActOnCont);
	Container * InContainer;

	// OFFER TO OPEN
	if (DEBUG_ROOM) std::cout << "ActOnCont->isContianer = " << ActOnCont->isContainer << std::endl;
	if (DEBUG_ROOM) std::cout << "ActOnCont->Open = " << ActOnCont->Open << std::endl;
	if (DEBUG_ROOM) std::cout << "ActOnCont->OpenFunc = " << ActOnCont->OpenFunc << std::endl;
	if (DEBUG_ROOM) std::cout << "ActOnCont->UseFunc = " << ActOnCont->UseFunc << std::endl;
	int foo=0;
  if ( ActOnCont->isContainer && ! ActOnCont->Open )
	{
  	if (ActOnCont->OpenFunc != NULL) 
		{
			if (DEBUG_ROOM) std::cout << "DEBUG: Running OpenFunc on " << ActOnCont->Name << std::endl;
			OpenSuccess = ActOnCont->OpenFunc(PlayerBag);
			if (OpenSuccess) 
			{
				std::cout << "	    You opened the " << ActOnCont->Name << "!" << std::endl;
				ActOnCont->Open = true;
			}
			else
			{
				std::cout << "	    The " << ActOnCont->Name << " didn't open." << std::endl;
			}
		}
		else if (ActOnCont->OpenFunc == NULL)
		{
			// Only useful for debugging
			if (DEBUG_ROOM) std::cout << "DEBUG: Got NULL OpenFunc for " << ActOnCont->Name 
				<< " (Room::ChangeAThing)" << std::endl;
		}
	}
	if (OpenSuccess) return;
	if (DEBUG_ROOM) std::cout << "Keep going after open try" << std::endl;

	// OFFER TO USE
 	//ActOnThing = (Thing *) ActOnCont;
 	if (ActOnThing->UseFunc != NULL) 
	{
		if (DEBUG_ROOM) std::cout << "ActOnThing UseFunc" << std::endl;
		UseSuccess = ActOnThing->UseFunc(this, PlayerBag);
	}
 	else if (ActOnThing->isContainer && ActOnCont->UseFunc != NULL) 
	{
		if (DEBUG_ROOM) std::cout << "ActOnContainer UseFunc" << std::endl;
		UseSuccess = ActOnCont->UseFunc(this, PlayerBag);
		//Containers can have use functions....
	}
 	else
	{
		// Only useful for debugging
		if (DEBUG_FUNCTION) std::cout << "DEBUG: Got NULL UseFunc for " << ActOnThing->Name
				<< " (Room::ChangeAThing)" << std::endl;
	}
	if (UseSuccess) return;
	if (DEBUG_ROOM) std::cout << "Keep going after use try" << std::endl;
	
	// Return or keep going?  TODO: make a decision
	// Maybe IF we've opened or used it, print it.  Then return to menu. Else continue

	// Print the thing
	ActOnCont->Examine(foo);
	if ( OnPerson  )
	{
		if (DEBUG_ROOM) std::cout << "DEBUG: Found " << ActOnCont->Name << " on Player " << PlayerBag->Name;
		std::cout << "You are carrying the " << ActOnCont->Name << "." << std::endl;
		std::cout << "Do you want to put the " << ActOnCont->Name << " down? [Yn]: ";
		Answer = getUserYN('Y');
		if (Answer){
			OnPerson->Contents.remove(ActOnCont);
			if (ActOnCont->isContainer)
			{
				this->ContainersHere.push_front((Container *)ActOnCont);
			}
			else
			{
				this->ThingsHere.push_front(ActOnCont);
			}
			//std::cout << "BOOyeah!!" << std::endl;
		}
	}
	else if ( InRoom )
	{
		// The object is inside the room, and probably a container
		if (DEBUG_ROOM) std::cout << "DEBUG: Found " << ActOnCont->Name << " in Room " << this->Name;
		std::cout << "Do you want to pick the " << ActOnCont->Name << " up? [Yn]: ";
		Answer = getUserYN('Y');
		if (Answer){
		 	// Check capacity
			// TODO: This should be a Holdall::function
			int PlayerBagCapacity = PlayerBag->getCapacity();
			int ItemWeight = ActOnCont->getWeight();
			if (ItemWeight > PlayerBagCapacity) 
			{
				std::cout << ActOnCont->Name << " is too big for the " << PlayerBag->Name << std::endl;
			}
			else
			{
				int roomLeft = PlayerBag->getAvailableCapacity();
				std::cout << "DEBUGGING: roomLeft is " << roomLeft <<std::endl;
				if (ItemWeight > roomLeft)
				{
					std::cout << "You don't have enough room in the " << PlayerBag->Name 
						<< " to carry the " << ActOnCont->Name << std::endl
						<< "You'll have to put something down." << std::endl;
				}
				else
				{
					if (ActOnCont->isContainer)
					{
						this->ContainersHere.remove((Container *)ActOnCont);
					}
					else
					{
						this->ThingsHere.remove(ActOnCont);
					}
					PlayerBag->Contents.push_front(ActOnCont);
				}
			}
		}
	}
	else 
	{
		// The object is inside a container inside the room.
  	if ( ContainersHere.size() != 0 ) 
		{
			for (iterCont=ContainersHere.begin(); iterCont != ContainersHere.end(); iterCont++)
			{
				if (DEBUG_ROOM) std::cout << "DEBUG: Looking in " <<  (*iterCont)->Name << " for " << ActOnCont->Name << std::endl;
				if ( InContainer = (*iterCont)->FindByPtr(ActOnCont) )
				{
					if (DEBUG_ROOM) std::cout << "DEBUG: Found " << ActOnCont->Name << " in Container " << (*iterCont)->Name;
					std::cout << "Do you want to pick the " << ActOnCont->Name <<" up? [Yn]: ";
					Answer = getUserYN('Y');
					if (Answer){
						int ItemWeight = ActOnCont->getWeight();
						int roomLeft = PlayerBag->getAvailableCapacity();
						std::cout << "DEBUGGING: roomLeft is " << roomLeft <<std::endl;
						if (ItemWeight > roomLeft)
						{
							std::cout << "You don't have enough room in the " << PlayerBag->Name 
								<< " to carry the " << ActOnCont->Name << std::endl
								<< "You'll have to put something down." << std::endl;
						}
						else
						{
							InContainer->Contents.remove(ActOnCont);
							PlayerBag->Contents.push_front(ActOnCont);
							//std::cout << "oh SNAP!!!" << std::endl;
						}
					}
					break;
				}
			}
		}
	}
}

/*****************************************************************/
Room * Room::getNextRoomFromDirection(MenuChoice nextChoice)
{
	bool error = false;
	Room * nextRoom = NULL;

	/*
 	if (currentRoom == NULL ) 
	{
		std::cout << "Can't proceed from a NULL room" << std::endl;
		return NULL;
	}
	*/
	switch (nextChoice) {
		case N:
			nextRoom = this->North;
			std::cout << "  Going North" << std::endl;
			break;
		case S:
			nextRoom = this->South;
			std::cout << "  Going South" << std::endl;
			break;
		case E:
			nextRoom = this->East;
			std::cout << "  Going East" << std::endl;
			break;
		case W:
			nextRoom = this->West;
			std::cout << "  Going West" << std::endl;
			break;
		case unknown:
			std::cout << "Unrecognized direction" << std::endl;
			error=true;
			break;
	}
	if ( error == false && nextRoom == NULL ){
		std::cout << "Sorry, you can't go that way." << std::endl;
		nextRoom = this;	
	}
	return(nextRoom);
}

/*****************************************************************/
void Room::Print(bool Enigmatic)
{
	std::string Conjunction = "";
	int counter = 1;
  
	std::cout << "You are in ";
	Enigmatic? std::cout << "a room": std::cout << this->Name;
	std::cout << "." << std::endl;
	std::cout << this->Story;
	std::cout << std::endl;

	std::list<Thing*> itemList;
	std::vector<char> moveList;

	if (firstView) 
	{
		//if ( ! Enigmatic) 
			//this->Examine(counter);
			//itemList = this->Examine(counter);
		firstView = false;
	}
}
Room * Room::FindByPtr(Thing * SeekingThingPtr)
{
  if ( ThingsHere.size() != 0 ) 
	{
		std::list<Thing*>::iterator iterThing;
		for (iterThing=ThingsHere.begin(); iterThing != ThingsHere.end(); iterThing++)
		{
			if ( (*iterThing) == SeekingThingPtr)
				return this;
		}
	}
  if ( ContainersHere.size() != 0 ) 
	{
		std::list<Container*>::iterator iterCont;
		for (iterCont=ContainersHere.begin(); iterCont != ContainersHere.end(); iterCont++)
		{
			if ( (*iterCont) == SeekingThingPtr)
				return this;
		}
	}
	return ((Room *) 0);
}
Container * Room::FindByName(std::string SeekingThingName)
{
	// Only looks for conatiners.  Sigh
  if ( ContainersHere.size() != 0 ) 
	{
		std::list<Container*>::iterator iterCont;
		for (iterCont=ContainersHere.begin(); iterCont != ContainersHere.end(); iterCont++)
		{
			if ( ((*iterCont)->Name).compare(SeekingThingName) == 0)
				return (*iterCont);
		}
	}
	return ((Container *) 0);
}
/*****************************************************************/

Actions Room::Examine(int &counter)
{
	std::string Conjunction = "";
	std::list<Thing*>::iterator iterThing;
	std::list<Container*>::iterator iterCont;
	Actions myActions;

	std::vector<char> moveList;
	std::vector<Thing*>	thingList;
	std::vector<Thing*>	tmpthingList;

	bool Enigmatic = false;//TODO

  if (DEBUG_EXAMINE) std::cout  << "DEBUG: beginning Room::Examine " << std::endl;
  if ( ContainersHere.size() != 0 ) 
	{
		std::cout << "	You see  " << std::endl;
		for (iterCont=ContainersHere.begin(); iterCont != ContainersHere.end(); iterCont++)
		{
			std::cout << "	"<< counter++ << ".  " << (*iterCont)->Name << std::endl;
			thingList.push_back((*iterCont));
			if ( (*iterCont)->Open == true )
			{
				tmpthingList = (*iterCont)->Examine(counter);
				thingList.insert(thingList.end(), tmpthingList.begin(),tmpthingList.end());
			}
		}
	}
  if ( ThingsHere.size() != 0 ) 
	{
		for (iterThing=ThingsHere.begin(); iterThing != ThingsHere.end(); iterThing++)
		{
			thingList.push_back((*iterThing));
			std::cout << "	"<< counter++ << ".  " << (*iterThing)->Name << std::endl;
		}
	}
	if (! Enigmatic ){
		std::cout << "You can move ";
		if (this->North != NULL)
		{
			moveList.push_back('N');
			std::cout << Conjunction + "North"; 
			Conjunction=" or ";
		}
		if (this->East != NULL)
		{
			moveList.push_back('E');
			std::cout << Conjunction + "East"; 
			Conjunction=" or ";
		}
		if (this->South != NULL)
		{
			moveList.push_back('S');
			std::cout << Conjunction + "South"; 
			Conjunction=" or ";
		}
		if (this->West != NULL)
		{
			moveList.push_back('W');
			std::cout << Conjunction + "West"; 
		}
	}
	myActions.Things = thingList;
	myActions.Moves = moveList;
  if (DEBUG_EXAMINE) std::cout  << "DEBUG: ending    Room::Examine " << std::endl;

	return myActions;
}

/*****************************************************************/
Choice Room::getUserMenuChoice(Actions* validActions)
{

	char MoveOptions[] = {'N', 'S', 'E', 'W'};
	char HelpOption = 'H';
	char QuitOption = 'Q';

	char menuLetter;
	Choice chosenAction;
	MenuChoice menuChoice; // TODO: wtf?

	std::string inputString;
	char inputChars[1024];
	int inputInt;
 
  //  Print out the menu of Things to interact with
	if ( DEBUG_MENU )
	{
		for (int i=0; i< validActions->Things.size(); i++)
  	{		
			std::cout << i+1 << "DEBUG: " << (validActions->Things[i])->Name << std::endl;
		}
	}
	std::cout << std::endl << "What do you want to do? ( ";
	for (int i=0; i< validActions->Things.size(); i++)
  {		
		std::cout << i+1 << " ";
	}

  //  Print out the menu of Moves that are possible
	for (int i=0; i< validActions->Moves.size(); i++)
  {		
		std::cout << validActions->Moves[i] << " ";
	}
	std::cout << "H Q):  ";

	chosenAction.nextRoom = this; // By default, the room stays the same

	getline(std::cin, inputString);
	std::strcpy (inputChars, inputString.c_str());
	if ( ( inputChars[0] >= 65 && inputChars[0] <=90)
		|| ( inputChars[0] >= 97 && inputChars[0] <=122))
	{
		if (DEBUG_MENU) std::cout << "This seems to be a letter: "<< inputChars[0] << std::endl;
		menuLetter = toupper(inputChars[0]);

		if (menuLetter == HelpOption )
		{
			std::cout << "You seem to remember that you have something to do today, but you" << std::endl; // TODO
			std::cout << "can't remember what it is.  You're usually pretty organized. Maybe" << std::endl;
			std::cout << "you left yourself a note." << std::endl;
		}
		else if (menuLetter == QuitOption )
		{
			std::cout << "Quitting" << std::endl; // TODO
		}

		for (int j=0; j < validActions->Moves.size(); j++)
		{
			if (toupper(menuLetter) == validActions->Moves[j] )
			{
				for (int i=0; i < 5; i++)
				{
					if (validActions->Moves[j] == MoveOptions[i])
					{
						menuChoice = (MenuChoice) i;
						chosenAction.nextRoom = getNextRoomFromDirection(menuChoice);
					}
				}
			}
		}
	}
  else
	{
		std::string::size_type sz;
		inputInt = std::stoi(inputString, &sz );
		if (DEBUG_MENU) std::cout << "This seems to be a number: "<< inputInt << std::endl;
		if ( (inputInt - 1) >= 0 && ((inputInt - 1) < validActions->Things.size()))
		{
			if (DEBUG_MENU) std::cout << "HEREUPON I am choosing item " << inputInt << std::endl;
			chosenAction.ActOnThing = (validActions->Things[inputInt-1]);
			//std::cout << (validActions->Things[inputInt-1])->Name << std::endl;
		}
	}

	// If it's a valid number
	// Else if it's a valid number
	// Else, you know, complain.
	// TODO: handle help and quit here
	std::cout << std::endl << std::endl;
	return chosenAction;
}
