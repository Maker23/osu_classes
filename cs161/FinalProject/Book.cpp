#include <string>
#include "Book.h"
#include "Patron.h"

#include "debug.h"

Book::Book(std::string idc, std::string t, std::string a)
{
	idCode = idc;
	title = t;
	author = a;
	location = ON_SHELF;
	checkedOutBy = NULL;
	requestedBy = NULL;
	dateCheckedOut = -1;  // QUESTION ?
}

Book::Book()
{
	idCode = "";
	title = "";
	author = "";
	location = ON_SHELF;
	checkedOutBy = NULL;
	requestedBy = NULL;
	dateCheckedOut = -1;  // QUESTION ?
}

/**** Book:: Getters ****/

int Book::getCheckOutLength()
{
	if (DBG_TESTING )
		return 2; // Seriously, who's going to wait 21 'days'?
	else
		return CHECK_OUT_LENGTH;
}

std::string Book::getIdCode()
{
	return idCode;
}

std::string Book::getTitle()
{
	return title;
}

std::string Book::getAuthor()
{
	return author;
}

Locale Book::getLocation()
{
	return location;
}

Patron* Book::getCheckedOutBy()
{
	return checkedOutBy;
}

Patron* Book::getRequestedBy()
{
	return requestedBy;
}

int Book::getDateCheckedOut()
{
	return dateCheckedOut;
}
/**** Book:: Setters ****/
void Book::setLocation(Locale lo)
{
	location = lo;
}

void Book::setCheckedOutBy(Patron* p)
{
	checkedOutBy = p;
}

void Book::setRequestedBy(Patron* p)
{
	requestedBy = p;
}
void Book::setDateCheckedOut(int d)
{
	dateCheckedOut = d;
}
