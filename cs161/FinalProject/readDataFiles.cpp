#include <iostream>
#include <fstream>
#include <sstream>

#include "Library.h"
#include "Book.h"
#include "Patron.h"

#ifndef DEBUG
#define DEBUG false
#endif

/* Function prototypes */
void	readDataFromFile(Library &centralLibrary);
void	readOneLine(std::string inputLine, Library &centralLibrary);


/*************************************************************
 * readDataFromFile
 *
 * Open the file(s) (file names are hardcoded here), get one line
 * at a time, and pass the line to the parsing function
 *************************************************************/
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
			readOneLine(inputLine, centralLibrary);
		}
	}

  if ( patronFile.is_open() )
	{
		while ( ! patronFile.eof() )
		{
			getline(patronFile, inputLine);
			readOneLine(inputLine, centralLibrary);
		}
	}
}

/*************************************************************
 *  readOneLine
 *
 *  Take one line of input, parse it into Words or tokens,
 *  and do something with the data.  This is all hardcoded
 *  for expediency.
 ************************************************************/
void readOneLine(std::string inputLine, Library &centralLibrary)
{
	char delimiter = ':'; 	// The word-separating character in the file
	char tmpbuf[1024];			// cstring for parsing the line
  std::vector <std::string> Word;	// The input line, separated into words
	std::string item;				// convert cstrings into std::strings


	if(DEBUG) std::cout << "readOneLine\n";

  // Break the line of data into tokens separated by ':'
  std::stringstream ss(inputLine);
  while (ss.getline(tmpbuf, 1024, delimiter)) {
		if(DEBUG) std::cout << "tmpbuf = " << tmpbuf << "\n";
		item = tmpbuf;
		Word.push_back(item);
  }

	if ( Word.size() == 0 )
		return; // No words found

  if ( Word.size() == 2 )
	{
		// Word vector should contain:
		// 	0     1 
		// 	IDN, Name
		if (DEBUG) std::cout << "Adding a Patron with " << Word[0] << " " << Word[1] << std::endl;
  	Patron tmpPatron(Word[0], Word[1]);
		centralLibrary.addMember(tmpPatron);
  }
  if ( Word.size() == 3 )
	{
		// Word vector should contain:
		// 	0     1      2    
		// 	IDC, Title, Author
		if (DEBUG) std::cout << "Adding a book with " << Word[0] << " " << Word[1] << " " << Word[2] << std::endl;
  	Book tmpBook(Word[0], Word[1], Word[2]);
		centralLibrary.addBook(tmpBook);
  }
}
