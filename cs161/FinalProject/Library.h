// vim: ts=2
//
//  Library.h
//  examples
//
//  Created by Tim Alcon on 11/25/14.
//  Copyright (c) 2014 Tim Alcon. All rights reserved.
//

#ifndef __examples__Library__
#define __examples__Library__

#include <vector>
#include <stdio.h>

class Patron;
class Book;

class Library
{
private:
    std::vector<Book> holdings;
    std::vector<Patron> members;
    int currentDate;

public:
    static const double DAILY_FINE = 0.1;

    Library(); 

		/* Interactive addBook and addMember take no arguments.
		 * When reading data from a file, they take a Book or Patron reference */
    void addBook();
    void addMember();
    void addBook(Book &);
    void addMember(Patron &);

		/* Standard library functions required by the assignment */
    void checkOutBook(std::string patronID, std::string bookID);
    void returnBook(std::string bookID);
    void requestBook(std::string patronID, std::string bookID);
    void incrementCurrentDate();
    void payFine(std::string patronID, double payment);
    void viewPatronInfo(std::string patronID);
    void viewBookInfo(std::string bookID);

    /* Helpful functions for debugging */
		void listAllBooks();
		void listAllPatrons();
		int  findBook(std::string bookID);
		int  findMember(std::string patronID);
		int	 getCurrentDate();

		/* These are not used because the assignment specifically forbade it */
		std::string getNextMemberId(int &);
		int getNextMemberNum();
};

#endif /* defined(__examples__Library__) */
