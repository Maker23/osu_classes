/*******************************************************************************
 *	Author: 				Shoshana Abrass
 *	Date Created:  	2014/09/29
 *	Last Modification Date:
 *	Filename: 			echo.cc
 *
 *	Overview:
 *		This program reads input from the terminal and echoes it back
 *	Inputs:
 *		Random input from the terminal handled as a string
 *  Output:
 *  	Whatever string was input
 *****************************************************************************/
#include <iostream>
#include <string>
#include <sstream>

int main()
{
	std::string TerminalInput;
  int integer_value;
	std::cin.exceptions(std::ios::failbit);

	//std::cout << "echo > ";
	//getline (std::cin, TerminalInput);
	//std::cout << TerminalInput << "\n";
	//
	std::cout << "Type an integer > ";
	getline(std::cin, TerminalInput);
	std::cout << "In theory the number of characters is " << std::cin.gcount();
	std::stringstream ss (TerminalInput);
	try 
	{
		ss >> integer_value;
		ss.read(0, 256);
	  std::cout << "In theory the number of characters is " << ss.gcount();
		std::cout << "You typed the number " << integer_value << "\n";
	}
	catch (...) {
		std::cout << "Sorry, that wasn't an integer\n";
	}

	return 0;
}

