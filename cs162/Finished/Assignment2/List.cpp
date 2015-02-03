//vim:ts=2
//
/***********************************************************
 *
 * List class library
 *
 *
 */

#include <cstdlib>  // atoi, atof
#include <fstream>
#include <iomanip> 	// setw
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Item.h"
#include "List.h"
#include "validateNumericInput.h"

#define DEBUG false

List::List()
{
	// declares but does not initialize myItems
}

List::List(std::string fileName)
{
	// declares but does not initialize myItems
	dataFileCommentHeader = "";
	dataFileDelimiter = 92;  // Backslash
	dataFileMaxWordLength = 2048; // A hardcoded word length
	readAll(fileName); // We don't do anything with this value for now
	needToSaveData = false;
}

bool List::addItem()
{
	std::string tmpName;
	std::string tmpUnit;
	std::string tmpString;
	std::string delimStr = std::string(1, dataFileDelimiter);
	int strPos;
	int tmpQty;
	float tmpUnitPrice;
	bool Success = true;

	std::cout << "Item name: ";
	std::getline(std::cin, tmpName);
  // Silently repress our delimiter.  DO NOT USE THE DELIMITER!!	
	while ( (strPos = tmpName.find(delimStr)) != std::string::npos) {
		tmpName.erase(tmpName.begin()+strPos);
	}


	std::cout << "Unit (eg: can,jar,bag,each): ";
	std::getline(std::cin, tmpUnit);

	std::cout << "Price per " << tmpUnit << ": ";
	std::getline(std::cin, tmpString);

	tmpUnitPrice = validateFloatInput((char *)tmpString.c_str(), 0.0, 19999.0);
	if ( tmpUnitPrice < 0.0 )
	{
		std::cout << "Error: setting price to $0.0" << std::endl;
		Success = false;
		tmpUnitPrice = 0.0;
	}

  // TODO: if unit is "lb", "pound", "oz", "ounce", "gram", "gm",
	// a decimal value should be accepted.
	std::cout << "Quantity [0-100] " ;
	std::getline(std::cin, tmpString);
	tmpQty = validateIntegerInput((char *)tmpString.c_str(), 0, 1999);
	if ( tmpQty < 0 )
	{
		std::cout << "Error: setting quantity to 0" << std::endl;
		Success = false;
		tmpQty = 0;
	}

	if (DEBUG) std::cout << "Adding Item \"" << tmpName << "\" qty: " << tmpQty << ", unit: " << tmpUnit << ", price = " << tmpUnitPrice << std::endl;

	Item tmpItem(tmpName,tmpUnit,tmpQty,tmpUnitPrice);

	myItems.push_back(tmpItem);  // TODO: Check return status
	if (DEBUG) std::cout << "exiting List::addItem" << std::endl;

	return(Success);

}

bool List::addItem(int _Qty, std::string _Name, std::string _Unit, float _UnitPrice)
{
	// TODO: Where should we validate values?

	Item tmpItem(_Name, _Unit, _Qty, _UnitPrice);
	myItems.push_back(tmpItem);
}

bool List::deleteItem(int listIndex)
{
	// Verify first?
  std::cout << "Deleting:" << std::endl;
	printItem(listIndex);
	myItems.erase(myItems.begin() + listIndex);
}

bool List::changeQty(int listIndex, int newQty)
{
	if ( listIndex >= 0 && listIndex < myItems.size())
	{
		myItems[listIndex].setQty(newQty);
		printItem(listIndex);
		return(true);
	}
	else
	{
		std::cout << "ERROR: Can't find that item on the list!"<< std::endl;
		return(false);
	}
}

bool List::changePrice(int listIndex, float newPrice)
{
	if ( listIndex >= 0 && listIndex < myItems.size())
	{
		myItems[listIndex].setUnitPrice(newPrice);
		printItem(listIndex);
		return(true);
	}
	else
	{
		std::cout << "ERROR: Can't find that item on the list!"<< std::endl;
		return(false);
	}
}

