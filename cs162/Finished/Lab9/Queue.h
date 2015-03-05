#include <iostream>  // for debugging
#include <stdexcept>

#include "Node.h"

#ifndef DEBUG
#define DEBUG false
#endif

#ifndef _QUEUE_H
#define _QUEUE_H

/* ******************************************************** 
   Queue class template
  ******************************************************** */
template <class Type> 
class myQueue 
{
private:
	StackElement<Type>* 	FrontElement;
	StackElement<Type>* 	BackElement;

public:
	myQueue()
	{
		FrontElement = ((StackElement<Type>*) 0);
		BackElement = ((StackElement<Type>*) 0);
	};
	void addBack(Type value); 	// adds on item to the back of structure
	Type getFront(); 	// returns the value at the front of the structure
	void removeFront(); 	// removes the front item in the structure
	bool isEmpty(); 		// For this lab you only need this check when you pop a value. 
};

/* ******************************************************** 
   Queue class member functions templates
  ******************************************************** */
#include "QueueFunc.h"

#endif // _QUEUE_H
