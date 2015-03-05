#include <iostream>  // for debugging
#include <stdexcept>

#include "Node.h"

#ifndef DEBUG
#define DEBUG false
#endif

/* ******************************************************** 
   Stack class template
  ******************************************************** */
template <class Type> 
class myStack 
{
private:
	StackElement<Type>* 	FirstElement;

public:
	myStack()
	{
		FirstElement = ((StackElement<Type>*) 0);
	};
	void push(Type value); 	// puts on item onto the structure
	Type peek(); 	// returns the value on top of the structure
	void pop(); 	// removes the top item in the structure
	bool isEmpty(); 		// For this lab you only need this check when you pop a value. 
};


/* ******************************************************** 
   Stack class member function template
  ******************************************************** */
#include "StackFunc.h"
