// vim: ts=2
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Library.h"
#include "Book.h"
#include "Patron.h"
#include "debug.h"


// Printable strings match the Locale enum defined in Book.h
std::string LocaleString[] = {"On the shelf", "On Hold", "Checked out"};

const int Book::CHECK_OUT_LENGTH;

Library::Library(){
  holdings.reserve(100); // pre-allocation vector memory to prevent
  members.reserve(100);  // pointer addresses from changing
	currentDate=0;				 // initialize to 0
	// nextMemberNum = getNextMemberNum(); // Not allowed
}

void Library::addBook()
{
	/*
	 * addBook - prompts the user for book info and uses it to create
	 *					 a Book, which is added to holdings  
	 */
	if (DBG_FUN) std::cout << "Library::addBook" << std::endl;
	 
	std::string tmpTitle;  // temporary storage for user input
	std::string tmpAuthor;
	std::string tmpID;

	std::cout << "Title: ";
	getline(std::cin, tmpTitle); // No validation is done on input
	std::cout << "Author: ";
	getline(std::cin, tmpAuthor);
	std::cout << "Book ID (ISBN####): ";
	getline(std::cin, tmpID);

	int checkID = findBook(tmpID); // Look for that tmpID in holdings
	if ( checkID >=0 )
	{
		std::cout << "Sorry, that Book ID is already in use." << std::endl;
		return;
	}

	Book book(tmpID,tmpTitle,tmpAuthor);
	holdings.push_back(book);
	std::cout << "Added book " << tmpTitle << " with ID " << tmpID <<std::endl;
}

void Library::addBook(Book & book)
{
  /* 
	 * addBook non-interactively (ie, from data file). No validation is
	 * done, including no checks for duplicate IDs, although that would
	 * be simple.  It is assumed that the admin has generated good data
	 */
  if (DBG_FUN) std::cout << "Library::addBook" << std::endl;
	holdings.push_back(book);
}

void Library::addMember()
{
	/*
	 * addMember - prompts the user for patron info and uses it to
	 * 		         create a Patron, which is added to members
	 */
  if (DBG_FUN) std::cout << "Library::addMember" << std::endl;

	std::string tmpName; // temporary storage for user input
	std::string tmpID;

	std::cout << "Enter member name (first then last): ";
	getline(std::cin, tmpName); // No validation is done on input
	std::cout << "Enter member ID # (P###): ";
	getline(std::cin, tmpID);

	int checkID = findMember(tmpID); // Look for tmpID in members
	if ( checkID >=0 )
	{
		std::cout << "Sorry, that member ID is already in use." << std::endl;
		return;
	}

	Patron member(tmpID, tmpName);
	members.push_back(member);
	std::cout << "Added member " << tmpName << " with ID " << tmpID <<std::endl;
}

void Library::addMember(Patron &member)
{
  /* 
	 * addMember non-interactively (ie, from data file). No validation is
	 * done, including no checks for duplicate IDs, although that would
	 * be simple.  It is assumed that the admin has generated good data
	 */
  if (DBG_FUN) std::cout << "Library::addMember" << std::endl;
	members.push_back(member);
}

void Library::checkOutBook(std::string patronID, std::string bookID)
{
	/*
	 * checkOutBook
	 *	◦ if the specified Book or Patron are not in the Library (an ID doesn't
	 *		match an object in the Library), print out that message and return
	 *		to the 	menu
	 *	◦ if a Book is already checked out, print out that message and return
	 *		to the menu
	 *	◦ if a Book is on hold by another Patron, print out that message and
	 *		return to the menu
	 *	◦ if a Book is on hold by this Patron, unset that
	 *
	 *	◦ update the Book's checkedOutBy, dateCheckedOut and Location;
	 *		update the Patron's list; print out that Book title has been checked out to
	 *		Patron name
	 */
  if (DBG_FUN) std::cout << "Library::checkOutBook" << std::endl;

	int book;
	int member;
	Locale location;

	book = findBook(bookID);
	if (book < 0 ){
		std::cout << "ERROR: Couldn't find that book in our collection" << std::endl;
		return;
	}
	member = findMember(patronID);
	if (member < 0 ){
		std::cout << "ERROR: Couldn't find that person in our membership" << std::endl;
		return;
	}

	location = holdings[book].getLocation();
	switch (location){
		case CHECKED_OUT:
			std::cout << "Sorry, that book is currently checked out to "
				<< (*(holdings[book].getCheckedOutBy())).getName() << std::endl;
			return;
			break;
		case ON_HOLD:
			if( patronID.compare((*(holdings[book].getRequestedBy())).getIdNum()) !=0 )
			{
				std::cout << "Sorry, that book is currently on hold for " 
				<< (*(holdings[book].getRequestedBy())).getName() << std::endl;
				return;
			}
			else
			{
				// If the member trying to check out the book is the member
				// who has it on hold, that works.
				std::cout << "Releasing member's hold on book." << std::endl;
				
				// No break or return here!! Fall through to next case.
				
			}
		case ON_SHELF:
			std::cout << "Checking out book." << std::endl;
			// Update the book
			holdings[book].setCheckedOutBy(& members[member]);
			holdings[book].setDateCheckedOut(currentDate);
			holdings[book].setLocation(CHECKED_OUT);
			holdings[book].setRequestedBy(NULL);

   		// Update the member
			members[member].addBook(& holdings[book]);

			std::cout << "\"" << holdings[book].getTitle() << "\"  has been checked out by " 
				<< members[member].getName() <<std::endl;
			break;
	}
}

