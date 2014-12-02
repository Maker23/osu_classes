/* Function prototypes */

#include <iostream>
#include <fstream>
#include <sstream>

#include "Library.h"
#include "Book.h"
#include "Patron.h"

#ifndef DEBUG
#define DEBUG false
#endif

void	readDataFromFile(Library &centralLibrary);
void	readBookOneLine(std::string inputLine, Library &centralLibrary);

//void	readDataFromFile(Library.members &patronList);

/*****************************************************
 * readDataFromFile
 * 
 *****************************************************/
void readDataFromFile(Library &centralLibrary)
{
	std::string inputLine;
	std::ifstream bookFile("books.data");
	std::ifstream patronFile("patrons.data");

  if ( bookFile.is_open() )
	{
		while ( ! bookFile.eof() )
		{
			getline(bookFile, inputLine);
			readBookOneLine(inputLine, centralLibrary);
		}
	}

  if ( patronFile.is_open() )
	{
		while ( ! patronFile.eof() )
		{
			getline(patronFile, inputLine);
			readBookOneLine(inputLine, centralLibrary);
		}
	}
}

/*****************************************************
 * 
 ****************************************************/
void readBookOneLine(std::string inputLine, Library &centralLibrary)
{
	bool goodData;
	char tmpbuf[1024];			// cstring for parsing the line
	char delimiter = ':'; 	// The word separating character in the file
  std::vector <std::string> Word;	// The input line, separated into words
	std::string item;				// convert cstrings into std::strings


	if(DEBUG) std::cout << "readOneLine\n";

  std::stringstream ss(inputLine);
  while (ss.getline(tmpbuf, 1024, delimiter)) {
		if(DEBUG) std::cout << "tmpbuf = " << tmpbuf << "\n";
		item = tmpbuf;
		Word.push_back(item);
  }
	if ( Word.size() == 0 )
		return;

  if ( Word.size() == 2 )
	{
		// Word should contain:
		// 	0     1 
		// 	IDN, Name
		if (DEBUG) std::cout << "Adding a Patron with " << Word[0] << " " << Word[1] << std::endl;
  	Patron tmpPatron(Word[0], Word[1]);
		centralLibrary.addMember(tmpPatron);
  }
  if ( Word.size() == 3 )
	{
		// Word should contain:
		// 	0     1      2    
		// 	IDC, Title, Author
		if (DEBUG) std::cout << "Adding a book with " << Word[0] << " " << Word[1] << " " << Word[2] << std::endl;
  	Book tmpBook(Word[0], Word[1], Word[2]);
		centralLibrary.addBook(tmpBook);
  }
}
