#include <iostream>
#include <string>

#include "Room.h"
#include "Container.h"
#include "Thing.h"

#ifndef _Environment_H
#define _Environment_H

#define NumRooms 13

enum RoomIDs {FrontLawn, FrontHall, Library, SunRm, DiningRm, Kitchen, Pantry,Garden, 
	StairUp, StairDown, Hallway, Bedrm, DressingRm, };

AbstractRoom * BuildTheHouse(AbstractRoom **allRooms);
void FillTheRooms(AbstractRoom **allRooms);
#endif // _Environment_H
/* OpenFunc Functions take a Container* */
bool UnlockTeaChest(Container *PlayerBag);
bool CheckTheTime(Container *PlayerBag);
/* TimerFunc Functions take a room and an integer */
void RingTheDoorbell(AbstractRoom * currentRoom, int currentTime);
/* UseFunc Functions take both a Room * and a Container* */
bool MixTheScones(AbstractRoom *currentRoom, Container *PlayerBag);
bool BakeTheScones(AbstractRoom *currentRoom, Container *PlayerBag);
bool BrewTheTea(AbstractRoom * currentRoom, Container *PlayerBag);
bool FillTheVase(AbstractRoom * currentRoom, Container *PlayerBag);
bool GatherHoney(AbstractRoom *currentRoom, Container *PlayerBag);
