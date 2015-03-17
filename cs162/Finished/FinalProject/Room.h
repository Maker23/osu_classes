#include <iostream>
#include <string>
#include <list>
#include <vector>

#include "Thing.h"
#include "Container.h"

#ifndef _Room_H
#define _Room_H

enum MenuChoice { N, S, E, W, unknown};

struct Choice; // Forward declaration

/* ********************************************************
 * Pure virtual base class AbstractRoom
 * ****************************************************** */
class AbstractRoom {

protected:
	std::string Name;
	std::string Story;
	bool FirstView;


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
	virtual std::string getName() = 0;
	virtual void Print(bool Enigmatic) = 0;
	virtual Actions Examine(int &counter) = 0;
	virtual AbstractRoom * NextUserAction(Holdall* PlayerBag) = 0;
	virtual AbstractRoom * NextUserActionTest(Holdall* PlayerBag, std::string TestAction) = 0;
	virtual AbstractRoom * getNextRoomFromDirection(MenuChoice nextChoice) = 0;
	virtual Choice getUserMenuChoice(Actions* validActions, std::string TestAction="")=0; 

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

	// Some of these are public for simplicity of maze setup
	// See the BuildTheEnvironment functions
	std::string getName() { return Name;}
	void Print(bool Enigmatic);
	void (*TimerFunc)(AbstractRoom * , int );
	Actions Examine(int &counter);
	AbstractRoom * NextUserAction(Holdall* PlayerBag);
	AbstractRoom * NextUserActionTest(Holdall *PlayerBag, std::string TestAction);
	AbstractRoom * getNextRoomFromDirection(MenuChoice nextChoice);
	Choice getUserMenuChoice(Actions* validActions, std::string TestAction="");
	Container * FindByName(std::string);
	Room * FindByPtr(Thing *);

};

class TimerRoom:public Room
{
public:
	int Timer;
	int TimerLimit;
  
	TimerRoom(std::string Na, std::string St); // constructor
	~TimerRoom(); // destructor

	int getTimerLimit() { return TimerLimit;}
	int getTimer() { return Timer;}
	void (*TimerFunc)(AbstractRoom *, int);
	void setTimerLimit(int timLimit) { TimerLimit = timLimit;};
	void setTimer(int tim) { Timer = tim;};
};
	
class OutsideRoom:public Room
{
	std::string Weather;

public:
	OutsideRoom(std::string Na, std::string St); // constructor
	~OutsideRoom(); // destructor

	std::string getWeather() {return Weather;};
	void setWeather(std::string We) { Weather = We;};
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
