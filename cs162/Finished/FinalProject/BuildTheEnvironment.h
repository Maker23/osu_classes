#include <iostream>
#include <string>

#include "Room.h"
#include "Container.h"
#include "Thing.h"

#ifndef _Environment_H
#define _Environment_H

enum RoomIDs {FrontLawn, FrontHall, Library, SunRm, DiningRm, Kitchen, Pantry,Garden, 
	StairUp, StairDown, Hallway, Bedrm, DressingRm, };

Room * BuildTheHouse(Room **allRooms);
void FillTheRooms(Room **allRooms);
#endif // _Environment_H
/* OpenFunc Functions take a Container* */
bool UnlockTeaChest(Container *PlayerBag);
bool GatherHoney(Container *PlayerBag);
bool CheckTheTime(Container *PlayerBag);
/* UseFunc Functions take both a Room * and a Container* */
bool MixTheScones(Room *currentRoom, Container *PlayerBag);
bool BakeTheScones(Room *currentRoom, Container *PlayerBag);
