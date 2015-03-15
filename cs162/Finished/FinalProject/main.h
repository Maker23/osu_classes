#ifndef _MAIN_H
#define _MAIN_H

#define DEBUG_EXAMINE false
#define DEBUG_FUNCTION false
#define DEBUG_MENU false
#define DEBUG_FIND false
#define DEBUG_ROOM true

class Container; // Forward declaration
class Room; // Forward declaration
class Thing; // Forward declaration

bool getUserYN(const char Default);
Room * BuildTheMaze(Room** allRooms);
std::string WriteTheInstructions();
std::string GetTheRecipeForScones();
#endif // _MAIN_H
