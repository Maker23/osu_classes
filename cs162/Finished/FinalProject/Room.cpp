#include <iostream>
#include <cstring>
#include <string>
#include <list>

#include "utilities.h"
#include "Room.h"


/* ***********************************************************
 * Constructors
 * ********************************************************* */

Room::Room(std::string Na, std::string St): AbstractRoom() 
{
	Name=Na;
	Story=St;
	North = NULL;
	East = NULL;
	South = NULL;
	West = NULL;

	FirstView = true;
	EntryFunc = NULL;
}

TimerRoom::TimerRoom(std::string Na, std::string St): Room(Na, St) 
{
	Timer = 0;
	TimerLimit = 0;
	TimerFunc = NULL;
}

OutsideRoom::OutsideRoom(std::string Na, std::string St) : Room (Na, St)
{
	Weather = "";
}

/* ***********************************************************
 * Destructors
 * ********************************************************* */
Room::~Room()
{
	std::list<Container*>::iterator iterCont;
	std::list<Thing*>::iterator iterThing;

	for (iterCont=ContainersHere.begin(); iterCont != ContainersHere.end(); iterCont++)
	{
		delete (*iterCont);
	}
	for (iterThing=ThingsHere.begin(); iterThing != ThingsHere.end(); iterThing++)
	{
		delete (*iterThing);
	}
}

TimerRoom::~TimerRoom()
{
	// No dynamic memory beyond the Room base class
}

OutsideRoom::~OutsideRoom()
{
	// No dynamic memory beyond the Room base class
}

/*************************************************************
 * NextUserAction is the primary public function for Room:: 
 *
 * ********************************************************* */
AbstractRoom * Room::NextUserAction(Holdall *PlayerBag)
{
	int counter = 1; // Begin each turn with 1
	std::vector<Thing*> backpackContents;
	Actions possibleActions;
	Choice 	chosenAction;
	Room *nextRoom;

  if (DEBUG_FUNCTION) std::cout << "===== begin Room::NextUserAction" << std::endl;
	backpackContents = PlayerBag->Examine(counter, true);
	possibleActions = this->Examine(counter);
	possibleActions.Things.insert(possibleActions.Things.begin(), backpackContents.begin(),backpackContents.end());
	chosenAction = getUserMenuChoice(&possibleActions);

	if ( chosenAction.ActOnThing != NULL )
	{
		ChangeAThing(chosenAction.ActOnThing, PlayerBag);
	}

  if (DEBUG_FUNCTION) std::cout << "===== end Room::NextUserAction" << std::endl;
	return chosenAction.nextRoom;
}

AbstractRoom * Room::NextUserActionTest(Holdall *PlayerBag, std::string TestAction)
{
	int counter = 1; // Begin each turn with 1
	std::vector<Thing*> backpackContents;
	Actions possibleActions;
	Choice 	chosenAction;
	Room *nextRoom;

  if (DEBUG_FUNCTION) std::cout << "===== begin Room::NextUserActionTest" << std::endl;
	backpackContents = PlayerBag->Examine(counter, true);
	possibleActions = this->Examine(counter);
	possibleActions.Things.insert(possibleActions.Things.begin(), backpackContents.begin(),backpackContents.end());
	chosenAction = getUserMenuChoice(&possibleActions, TestAction);

	if ( chosenAction.ActOnThing != NULL )
	{
		ChangeAThing(chosenAction.ActOnThing, PlayerBag);
	}

  if (DEBUG_FUNCTION) std::cout << "===== end Room::NextUserActionTest" << std::endl;
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
	Container * ActOnCont = (Container*) ActOnThing; // Unbelievable
	
  if (DEBUG_FUNCTION) std::cout << "===== begin Room::ChangeAThing" << std::endl;
	if (DEBUG_ROOM) std::cout << "DEBUG: Here's where the magic happens!" << std::endl
		<< "DEBUG: Doing something to " << ActOnThing->Name <<  " in Room " << this->Name 
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
	if (DEBUG_ROOM || DEBUG_FUNCTION) std::cout << "Keep going after OPEN try" << std::endl;

	// OFFER TO USE
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
	if (DEBUG_ROOM || DEBUG_FUNCTION) std::cout 
		<< "Keep going after USE try" << std::endl;
	
	// IF we've succesfully opened or used it, return to menu. Else continue

  if (DEBUG_FUNCTION) std::cout
		<< "===== start the search Room::ChangeAThing" << std::endl;
	// Print the thing
	int foo=0;
	ActOnCont->Examine(foo);
	if ( OnPerson  )
	{
		if (DEBUG_ROOM || DEBUG_FUNCTION) std::cout 
			<< "DEBUG: Found " << ActOnCont->Name << " on Player " << PlayerBag->Name;
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
  	if (DEBUG_ROOM || DEBUG_FUNCTION) std::cout 
			<< "===== found InRoom, Room::ChangeAThing" << std::endl;
		// The object is inside the room, and probably a container
		if (DEBUG_ROOM) std::cout << "DEBUG: Found " 
			<< ActOnCont->Name << " in Room " << this->Name;
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
  	if (DEBUG_ROOM || DEBUG_FUNCTION) std::cout 
			<< "===== inside a container inside the room, Room::ChangeAThing" 
			<< std::endl;
		// The object is inside a container inside the room.
  	if ( ContainersHere.size() != 0 ) 
		{
			for (iterCont=ContainersHere.begin(); iterCont != ContainersHere.end(); iterCont++)
			{
				if (DEBUG_ROOM) std::cout << "DEBUG: Looking in " 
					<<  (*iterCont)->Name << " for " << ActOnCont->Name << std::endl;
				if ( InContainer = (*iterCont)->FindByPtr(ActOnCont) )
				{
					if (DEBUG_ROOM) std::cout << "DEBUG: Found " 
						<< ActOnCont->Name << " in Container " << (*iterCont)->Name;
					std::cout << "Do you want to pick the " << ActOnCont->Name <<" up? [Yn]: ";
					Answer = getUserYN('Y');
					if (Answer){
						int ItemWeight = ActOnCont->getWeight();
						int roomLeft = PlayerBag->getAvailableCapacity();
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
						}
					}
					break;
				}
			}
		}
	}
}