bool List::printItem(int listIndex)
{
	// std::cout << "Printing item " << listIndex << std::endl;
	if (myItems.size() < (listIndex ))
	{
		std::cout << "Zoicks, that item isn't on the list! Can't touch that." << std::endl;
		return(false);
	}
	//printScreenHeader();
	std::cout << 
		listIndex+1 << std::setw(4) << std::left << "."  <<
		std::setw(36) << std::left << myItems[listIndex].getName() << " " <<
		std::setw(8)  << myItems[listIndex].getUnit() << " "<<
		std::setw(3)  << myItems[listIndex].getQty() << " " <<
		std::right;
	if (myItems[listIndex].getQty() == 1)
	{
		std::cout <<  std::setprecision(2) << std::fixed <<
			std::setw(15)  << myItems[listIndex].getUnitPrice();
	}
	else
	{
		std::cout << std::setprecision(2) << std::fixed <<
			std::setw(5)  << myItems[listIndex].getUnitPrice() <<
			std::setw(10) << myItems[listIndex].getQty() * myItems[listIndex].getUnitPrice();
	}
	std::cout << std::endl;
	return(true);
}

int List::readAll(std::string fileName)
{
	// This is a private function, used by the constructor
  std::string comment = "#" ; // not implemented yet	
	std::string inputLine;
	std::ifstream dataFile(fileName);
	
	if (dataFile.is_open() && dataFile.good() )
	{
		while ( ! dataFile.eof() )
		{
			// TODO: I think we get an extra blank line out of this
			// eof isn't reached until getline fails?  need to test
			getline(dataFile, inputLine);
			readOneItem(inputLine);
		}
	}
	dataFile.close();
}

void List::readOneItem(std::string inputLine)
{
	if (DEBUG) std::cout << "Entering readOneItem with inputLine \n\t\"" << inputLine << "\"" << std::endl;

	char inputWord[dataFileMaxWordLength]; // A hardcoded word length
	char delimiter = dataFileDelimiter;  // Backslash. This should probably belong to the List class...
	std::vector <std::string> Word; // The input line, separated into words
	std::string tmpString;

  if ((inputLine.compare(0,2,"//") == 0)
		||(inputLine.compare(0,1,"#") == 0))
	{
		// Comment? Save and return.
		dataFileCommentHeader += inputLine;
		dataFileCommentHeader += '\n';
		return;
	}

  std::stringstream ss(inputLine); // Convert the string to a stream
	while (ss.getline(inputWord, 2048, delimiter)) {
		tmpString = inputWord; // Convert char[] to string
		Word.push_back(tmpString);
	}
	if (Word.size() != 4 )
	{
		if (DEBUG) std::cout << "Got " << Word.size() << " words out of input line" << std::endl;
		return; // Silently fail
	}
  
	// Input is not validated yet.  Should be done in addItem?

  addItem(atoi(Word[0].c_str()),Word[1], Word[2], atof(Word[3].c_str()));
}

void List::printScreenHeader()
{
	std::cout  <<
		std::setw(10) << std::left << "line #" << " " <<
		std::setw(30) << std::left << "item name" << " " <<
		std::setw(12)  << "qty" << "	" <<
		std::setw(5)  << "each" << " " << 
		std::setw(10)  << "subtotal" << std::endl << std::endl;
}
void List::printAll()
{
	float runningTotal = 0.0;

  if (DEBUG) std::cout << dataFileCommentHeader << std::endl;

	printScreenHeader();

	for (int i=0; i < myItems.size(); i++)
	{
		printItem(i);
		runningTotal += myItems[i].getQty() * myItems[i].getUnitPrice();
	}
	if (runningTotal > 0)
	{
		std::cout << 
			std::right <<
			std::setw(70) << "-------" << std::endl << 
			std::setw(60) << "TOTAL: " << std::setw(10) << runningTotal  << std::endl;
	}
}

bool List::saveAll(std::string fileName)
{
	std::ofstream saveFile(fileName);
	int runningCount = 0;
  
	if (! saveFile.good() )
	{
		std::cout << "Error: can't write to file " << fileName << std::endl;
		return(false);
	}

	saveFile << dataFileCommentHeader;

	for (int i=0; i < myItems.size(); i++)
	{
		saveFile <<
			myItems[i].getQty() << dataFileDelimiter <<
			myItems[i].getName() << dataFileDelimiter <<
			myItems[i].getUnit() << dataFileDelimiter <<
			myItems[i].getUnitPrice() << std::endl;
		runningCount ++;
	}

  if (DEBUG) std::cout << "Wrote " << runningCount << " items to "<< fileName << std::endl;
	
}

int List::itemCount()
{
	return(myItems.size());
}
