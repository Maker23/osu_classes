#include <iostream> // for debugging
#include <list>
#include <string>

#include "Container.h"
#include "Thing.h"


/* ***********************************************************
 * Constructors
 * ********************************************************* */
Container::Container (std::string Na, std::string St) : Thing (Na, St)
{
	Name=Na;
	Story=St;
	Open=true; 		// Much easier to play this way
	Weight=100; 	// By default - too heavy to carry
	Capacity=99; 	// By default - basically no limit on the number of Things
	UseFunc = NULL;
	OpenFunc = NULL;
	isContainer = true;
}

Holdall::Holdall(std::string Na) : Container (Na,"")
{
	Capacity = 1; // Default
}

/* ********************************************************* */
void Container::Print()
{
	std::cout << "You are looking at a " << this->Name << std::endl;
	std::cout << this->Story << std::endl;
}

/* ***********************************************************
 * 
 * 
 *
 * ********************************************************* */
std::vector<Thing*> Container::Examine(int &counter, bool verbose)
{
	std::list<Thing*>::iterator iter;
	std::vector<Thing*> AllContents;
	std::vector<Thing*> subContents;

  if (DEBUG_FUNCTION) std::cout << "===== begin Container::Examine" << std::endl;
  if (DEBUG_EXAMINE)
	{	
		std::cout  << "DEBUG: Container::Examine counter=" <<counter
			<<  ", Open = " << Open
			<< ", isContainer = " << isContainer << std::endl;
	}
	if ( (this->Story).compare("") != 0 )
		std::cout << "	    " << this-> Name << ".  " << this->Story << std::endl;

  if ( ! Open )
	{
  	if (OpenFunc != NULL) {
			if (DEBUG_EXAMINE) std::cout << "DEBUG: Running OpenFunc " << OpenFunc << " on " 
					<< this->Name << " (Container::Examine)" << std::endl;
		
			// We're not really trying to open the container here; we 
			// just want to get any useful printout from the OpenFunc, 
			// for example, "look for a silver key" or somesuch.
			// So we pass the function a NULL container*
			bool Success = OpenFunc((Container*) NULL); 
			if (!Success) 
			{
				std::cout << "	    The " << this->Name << " won't open. Maybe it's locked." << std::endl;
				return AllContents;
			}
		}
		else {
			std::cout << "	    The " << this->Name << " doesn't open." << std::endl;
			return AllContents;
		}
	}

	// If the container is holding anything, examine that too
  if ( Contents.size() == 0 ) 
	{
		std::cout << "	    The " << this->Name << " is empty" << std::endl;
	}
	else
	{
  	if (DEBUG_EXAMINE) std::cout  << "	    " << "The " << this->Name 
			<< " holds " << Contents.size() << " items:" << std::endl;

		std::cout << "	    " << "The " << this->Name << " holds:" << std::endl;
		for (iter=Contents.begin(); iter != Contents.end(); iter++)
		{
			if ( (*iter)->isContainer )
			{
				// If we find a container inside a container, deal with it recursively
				std::cout << "	    ";
				if (verbose ) std::cout << counter++ << ".  " ;
				std::cout << (*iter)->Name << std::endl;
				AllContents.push_back(*iter);
				subContents = (*iter)->Examine(counter, verbose); // Recursion FTW
				AllContents.insert(AllContents.end(), subContents.begin(),subContents.end());
			}
			else
			{
				// If we find a thing, no recursion
				//std::cout << "	    "<< counter++ << ".  " << (*iter)->Name << std::endl;
				std::cout << "	    ";
				if (verbose ) std::cout << counter++ << ".  " ;
				std::cout << (*iter)->Name << std::endl;
				AllContents.push_back(*iter);
			}
		}
	}
  if (DEBUG_EXAMINE) std::cout  << "===== end   Container::Examine counter=" << counter << std::endl;
	return AllContents;
}

/* ***********************************************************
 * Search inside a container for a Thing with a particulare address
 * If found, return a pointer to the holding container;
 * else return NULL
 * ********************************************************* */
Container * Container::FindByPtr(Thing * SeekingThingPtr)
{
	std::list<Thing*>::iterator iter;
	if (DEBUG_FIND) std::cout << "DEBUG: Find: Looking in " << this->Name << std::endl;
	for (iter=Contents.begin(); iter != Contents.end(); iter++)
	{
			if ( (*iter) == SeekingThingPtr ) 
			{
				return this; // The Thing is in this container
			}
			if ( (*iter)->isContainer )
			{
				if (DEBUG_FIND) std::cout << "DEBUG: Recursing FindByPtr into " << (*iter)->Name << std::endl;
				return(((Container*)(*iter))->Container::FindByPtr(SeekingThingPtr));
			}
	}
	return ((Container *)0);
}

/* ***********************************************************
 * Search inside a container for a Thing with a particulare name
 * Return the pointer for that Thing
 * ********************************************************* */
Thing * Container::FindByName(std::string SeekingThingName)
{
	std::list<Thing*>::iterator iter;

	if (DEBUG_FIND) std::cout << "===== begin Container::FindByName, looking in " << this->Name << std::endl;
	for (iter=Contents.begin(); iter != Contents.end(); iter++)
	{
			if ( ((*iter)->Name).compare(SeekingThingName) == 0 ) 
			{
				//return this; // The Thing is in this container
				return (*iter); // Return eht pointer to thing found hting
			}
			if ( (*iter)->isContainer )
			{
				if (DEBUG_FIND) std::cout << "DEBUG: Recursing FindByName into " << (*iter)->Name << std::endl;
				return(((Container*)(*iter))->Container::FindByName(SeekingThingName));
			}
	}
	if (DEBUG_FIND) std::cout << "===== begin Container::FindByName, looking in " << this->Name << std::endl;
	return ((Thing *)0);
}

/* ***********************************************************
 * Holdall functions
 *
 *
 * Holdall::Examine is different in that:
 *
 * 	 It returns the Holdall in the vector (container examine does not return itself)
 * 	 It doesn't need to handle open tests or OpenFunc functions
 *
 * ********************************************************* */
std::vector<Thing*> Holdall::Examine(int &counter, bool verbose)
{
	std::vector<Thing *> AllContents;
	std::vector<Thing*> subContents;

  if (DEBUG_FUNCTION) std::cout << "===== begin Holdall::Examine" << std::endl;
	if (verbose)
		std::cout << "	" << counter ++ << ".  You are carrying a " << this->Name << std::endl;
 	else
		counter++;

	AllContents.push_back(this);
	subContents = Container::Examine (counter, verbose);
	AllContents.insert(AllContents.end(), subContents.begin(),subContents.end());
  if (DEBUG_FUNCTION) std::cout << "===== end Holdall::Examine" << std::endl;

	return AllContents;

}

int Holdall::getAvailableCapacity()
{
	int HoldallIsCarrying = 0;
	int counter = 0;
	std::vector<Thing*> backpackContents;
	std::vector<Thing*>::iterator iterThing;

	backpackContents = this->Examine(counter, false);
	for (iterThing=backpackContents.begin(); iterThing != backpackContents.end(); iterThing++)
	{
		if ( (*iterThing) == this) continue; // Don't count the holdall itself
		HoldallIsCarrying += (*iterThing)->getWeight();
	}
	return (this->Capacity - HoldallIsCarrying);
}

