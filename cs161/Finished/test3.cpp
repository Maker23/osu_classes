#include <iostream>
#include <string>

int main ()
{
	int range_low;

	std::cout << "What is the range from and to?" << std::endl;

	std::cout << "From: ";

	while ( ! (std::cin >> range_low) )
	{
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "From: ";
	}

	std::cout << "Got number " << range_low << std::endl;

}
