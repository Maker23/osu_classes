//vim:ts=2
//
/***********************************************************
 *
 * CS162 Assignment2
 * Shoshana Abrass
 * abrasss@onid.oregonstate.edu
 * Jan 30, 2015
 *
 *
 * TODO:
 * 	Maybe add dollar sign to printout?
 *  Fix DEBUG flag inheritance
 */

#include <climits>
#include "Item.h"
#include "List.h"
#include "validateNumericInput.h"

#define DEBUG false

enum Choice {Add, Edit, Delete, Print, Save, Quit, unknown};
char Options[] = {'A','E','D','P','S','Q'};

enum EditChoice {Price, Quantity, edit_unknown};
char EditOptions[] = {'P','Q'};

Choice getUserMenuChoice();
EditChoice getUserMenuChoice_Edit_submenu();
void changeItem(bool deleteItem, List &myList);

/*****************************************************************/
int main()
{
	bool deleteItem;
	std::string fileName = "myList.data"; // hardcoded in version 1
	std::string tmpString;
	Choice nextChoice = Quit;
	
	// Declare a list and initialise it from a file
	// Silently does nothing on failure. TODO: Warn, not error, if file not found
	List myList(fileName);

	std::cout << "Welcome to your shopping list." << std::endl;
	if (myList.itemCount() > 0)
	{
		std::cout << "Here is what you have on the list so far: " << std::endl;
		myList.printAll();
	}

  // Enter the main menu and loop until quit
	do
	{
		nextChoice = getUserMenuChoice();
		switch (nextChoice){
			case Add:
				myList.addItem();
				myList.needToSaveData = true;
				break;
			case Edit:
				changeItem(deleteItem=false, myList);
				break;
			case Delete:
				changeItem(deleteItem=true, myList);
				break;
			case Print:
				myList.printAll();
				break;
			case Save:
				std::cout << "Saving file.... " << std::endl;
				myList.saveAll(fileName);
				myList.needToSaveData = false;
				break;
			case Quit:
				if (myList.needToSaveData) {
					std::cout << "Warning: data has been changed, do you want to save before quitting? [Y,n] ";
					getline(std::cin, tmpString);
					// Defaults to Y if anything other than "n" is typed
					if ( (toupper(tmpString[0])) != 'N' )
					{
						myList.saveAll(fileName);
					}
					std::cout << "Exiting." << std::endl;
				}
				break;
			default:
				std::cout << "Unrecognized command, try again" << std::endl;
				break;
		}
	}
	while (nextChoice != Quit);
}


/*****************************************************************/
void changeItem(bool deleteItem, List &myList)
{

	EditChoice nextChoice = edit_unknown;
	std::string tmpString;
	float newPrice;
	int newQty;

	if (myList.itemCount() == 0)
	{
  	std::cout << "List is empty; nothing on the list to edit. Add something first."<< std::endl;
		return;
	}
	else
	{
		myList.printAll();
		std::cout << std::endl << "Which line item do you want to ";
		deleteItem ? (std::cout << "delete? "): (std::cout << "change? ");
		//if (deleteItem)
			//std::cout << "change? " ;
		//else

		int lineNumber = getIntegerInput(1, myList.itemCount(),0,"");
		if (lineNumber < 1) {
			// ERROR, TODO print message
			return;
		}
		if (deleteItem) {
			if (DEBUG) std::cout << "Deleting line item # " << lineNumber << std::endl;
			myList.deleteItem(lineNumber-1);
			myList.needToSaveData = true; // Data has changed and needs to be saved
			return;
		}
		else
		{
			nextChoice = getUserMenuChoice_Edit_submenu();
			switch (nextChoice)
			{
				case Price:
					std::cout << "Enter the new price: [$0.00 - ] ";
					getline (std::cin, tmpString);
					newPrice = validateFloatInput((char *)tmpString.c_str(), 0.00, INT_MAX);
					if (newPrice < 0.0)
					{
						std::cout << "ERROR: Invalid price " << newPrice << std::endl;
						return;
					}
					else {
						myList.changePrice(lineNumber-1, newPrice);
						myList.needToSaveData = true;
						return;
					}
					break;
				case Quantity:
					std::cout << "Enter the new quantity: [1- ] ";
					getline (std::cin, tmpString);
					newQty = validateIntegerInput((char *)tmpString.c_str(), 1, INT_MAX);
					if (newQty < 1)
					{
						std::cout << "ERROR: Invalid quantity " << newQty << std::endl;
						return;
					}
					else {
						myList.changeQty(lineNumber-1, newQty);
						myList.needToSaveData = true;
						return;
					}
					break;
				default:
					// If unrecognized just return, don't retry
					std::cout << "Leaving item unchanged" << std::endl;
					return;
					break;
			}
		}
	}
}

/*****************************************************************/
Choice getUserMenuChoice()
{
	char menuOption;
	Choice menuChoice;
	char inputBuffer[1024];

	std::cout << std::endl <<
		"[A]dd an item to the list" << std::endl <<
		"[E]dit an item on the list" << std::endl <<
		"[D]elete an item from the list" << std::endl <<
		"[P]rint the list to the screen" << std::endl <<
		"[S]ave the list to disk" << std::endl <<
		"[Q]uit the program" << std::endl << std::endl <<
		"What do you want to do? (A,E,D,P,S,Q): ";
  menuOption = std::cin.get(); // get the first character
	std::cin.getline(inputBuffer,1024); // throw away anything else they typed

	for (int i=0; i<6; i++)
	{
		if (toupper(menuOption) == Options[i])
		{
			menuChoice = (Choice) i;
			return (menuChoice);
		}
	}
	return (unknown);
}

/*****************************************************************/
EditChoice getUserMenuChoice_Edit_submenu()
{
	char menuOption;
	EditChoice menuChoice;
	char inputBuffer[1024];

	std::cout << std::endl <<
//		"\t" << "[N]ame of the item" << std::endl <<
//		"\t" << "[U]nit of the item" << std::endl <<
		"\t" << "[P]rice of the item" << std::endl <<
		"\t" << "[Q]uantity of the item" << std::endl <<
		"What do you want to change? (P,Q): ";
  menuOption = std::cin.get(); // get the first character
	std::cin.getline(inputBuffer,1024); // throw away anything else they typed

	for (int i=0; i<6; i++)
	{
		if (toupper(menuOption) == EditOptions[i])
		{
			menuChoice = (EditChoice) i;
			return (menuChoice);
		}
	}
	return (edit_unknown);
}
