#include <iostream>  // for debugging
#include <stdexcept>

#ifndef DEBUG
#define DEBUG false
#endif

/* ******************************************************** 
   Stack class member function templates
  ******************************************************** */

template <typename Type>
void myStack<Type>::push(Type value)
{
	StackElement<Type>* tmpElem;

  tmpElem = new StackElement<Type>;
	if (FirstElement != ((StackElement<Type>*)0))
	{
		tmpElem->setNext(FirstElement);
	}
	tmpElem->setVal(value);
	FirstElement = tmpElem;
}

template <typename Type>
void myStack<Type>::pop()
{
	StackElement<Type>* tmpElemPtr;

  if (FirstElement == ((StackElement<Type>*) 0))
	{
		throw std::logic_error("Error: trying to pop off an empty stack");
	}
	else 
	{
		tmpElemPtr = FirstElement->getNext();
  	if (tmpElemPtr == ((StackElement<Type>*) 0))
		{
			std::cout << "WARNING: last pop, stack is empty" << std::endl;
		}
		delete FirstElement;
		FirstElement = tmpElemPtr;
	}
}

template <typename Type>
Type myStack<Type>::peek()
{
  if (FirstElement == ((StackElement<Type>*) 0))
	{
		throw std::logic_error("Error: trying to peek into an empty stack");
	}
	if (DEBUG) std::cout << "DEBUG: First element next = " << (void *) FirstElement->getNext()<< std::endl;
	if (DEBUG) std::cout << "DEBUG: wtf " << FirstElement->getVal() << std::endl;
	return FirstElement->getVal();
}

template <typename Type>
bool myStack<Type>::isEmpty()
{
	if (FirstElement != ((StackElement<Type>*)0))
	{
		return false;
	}
	return true;
}

