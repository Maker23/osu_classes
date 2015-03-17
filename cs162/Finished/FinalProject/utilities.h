#ifndef _MAIN_H
#define _MAIN_H

//  Global debugging flags
#define DEBUG_EXAMINE false
#define DEBUG_FUNCTION false
#define DEBUG_MENU false
#define DEBUG_FIND false
#define DEBUG_ROOM false
#define DEBUG_USE false

#ifndef TEST
#define TEST false
#endif

#define GameLength 52	// Number of turns the user gets

#include <string>

class Container; // Forward declaration
class AbstractRoom; // Forward declaration
class Thing; // Forward declaration
class Holdall; // Forward declaration

bool getUserYN(const char Default);
std::string WriteTheInstructions();
std::string GetTheRecipeForScones();
void PrintResults (int GamePoints);
void UpdateGameState(int &Flags, int &GameClock, Holdall* PlayerBag, AbstractRoom* currentRoom);
void CheckForTimers(AbstractRoom ** allRooms, int &GameClock, Holdall* PlayerBag);
AbstractRoom * BuildTheMaze(AbstractRoom** allRooms);

// Ended up not having time to implement the use of this;
// still a good design pattern though
enum GameTaskMarker { TeaIsBrewed, SconesAreBaked, FlowersArePicked,
	HoneyIsGathered, HatIsChosen};

#define numGameTasks 5

#endif // _MAIN_H
