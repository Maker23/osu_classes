#include <iostream> // for debugging
#include <list>
#include <string>

#include "Thing.h"
#include "Actions.h"

#ifndef _CONTAINER_H
#define _CONTAINER_H


class Container : public Thing {
public:

	Container (std::string Na, std::string St); // constructor
	virtual ~Container (); // destructor

	bool 	Open;
	int 	Capacity; // How much can it hold
	std::list<Thing*> Contents; // Objects held by container

	bool (*OpenFunc)(Container*);
	bool (*UseFunc)(AbstractRoom *, Container*);
	virtual int getCapacity() { return Capacity;}
	virtual std::vector<Thing*> Examine(int &counter, bool verbose=true, bool silent=false);
	virtual void Print();
	virtual Container * FindByPtr(Thing *);
	virtual Thing * FindByName(std::string);
};


class Holdall : public Container {
public:
	Holdall(std::string Na);
	~Holdall();

	bool GameTask[numGameTasks]; // GameTasks are defined in utilities.h

	int getGameTaskStatus();
	int getAvailableCapacity();	// Capacity - ThingsCarried = Available
	int getCapacity() { return Capacity;}
	std::vector<Thing*> Examine(int &counter, bool verbose=false, bool silent=false);
};


#endif // _CONTAINER_H
