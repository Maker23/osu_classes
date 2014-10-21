#include <iostream>
#include <string>

int main ()
{
	std::string myWord = "";

	std::cout << "enter some words: ";

  while ( std::cin >> myWord)  
	{
		std::cout << "myWord is " << myWord << std::endl;
	}
}