void Library::returnBook(std::string bookID)
{
	/*
	 * returnBook
	 *	◦ if the specified Book is not in the Library, print out that message 
	 *		and return to the menu
	 *	◦ if the Book is not checked out, print out that message and return to 
	 *		the menu
	 *	◦ update the Patron's list; update the Book's location (and possibly 
	 *		requestedBy) depending on whether another Patron has requested it; 
	 *		print out that Book title has been returned
	 */
  if (DBG_FUN) std::cout << "Library::returnBook" << std::endl;
	int book;
	int member;
	Locale location;

	book = findBook(bookID);
	if (book < 0 )
	{
		std::cout << "ERROR: Couldn't find that book in our collection." << std::endl;
		return;
	}
	if ( holdings[book].getLocation() != CHECKED_OUT) 
	{
		std::cout << "Our records indicate that book is not checked out." << std::endl;
		return;
	}
	std::cout << "Returning book " << holdings[book].getTitle() << " to library" << std::endl;

	// Update the members list of checked out books
	member = findMember( (*(holdings[book].getCheckedOutBy())).getIdNum() );
	members[member].removeBook(& holdings[book]);

	// If there's a hold on the book, move it to ON_HOLD, otherwise
	// return it to the shelf
	if ( holdings[book].getRequestedBy() != NULL )
	{
		std::cout << "Putting book on hold for "
			<< (* (holdings[book].getRequestedBy())).getName() << std::endl;
		holdings[book].setLocation(ON_HOLD);
	}
	else
	{
		holdings[book].setLocation(ON_SHELF);
	}
}

void Library::requestBook(std::string patronID, std::string bookID)
{
	/*
	 * requestBook
	 *	◦ if the specified Book or Patron are not in the Library, print out
	 *		that message and return to the menu
	 *	◦ if the Book is already requested by another Patron, print out that
	 *		message and return to the menu
	 *	◦ update the Book's requestedBy; if the Book is on the shelf, update
	 *		its location to on hold; print that Book title is on request for
	 *		Patron name
	 */
  if (DBG_FUN) std::cout << "Library::requestBook" << std::endl;
	int book;
	int member;
	Locale location;

	book = findBook(bookID);
	if (book < 0 ) {
		std::cout << "ERROR: Couldn't find that book in our collection." 
			<< std::endl;
		return;
	}
	member = findMember(patronID);
	if (member < 0 ){
		std::cout << "ERROR: Couldn't find that person in our membership" 
			<< std::endl;
		return;
	}

	if ( holdings[book].getRequestedBy() != NULL) 
	{
		std::cout << "That book is already on hold; " 
			<< "only one hold allowed at a time." << std::endl;
		return;
	}

  if ( holdings[book].getCheckedOutBy() != NULL ) {
  	if ( patronID.compare((*(holdings[book].getCheckedOutBy())).getIdNum()) == 0 )
		{
			std::cout << "ERROR: Can't put a hold on a book you've checked out" << std::endl;
			return;
		}
	}


  // Update the Book  with the request
  holdings[book].setRequestedBy(& members[member]);
	location = holdings[book].getLocation();
	if (location == ON_SHELF){
		holdings[book].setLocation(ON_HOLD);
	}

	std::cout << "\"" << holdings[book].getTitle() << " is on hold for " <<
		members[member].getName() << std::endl;
}

