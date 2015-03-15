#include <iostream>
#include <string>
#include <list>
#include <vector>

#include "Thing.h"

#ifndef _Actions_H
#define _Actions_H

struct Actions {
	std::vector<Thing*> Things;
	std::vector<char> Moves;

	Actions(){
	}
};

#endif // _Actions_H
