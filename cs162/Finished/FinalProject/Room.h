#include <iostream>
#include <string>
#include <list>
#include <vector>

#include "Thing.h"
#include "Container.h"

#ifndef _Room_H
#define _Room_H
//enum RoomIDs {A, B, C, D, F, G, H, Done };
enum MenuChoice { N, S, E, W, unknown};


struct Choice;

class Room {
	bool firstView;
	std::string Name;
	std::string Story;
	void (*entryFunc)();
	Choice getUserMenuChoice(Actions* validActions);
	Room * FindByPtr(Thing *);
	void ChangeAThing(Thing* ActOnThing, Holdall * PlayerBag);

public:						
	// A lot of these are public for simplicity of maze setup
	// See the BuildTheEnvironment functions
	Room * North;
	Room * East;
	Room * South;
	Room * West;

	Actions Examine(int &counter);

	std::list<Thing*> ThingsHere;
	std::list<Container*> ContainersHere;
	void Print(bool Enigmatic);
	Room * NextUserAction(Holdall* PlayerBag);
	Room * getNextRoomFromDirection(MenuChoice nextChoice);
	//void ChangeAThing(Thing* ActOnThing, Holdall * PlayerBag);
	Container * FindByName(std::string);


  // constructor
	Room(std::string Na, std::string St);

	//TODO:  destructor will need to clear the vector of pointers but not delete the things
};
	
struct Choice {
	Room* nextRoom;
	Thing* ActOnThing;

	Choice(){
		nextRoom = NULL;
		ActOnThing = NULL;
	};
};


#endif // _Room_H