void Library::incrementCurrentDate()
{
	/*
	 *	• incrementCurrentDate
	 *	◦ increment current date; increase each Patron's fines by DAILY_FINE
	 *		for each overdue Book they have
	 */
  if (DBG_FUN) std::cout << "Library::incrementCurrentDate" << std::endl;

	currentDate ++;

	std::vector <Book *> checkedOut;

	for (int member=0; member < members.size(); member++)
	{
		// For each member
		checkedOut = members[member].getCheckedOutBooks();
		if (checkedOut.size() != 0 )
		{
			// For each book the member has checked out
			for (int b=0; b < checkedOut.size(); b++ )
			{
				int timeOut = (currentDate - (* checkedOut[b]).getDateCheckedOut());
				//int allowedTime = (* checkedOut[b]).getCheckOutLength();
				int allowedTime = Book::CHECK_OUT_LENGTH;

				if ( timeOut >=  allowedTime)
				{
					if (DBG_VERBOSE) 
						std::cout << "Incrementing fine for user " << members[member].getName()
							<< " on book " << (* checkedOut[b]).getTitle() << std::endl;
					members[member].amendFine(DAILY_FINE);
				}
			}
		}
	}
}
	
void Library::payFine(std::string patronID, double payment)
{
	/*
	 * • payFine
	 *	◦ if the specified Patron is not in the Library, print out that
	 *		message and return to the menu
	 *	◦ use amendFine to update the Patron's fine; print out that the
	 *		fines for Patron name are now Patron fineAmount checked out
	 *		(using amendFine)
	 */
  if (DBG_FUN) std::cout << "Library::payFine" << std::endl;
	int member = findMember(patronID);
	double owed;
	if (member < 0)
	{
		std::cout << "Couldn't find that person in our membership" << std::endl;
		return;
	}

	members[member].amendFine( - (payment)); // No validation of payment
	owed = members[member].getFineAmount();

	if ( owed < 0 )
	{
		std::cout << "Member credit:      $" << std::setprecision(2)  << std::fixed
		<<  owed << std::endl;
	}
	else
	{
		std::cout << "Current balance is: $" << std::setprecision(2)  << std::fixed
		<<  owed << std::endl;
	}
}

void Library::viewPatronInfo(std::string patronID)
{
	/*
	 * • viewPatronInfo
	 *	◦ if the specified Patron is not in the Library, print out that
	 *		message and return to the menu
	 *	◦ print the Patron's ID, name, any checked out Books and their
	 *		current fines
	 */
  if (DBG_FUN) std::cout << "Library::viewPatronInfo" << std::endl;
	int member = findMember(patronID);
	std::vector <Book *> checkedOut;
	std::string tab = "         ";

	if (member < 0)
	{
		std::cout << "Couldn't find that person in our membership" << std::endl;
		return;
	}

  // Print Member ID and Name
	std::cout << members[member].getIdNum() << "     " 
		<< members[member].getName() << std::endl;

  // If they have books checked out, print those
	checkedOut = members[member].getCheckedOutBooks();
	if (checkedOut.size() > 0 )
		std::cout << tab << "Books checked out:" << std::endl;
	for (int i=0; i < checkedOut.size(); i++)
	{
		std::cout << tab << (* (checkedOut[i])).getIdCode() << "    " 
			<< (* (checkedOut[i])).getTitle() << ",  "
			<< (* (checkedOut[i])).getAuthor() << std::endl;
	}

	// Only print fines if they are not zero
  double tmpFines = members[member].getFineAmount();
	if (tmpFines > 0)
	{
		std::cout << std::setprecision(2) << std::fixed << tab 
			<< "Current fines: $ " << tmpFines << std::endl;
	}
	else if (tmpFines < 0)
	{
		std::cout << std::setprecision(2) << std::fixed << tab 
			<< "Member credit: $ " << tmpFines << std::endl;
	}
}

