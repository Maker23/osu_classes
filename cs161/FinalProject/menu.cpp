// vim: ts=2
#include <cstdlib>
#include <iostream>
#include <string>
#include "Library.h"
#include "Book.h"
#include "Patron.h"
#include "readDataFiles.h"
#include "debug.h"

/******************************************************************************/
// Menu choices as an enumerated list
enum Action {unknown, AddBook, AddMember, CheckOutBook, ReturnBook,
						 RequestBook, IncrementDate, PayFine,ViewPatronInfo, ViewBookInfo,
						 Quit, ListAllBooks, ListAllPatrons, WQuit};
Action getUserAction(bool);
std::string getMemberID();
std::string getBookID();
double getPaymentAmount();

int main (int argc, char**argv)
{
	Library theLibrary;
	Action nextAction = Quit;
	bool adminMode = false;
	std::string tmpMember;

	if (argc > 1)
	{
		if (DBG_VERBOSE)
			std::cout << "Running in Administrative mode" << std::endl;
		adminMode = true;
		readDataFromFile(theLibrary); // For debugging
	}

	do
	{
		std::cout << std::endl;
		if (DBG_VERBOSE) std::cout << "The library date is "
			<< theLibrary.getCurrentDate() << std::endl;
		nextAction = getUserAction(adminMode);
		if (DBG_FUN) std::cout << "Action is " << (Action) nextAction << std::endl;
		switch (nextAction){
			case AddBook:
				theLibrary.addBook();
				break;
			case AddMember:
				theLibrary.addMember();
				break;
			case CheckOutBook:
				theLibrary.checkOutBook(getMemberID(), getBookID());
				break;
			case ReturnBook:
				theLibrary.returnBook(getBookID());
				break;
			case RequestBook:
				theLibrary.requestBook(getMemberID(), getBookID());
				break;
			case IncrementDate:
				theLibrary.incrementCurrentDate();
				break;
			case PayFine:
				tmpMember = getMemberID();
				theLibrary.payFine(tmpMember, getPaymentAmount());
				break;
			case ViewPatronInfo:
				theLibrary.viewPatronInfo(getMemberID());
				break;
			case ViewBookInfo:
				theLibrary.viewBookInfo(getBookID());
				break;
			case Quit:
				break;
		  case ListAllBooks:	
				theLibrary.listAllBooks();
				break;
		  case ListAllPatrons:	
				theLibrary.listAllPatrons();
				break;
		  case WQuit:	
				//writeDataToFile(theLibrary);
				// Can't do this while we're depending on pointers :/
				break;
			default:
				std::cout << "Unrecognized command, please try again." << std::endl;			
				break;
		}
	}
	while (nextAction != Quit);
}
/****************************************************************
 * getUserAction
 *
 * Print the menu and get the user's menu choice
 * Returns: An Action (enum int)
 ***************************************************************/
Action getUserAction(bool adminMode)
{
	if (DBG_FUN) std::cout << "Entering getUserAction" << std::endl;
	int menuChoice;
	int highChoiceNumber = 10;
	Action actionChoice;

	std::cout << std::endl <<
		"1. Add a Book to the library" << std::endl <<
		"2. Add a Member to the library" << std::endl <<
		"3. Check out a book" << std::endl <<
		"4. Return a book" << std::endl <<
		"5. Request a book (put on hold)" << std::endl <<
		"6. Increment the current date" << std::endl <<
		"7. Pay a fine" << std::endl <<
		"8. View Member information" << std::endl <<
		"9. View Book information" << std::endl <<
		"10. Quit" << std::endl;

 	// If we're in "admin mode" we get more choices
	if (adminMode)
	{
		std::cout << std::endl <<
		"11. List all books in the library" << std::endl <<
		"12. List all library patrons" << std::endl;
		//"13. Quit and write updated files" << std::endl;
		highChoiceNumber = 12;
	}

	std::cout << std::endl << "What do you want to do? [1-"
		<< highChoiceNumber << "]: ";

  // Request input from the user until we get an integer
	while ( !  (std::cin >> menuChoice ))
	{
		std::cin.clear();
		std::cin.ignore(1000,'\n');
		std::cout << std::endl << "What do you want to do? [1-"
			<< highChoiceNumber << "]: ";
	}
	std::cin.ignore(1000,'\n'); // Throw away the trailing newline

	// If we don't recognize the menu choice set it to Unknown
	if ( menuChoice < 1 || menuChoice > highChoiceNumber) menuChoice = 0;
	actionChoice = (Action) menuChoice;
	return (actionChoice);
}

std::string getMemberID()
{
	if (DBG_FUN) std::cout << "Entering getMemberID" << std::endl;
	std::string tmpMember;
	std::cout << "Enter the Member Number [P###]: ";
	getline(std::cin, tmpMember);
	return tmpMember;
}
std::string getBookID()
{
	if (DBG_FUN) std::cout << "Entering getBookID" << std::endl;
  std::string tmpBook;
	std::cout << "Enter the book ID   [ISBN####]: ";
	getline(std::cin, tmpBook);
	return tmpBook;
}

double getPaymentAmount()
{
	if (DBG_FUN) std::cout << "Entering getPaymentAmount" << std::endl;
  std::string tmpStr;
	std::string::size_type found;
  double tmpAmount;

	std::cout << "Enter the payment you wish to make: ";
	getline(std::cin, tmpStr);
	found = tmpStr.find_first_not_of("$");
	tmpAmount = strtod((tmpStr.substr(found, tmpStr.length() - found)).c_str(), NULL);
	return tmpAmount;
}
