#include <iostream>
#include <string>
#include <list>
#include <vector>

#include "Thing.h"
#include "Container.h"

#ifndef _Room_H
#define _Room_H
//enum RoomIDs {A, B, C, D, F, G, H, Done };
enum MenuChoice { N, S, E, W, unknown};


struct Choice; // Forward declaration

/* ********************************************************
 *
 * ****************************************************** */
class AbstractRoom {

protected:
	std::string Name;
	std::string Story;
	bool FirstView;

	virtual Choice getUserMenuChoice(Actions* validActions, std::string TestAction="")=0; // Can't do anything with AbstractRoom

public:
	void (*EntryFunc)();
	AbstractRoom * North;
	AbstractRoom * East;
	AbstractRoom * South;
	AbstractRoom * West;
	std::list<Thing*> ThingsHere;
	std::list<Container*> ContainersHere;

	AbstractRoom() {}; //constructor
	virtual ~AbstractRoom() {}; // virtual destructor

	void (*TimerFunc)(AbstractRoom * , int );

	// Pure virtual functions
	virtual Actions Examine(int &counter) = 0; // Can't Examine AbstractRoom
	virtual AbstractRoom * NextUserAction(Holdall* PlayerBag) = 0;
	virtual AbstractRoom * NextUserActionTest(Holdall* PlayerBag, std::string TestAction) = 0;
	virtual void Print(bool Enigmatic) = 0;
	virtual AbstractRoom * getNextRoomFromDirection(MenuChoice nextChoice) = 0;
	virtual std::string getName() = 0;

	// Functions that are implemented in derived classes
	virtual void setTimerLimit(int timLimit) {  };
	virtual void setTimer(int tim) {  };
	virtual int getTimerLimit() { return 0;};
	virtual int getTimer() { return 0;};
	virtual void setWeather(std::string) {};
	virtual std::string getWeather() { return "";};
	virtual Container * FindByName(std::string){return 0;};
};

/* ********************************************************
 *
 * ****************************************************** */
class Room:public AbstractRoom 
{
protected:
	void ChangeAThing(Thing* ActOnThing, Holdall * PlayerBag);

public:						
	Room(std::string Na, std::string St); // constructor
	~Room(); // destructor
	//TODO:  destructor will need to clear the vector of pointers but not delete the things

	// Some of these are public for simplicity of maze setup
	// See the BuildTheEnvironment functions
	Actions Examine(int &counter);
	Choice getUserMenuChoice(Actions* validActions, std::string TestAction="");
	void Print(bool Enigmatic);
	AbstractRoom * NextUserAction(Holdall* PlayerBag);
	AbstractRoom * NextUserActionTest(Holdall *PlayerBag, std::string TestAction);
	AbstractRoom * getNextRoomFromDirection(MenuChoice nextChoice);
	Room * FindByPtr(Thing *);
	Container * FindByName(std::string);
	std::string getName() { return Name;}
	void (*TimerFunc)(AbstractRoom * , int );


};

class TimerRoom:public Room
{
public:
	int Timer;
	int TimerLimit;
  
	TimerRoom(std::string Na, std::string St); // constructor
	~TimerRoom(); // destructor
	void (*TimerFunc)(AbstractRoom *, int);
	void setTimerLimit(int timLimit) { TimerLimit = timLimit;};
	void setTimer(int tim) { Timer = tim;};
	int getTimerLimit() { return TimerLimit;}
	int getTimer() { return Timer;}
};
	
class OutsideRoom:public Room
{
	std::string Weather;

public:
	OutsideRoom(std::string Na, std::string St); // constructor
	~OutsideRoom(); // destructor

	void setWeather(std::string We) { Weather = We;};
	std::string getWeather() {return Weather;};
};
	
struct Choice {
	AbstractRoom* nextRoom;
	Thing* ActOnThing;

	Choice(){
		nextRoom = NULL;
		ActOnThing = NULL;
	};
};


#endif // _Room_H
