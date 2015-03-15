#include <iostream>
#include <string>
#include <vector>


#ifndef _THING_H
#define _THING_H

#include "main.h"

class Container; // Forward declaration
class Room; // Forward declaration

class Thing {
public:
	std::string Name;
	std::string Story;
	int Weight;
	bool isContainer;
	bool Open;

	bool (*UseFunc)(Room *, Container *);	//Does this thing do something? Most do not
	bool (*OpenFunc)(Container *); // Does this thing open? Most do not
	virtual void Print();
	virtual std::vector<Thing*> Examine(int &counter, bool verbose=true);
	virtual int getWeight() {return Weight;};
	Thing (std::string Na, std::string St);

	//Thing () {};
};

#endif // _THING_H