void Library::viewBookInfo(std::string bookID)
{
	/*
	 * • viewBookInfo
	 *	◦ if the specified Book is not in the Library, print out that
	 *		message and return to the menu
	 *	◦ print the Book's ID, title, author and location; if it's on
	 *		request, print who it's requested by; if it's checked	out,
	 *		print who it's checked out by, and it's due date (date checked
	 *		out + check out length)
	 *	• be careful - a Book can be on request without its location being
	 *		the hold shelf (if another Patron has it checked out);
	 */
  if (DBG_FUN) std::cout << "Library::viewBookInfo" << std::endl;
	bool bookFound = false;
	std::string tab = "            ";
  
	int book = findBook(bookID);

	if (book < 0)
	{
		std::cout << "Couldn't find that book in our collection." << std::endl;
		return;
	}


  // Print the ID, Title and Author of the book
	std::cout << holdings[book].getIdCode() << "    " 
		<< holdings[book].getTitle() << ",  "
		<< holdings[book].getAuthor() << std::endl;

	Locale location = holdings[book].getLocation();
	Patron * requestedBy = holdings[book].getRequestedBy();


	// To avoid screen noise, don't show location if it's on the shelf
  // If the book is NOT on the shelf, print it's location and show
	// which member has it checked out and/or on hold

	if (location == CHECKED_OUT)
	{
		std::cout << tab << "Current location: " << LocaleString[location] 
			<< " to " << (*(holdings[book].getCheckedOutBy())).getName()
			<< ", due date is " 
			<< (holdings[book].getDateCheckedOut() + Book::CHECK_OUT_LENGTH )
			<< std::endl;
	}
	else if (location == ON_HOLD || requestedBy != NULL ) {
		// If the location is ON HOLD, or if the book is on the shelf but
		// requested by someone, print the location
		std::cout << tab << "Current location: " << LocaleString[location] << std::endl;
	}
	if ( requestedBy != NULL )
	{
		// Print if someone has the book on hold
		std::cout << tab << "Hold requested by: " << (*requestedBy).getName() << std::endl;
		return;
	}
}

void Library::listAllBooks()
{
  /*
	 * An extremely useful function for debugging, also much faster than
	 * typing in single-book information even when you only want to look
	 * at a single book
	 *
	 * Does just what it says
	 */
	std::cout << std::endl << "Showing all books in the library:" << std::endl;
	for (int i=0; i < holdings.size(); i++)
		viewBookInfo(holdings[i].getIdCode());
}

void Library::listAllPatrons()
{
  /*
	 * An extremely useful function for debugging, also much faster than
	 * typing in single-member information even when you only want to look
	 * at a single member
	 *
	 * Does just what it says
	 */
	std::cout << std::endl << "Showing all library members:" << std::endl;
	for (int i=0; i < members.size(); i++)
		viewPatronInfo(members[i].getIdNum());
}

int  Library::findBook(std::string bookID)
{
	/* 
	 * Returns the index in the holdings vector for the given bookID,
	 * or -1  if the book is not found
	 */
	if (DBG_FUN) std::cout << "Library::findBook" << std::endl;
	for (int h=0; h < holdings.size(); h++)
	{
		if ( bookID.compare( holdings[h].getIdCode()) == 0 )
		{
			return(h);
		}
	}
	return (-1); // ERROR
}

int  Library::findMember(std::string patronID)
{
	/* 
	 * Returns the index in the members vector for the given patronID,
	 * or -1  if the patron is not found
	 */
	if (DBG_FUN) std::cout << "Library::findMember" << std::endl;
	for (int m=0; m < members.size(); m++)
	{
		if ( patronID.compare( members[m].getIdNum()) == 0 )
		{
			return(m);
			
		}
	}
	return (-1); // ERROR
}

int Library::getCurrentDate()
{
	return currentDate;
}

/* These functions are not used and are not fully implemented */

std::string  Library::getNextMemberId(int &nextMemberNum)
{
	int tmpInt = 10000 + nextMemberNum;
	//TODO:  arrgh!  how to make this work without itoa??
	//Turns out it doesn't matter... The assigment explicitly
	//does not allow autogenerating ID numbers.
}

int  Library::getNextMemberNum()
{
	std::string tmpStr;
	std::string::size_type found;
	int tmpNum;
	int hiNum = 0;

	for (int m=0; m < members.size(); m++)
	{
		tmpStr = members[m].getIdNum();
		found = tmpStr.find_first_of("123456789");
		//tmpNum = atoi( (tmpStr.substr(found, tmpStr.length() -found)).c_str());
		if (tmpNum > hiNum)
			hiNum = tmpNum;
	}
	return (hiNum);
}

