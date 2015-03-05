#include <iostream>

#include "Queue.h"
#include "Stack.h"

void IntegerQueueTests();
void IntegerStackTests();
void StringStackTests();

int main()
{
	std::cout << "Fun with Templates!" << std::endl;
	std::cout << "Running canned tests" << std::endl;

  IntegerQueueTests();
	IntegerStackTests();
  StringStackTests();
}


void StringStackTests()
{
	myStack<std::string> StrStack;
  
	std::cout << std::endl
		<< "Testing myStack<std::string> *****************" << std::endl;

  std::cout << "Is it empty? " << StrStack.isEmpty() << std::endl;
	std::cout << "Pushing 'bar' " << std::endl;
	StrStack.push("bar");
	std::cout << "Pushing 'foo' " << std::endl;
	StrStack.push("foo");
	std::cout << "Peeking, should get 'foo': " << StrStack.peek() << std::endl;
  std::cout << "Is it still empty? " << StrStack.isEmpty() << std::endl;

}

void IntegerStackTests()
{
	myStack<int> IntStack;

	std::cout << std::endl
		<< "Testing myStack<int> ************************" << std::endl;

  std::cout << "Is it empty? " << IntStack.isEmpty() << std::endl;
	std::cout << "Pushing 9 " << std::endl;
	IntStack.push(9);
	std::cout << "Peeking, should get 9: " << IntStack.peek() << std::endl;
  std::cout << "Is it still empty? " << IntStack.isEmpty() << std::endl;

	std::cout << "Pushing 3 " << std::endl;
	IntStack.push(3);
	std::cout << "Peeking, should get 3: " << IntStack.peek() << std::endl;

	std::cout << "Popping 3 " << std::endl;
	IntStack.pop();
	std::cout << "Peeking, should get 9: " << IntStack.peek() << std::endl;

	std::cout << "Popping 9 " << std::endl;
	IntStack.pop();
}


void IntegerQueueTests()
{
	myQueue<int> IntQueue;

	std::cout << std::endl
		<< "Testing myQueue<int> ************************" << std::endl;

  std::cout << "Is it empty? " << IntQueue.isEmpty() << std::endl;
	std::cout << "addBack 9 " << std::endl;
	IntQueue.addBack(9);
	std::cout << "getFront, should get 9: " << IntQueue.getFront() << std::endl;
  std::cout << "Is it still empty? " << IntQueue.isEmpty() << std::endl;

	std::cout << "addBack 3 " << std::endl;
	IntQueue.addBack(3);
	std::cout << "getFront, should get 9: " << IntQueue.getFront() << std::endl;

	std::cout << "removeFront " << std::endl;
	IntQueue.removeFront();
	std::cout << "getFront, should get 3: " << IntQueue.getFront() << std::endl;

	std::cout << "removeFront" << std::endl;
	IntQueue.removeFront();
  std::cout << "Is it empty now? " << IntQueue.isEmpty() << std::endl;
}
