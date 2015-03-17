#ifndef _MAIN_H
#define _MAIN_H

#define DEBUG_EXAMINE false
#define DEBUG_FUNCTION false
#define DEBUG_MENU false
#define DEBUG_FIND false
#define DEBUG_ROOM false
#define DEBUG_USE false

#ifndef TEST
#define TEST false
#endif

#define GameLength 36

#include <string>

class Container; // Forward declaration
class Room; // Forward declaration
class Thing; // Forward declaration

bool getUserYN(const char Default);
Room * BuildTheMaze(Room** allRooms);
std::string WriteTheInstructions();
std::string GetTheRecipeForScones();

enum GameTaskMarker {
	TeaIsBrewed,
	SconesAreBaked,
	FlowersArePicked,
	HoneyIsGathered,
	HatIsChosen};

#define numGameTasks 5

#endif // _MAIN_H
