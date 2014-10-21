/*******************************************************************************
 *	Author: 				Shoshana Abrass
 *	Date Created:  	2014/09/29
 *	Last Modification Date: 2014/10/01
 *	Filename: 			echo.cc
 *
 *	Overview:
 *		This program prompts for input and reads input from the terminal. 
 *		If input is an integer it prints out the integer;
 *		otherwise it prompts again.
 *	Inputs:
 *		Random input from the terminal handled as an int
 *  Output:
 *  	Whatever integer value was input
 *****************************************************************************/
#include <iostream>
#include <climits>

int main()
{
	int UserInput;

  /* This prompt is really ugly, but will leave it for now */
	std::cout << "Type an integer" << " [" << INT_MIN << "-" << INT_MAX << "] > ";
	std::cin >> UserInput;
	while (!std::cin) {
		/* Clear the failbit and dicard any characters, up to the carriage return */
		std::cin.clear();
		std::cin.ignore(10000,'\n');
		std::cout << "Type an integer" << " [0-" << INT_MAX << "] > ";
		std::cin >> UserInput;
	}
	std::cout << "You typed " << UserInput << "\n";

	return 0;
}
