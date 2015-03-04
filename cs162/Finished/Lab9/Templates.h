#include <iostream>  // for debugging
#include <stdexcept>

#define DEBUG false

template <class Type> 
class StackElement
{
	Type* Element;
	StackElement<Type>* Next;

public:
	StackElement() 
	{
		Element = new Type;
		Next = ((StackElement<Type>*) 0);
	};

	void setVal(Type val)
		{ *Element = val; };

	Type getVal()
		{ return *Element; };

	void setNext(StackElement<Type>* nxt)
		{ Next = nxt; };

	StackElement<Type>* getNext()
		{ return Next; };
};

/* ******************************************************** 
   Stack template
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

/* ******************************************************** 
   Queue template
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

