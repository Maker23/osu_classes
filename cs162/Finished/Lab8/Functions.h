#include <iostream>
#include <string>

struct Room {
	std::string Name;
	Room * North;
	Room * East;
	Room * South;
	Room * West;

  // constructor
	Room(std::string Na) {
		Name=Na;
		North = NULL;
		East = NULL;
		South = NULL;
		West = NULL;
	}
};
	
enum RoomIDs {A, B, C, D, F, G, H, Done };
enum MenuChoice { N, S, E, W, unknown};

MenuChoice getUserMenuChoice();
bool getUserYN();
Room * BuildTheMaze(Room** allRooms);
Room * getNextRoom( Room * currentRoom);
Room * getNextRoomFromDirection( Room * currentRoom, MenuChoice nextChoice);
void PrintRoom(Room * currentRoom, bool Enigmatic);

