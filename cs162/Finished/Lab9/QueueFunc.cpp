#include <iostream>  // for debugging
#include <stdexcept>

#include "Node.h"

#ifndef DEBUG
#define DEBUG false
#endif

/* ******************************************************** 
   Queue class member templates
  ******************************************************** */
template <typename Type>
void myQueue<Type>::addBack(Type value)
{
	StackElement<Type>* tmpElem;

  tmpElem = new StackElement<Type>;
	tmpElem->setVal(value);

	if (BackElement != ((StackElement<Type>*)0))
	{
		BackElement->setNext(tmpElem);
	}
	BackElement = tmpElem;
	if (FrontElement == ((StackElement<Type>*)0))
	{
		FrontElement = BackElement;
	}
}

template <typename Type>
Type myQueue<Type>::getFront()
{
  if (FrontElement == ((StackElement<Type>*) 0))
	{
		throw std::logic_error("Error: trying to getFront off an empty queue");
	}
	if (DEBUG) std::cout << "DEBUG: First element next = " << (void *) FrontElement->getNext()<< std::endl;
	if (DEBUG) std::cout << "DEBUG: " << FrontElement->getVal() << std::endl;
	return FrontElement->getVal();
}

template <typename Type>
void myQueue<Type>::removeFront()
{
	StackElement<Type>* tmpElemPtr;

  if (FrontElement == ((StackElement<Type>*) 0))
	{
		throw std::logic_error("Error: trying to removeFront off an empty queue");
	}
	else 
	{
		tmpElemPtr = FrontElement->getNext();
  	if (tmpElemPtr == ((StackElement<Type>*) 0))
		{
			std::cout << "WARNING: last remove, queue is empty" << std::endl;
		}
		delete FrontElement;
		FrontElement = tmpElemPtr;
	}
}

template <typename Type>
bool myQueue<Type>::isEmpty()
{
	if (FrontElement != ((StackElement<Type>*)0))
	{
		return false;
	}
	return true;
}

