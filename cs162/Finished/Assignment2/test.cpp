//vim:ts=2
//
/*
 *
 *
 */

#include <climits>

#define DEBUG true  // define this before we include local files
#include "Item.h"
#include "List.h"
#include "validateNumericInput.h"


void testListClass();
void testItemClass();

int main()
{
	testItemClass();
	testListClass();
}

/*****************************************************************/
void testItemClass()
{
	Item testItem("ItemTest", "jar", 1, 10.00);
	Item negPrice("NegPrice", "can", 1, -5.00);
	Item negQty("NegQty", "can", -1, 5.00);
	Item floatQty("FloatQty", "bag", 1.01, 5.50);
	Item defaultConstructor();
}
void testListClass()
{
	std::string fileName = "myListTest.data";
	std::string output_fileName = "myListTest.output";
	std::string tmpString;
	
	// Declare a list and initialise it from a file
	List myList(fileName);  // Aargh, need to test and exit!

	myList.printAll();
	std::cout << "Hit <return> to begin testing: ";
	getline(std::cin, tmpString);

	std::cout << "Should SUCCEED:" << "-------------" << std::endl;

  std::cout << "===== Changing quantity of line item 5 to 2" << std::endl;
	myList.changeQty(4,2);

  std::cout << "===== Changing quantity of line item 6 to 0" << std::endl;
	myList.changeQty(5,0);

  std::cout << "===== Changing price of line item 2 to 1.11111" << std::endl;
	myList.changePrice(1, 1.11111);

  std::cout << "===== Changing price of line item 3 to 20" << std::endl;
	myList.changePrice(2, 20);

	std::cout << "Should FAIL:" << "-----------" << std::endl;

  std::cout << "===== Changing quantity of line item 100" << std::endl;
	myList.changeQty(100,0); 

  std::cout << "===== Changing quantity of line item 5 to -2" << std::endl;
	myList.changeQty(4,-2);

  std::cout << "===== Changing price of line item 4 to -10" << std::endl;
	myList.changePrice(3, -10);

	myList.printAll();

	std::cout << "Hit <return> to continue testing: ";
	getline(std::cin, tmpString);

	std::cout << "TESTING: When prompted, enter a negative price ========" << std::endl;;
	myList.addItem();
	std::cout << "TESTING: When prompted, enter a negative quantity =====" << std::endl;
	myList.addItem();

	myList.printAll();
	myList.saveAll(output_fileName);

}