/*****************************************************************/
AbstractRoom * Room::getNextRoomFromDirection(MenuChoice nextChoice)
{
	bool error = false;
	AbstractRoom * nextRoom = NULL;

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
	std::string Weather = getWeather();
  
	std::cout << "You are in ";
	Enigmatic? std::cout << "a room": std::cout << this->Name;
	std::cout << "." << std::endl;
	if ( (this->Story.compare("") !=0 ) && FirstView)
	{
		std::cout << this->Story;
		std::cout << std::endl;
	}
	if ( Weather.compare("") !=0 && FirstView)
	{
		std::cout << "The weather is " << getWeather() << std::endl;
	}

	std::list<Thing*> itemList;
	std::vector<char> moveList;

	if (FirstView) 
	{
		FirstView = false;
	}
}
Room * Room::FindByPtr(Thing * SeekingThingPtr)
{
  if (DEBUG_FUNCTION) std::cout << "===== begin Room::FindByPtr" << std::endl;
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
  if (DEBUG_FUNCTION) std::cout << "===== begin Room::FindByName" << std::endl;
	// Only looks for containers.  Sigh
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

  if (DEBUG_EXAMINE || DEBUG_FUNCTION) std::cout 
		<< "===== begin Room::Examine" << std::endl;
	
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
  if (DEBUG_EXAMINE || DEBUG_FUNCTION) std::cout 
		<< "===== end Room::Examine" << std::endl;

	return myActions;
}

/*****************************************************************/
Choice Room::getUserMenuChoice(Actions* validActions, std::string TestAction)
{

	char MoveOptions[] = {'N', 'S', 'E', 'W'};
	char HelpOption = 'H';
	char QuitOption = 'Q';
	char TestNullOption = 'T';

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

	if (TEST)
	{
		std::cout << "TESTING: User Menu Choice is " << TestAction << std::endl;
		inputString = TestAction;
	}
	else
	{
		getline(std::cin, inputString);
	}

	if ( inputString.compare("") == 0 )
		return chosenAction;

	std::strcpy (inputChars, inputString.c_str());
	if ( ( inputChars[0] >= 65 && inputChars[0] <=90)
		|| ( inputChars[0] >= 97 && inputChars[0] <=122))
	{
		if (DEBUG_MENU) std::cout << "This seems to be a letter: "<< inputChars[0] << std::endl;
		menuLetter = toupper(inputChars[0]);

		if (menuLetter == TestNullOption )
		{
			// Do Nothing.  This allows timers to cycle forward whle the user waits
		}
		else if (menuLetter == HelpOption )
		{
			// TODO: do we have the notebook?
			std::cout << "You seem to remember that you have something to do today, but you" << std::endl; 
			std::cout << "can't remember what it is.  You're usually pretty organized. Maybe" << std::endl;
			std::cout << "you left yourself a note. Look around." << std::endl;
		}
		else if (menuLetter == QuitOption )
		{
			std::cout << "Quitting..." << std::endl; //
			chosenAction.nextRoom = (AbstractRoom *)0;
			return chosenAction;
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
