#include <iostream>  // for debugging
#include <stdexcept>

#ifndef DEBUG
#define DEBUG false
#endif

#ifndef _NODE_H
#define _NODE_H

/* ******************************************************** 
   StackElement is the "node" in the queue or stack
  ******************************************************** */
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

	~StackElement()
	{
		delete Element;
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

#endif // _NODE_H
