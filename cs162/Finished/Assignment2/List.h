//vim:ts=2
//
/***********************************************************
 *
 * List class library
 *
 *
 *
 *
 */

#include <iostream>
#include <string>
#include <vector>

#include "Item.h"

class List
{
private:
	char dataFileDelimiter;
	int dataFileMaxWordLength;
	std::vector<Item> myItems;  	
	std::string dataFileCommentHeader;

	int readAll(std::string fileName);
	void readOneItem(std::string inputLine);
	bool printItem(int listIndex);
	void printScreenHeader();
	// This version of addItem is only called by readOneItem()
	bool addItem(int Qty, std::string Name, std::string Unit, float UnitPrice);

public:
	bool needToSaveData;
	List(); // constructor
	List(std::string fileName); // constructor
	bool addItem();
	bool deleteItem(int listIndex);
	bool changeQty(int listIndex, int newQty);
	bool changePrice(int listIndex, float newPrice);
	void printAll();
	bool saveAll(std::string fileName);
	int  itemCount();
};
