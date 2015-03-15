#include <iostream> // for debugging
#include <list>
#include <string>

#include "Thing.h"
#include "Actions.h"

#ifndef _CONTAINER_H
#define _CONTAINER_H


class Container : public Thing {
public:

	std::list<Thing*> Contents;
	int 	Capacity; // How much can it hold
	bool 	Open;


	bool (*OpenFunc)(Container*);
	bool (*UseFunc)(Room *, Container*);
	virtual void Print();
	virtual std::vector<Thing*> Examine(int &counter, bool verbose=true);
	virtual Container * FindByPtr(Thing *);
	virtual Thing * FindByName(std::string);
	virtual int getCapacity() { return Capacity;}

	//Container (){};
	Container (std::string Na, std::string St);
};


class Holdall : public Container {
public:

	std::vector<Thing*> Examine(int &counter, bool verbose=false);
	int getAvailableCapacity();

	int getCapacity() { return Capacity;}
	Holdall(std::string Na);
};


#endif // _CONTAINER_H
