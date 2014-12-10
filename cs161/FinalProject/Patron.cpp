#include <iostream>
#include <string>
#include <vector>
#include "Patron.h"
#include "Book.h"
#include "debug.h"


Patron::Patron(std::string idn, std::string n)
{
	idNum = idn; // Uniqueness is checked before calling; see instructions
	name = n;
  fineAmount = 0;
}

Patron::Patron()
{
	idNum = ""; 
	name = "";
  fineAmount = 0;
}

/**** Patron:: Getters ****/
std::string Patron::getIdNum()
{
	return idNum;
}

std::string Patron::getName()
{
	return name;
}

std::vector<Book*> Patron::getCheckedOutBooks()
{
	return checkedOutBooks;
}

double Patron::getFineAmount()
{
	return fineAmount;
}

void Patron::addBook(Book* b)
{
	checkedOutBooks.push_back(b);
}

void Patron::removeBook(Book* b)
{
	std::string removeBookID = (*b).getIdCode();

	for (int i=0; i < checkedOutBooks.size(); i++)
	{
		if (removeBookID.compare((*(checkedOutBooks[i])).getIdCode()) == 0 )
		{
			// Find the book in the vector, identify the vector element number i
			if (DBG_VERBOSE) std::cout << "Removing book from patron's vector"
				<< std::endl;
			checkedOutBooks.erase(checkedOutBooks.begin() + i); 
			return;
		}
	}
}

void Patron::amendFine(double amount)
{
	fineAmount += amount;
}
