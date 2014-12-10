//
//  Book.h
//  examples
//
//  Created by Tim Alcon on 11/25/14.
//  Copyright (c) 2014 Tim Alcon. All rights reserved.
//

#ifndef examples_Book_h
#define examples_Book_h

class Patron;

enum Locale {ON_SHELF, ON_HOLD, CHECKED_OUT};

class Book
{
private:
    std::string idCode; // must be unique within the library
    std::string title;
    std::string author;
    Locale location;
    Patron* checkedOutBy;
    Patron* requestedBy;
    int dateCheckedOut;
public:
    static const int CHECK_OUT_LENGTH = 21;
    Book();
    Book(std::string idc, std::string t, std::string a);
    int getCheckOutLength();
    std::string getIdCode();
    std::string getTitle();
    std::string getAuthor();
    Locale getLocation();
    void setLocation(Locale lo);
    Patron* getCheckedOutBy();
    void setCheckedOutBy(Patron* p);
    Patron* getRequestedBy();
    void setRequestedBy(Patron* p);
    int getDateCheckedOut();
    void setDateCheckedOut(int d);
};

#endif
