/* vim: ts=2
 *
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/11/17
 *  Last Modification date: 2014/11/23
 *  Filename: 
 *
 *  Overview:
 * 	Define a struct called Item that consists of a string called name, a double
 * 	called price, and an int called quantity. Create an array of Item called
 * 	shoppingCart (you can assume a maximum of 100 Items). Display a menu that
 * 	gives the following options: 
 *
 * 	◦ Add item: this allows the user to enter the information for a new Item,
 * 		which is then added to the cart.
 *	◦ List contents: this lists the name, price and quantity for all Items in
 *		the cart. All prices should be displayed with two decimal places. Use
 *		showpoint and setprecision for this (section 3.7).  
 * 	◦ Total price: this displays the total cost of all Items in the cart (with
 * 		two decimal places) - no sales tax, since OSU is in Oregon. :) 
 *	◦ Quit: exits the program.  
 *
 *	You should write a separate function to handle each of the first three options.  
 *
 *	Input validation: Verify that the user enters a valid double for price and
 *	a valid int for quantity. If an input isn't valid, prompt the user to try
 *	again.
 */

#include <iostream>
#include <cstdlib>

struct Item {
	std::string Name;
	double Price;
	int Qty;
};
enum Action {Add, List, Total, Quit, unknown};

void addItem(Item * itemPtr);
void listCart(Item ** cartPtr, int numItems);
void totalCart(Item ** cartPtr, int numItems);
void emptyCart(Item ** cartPtr, int numItems);
Action	 getUserAction();

int main () 
{
	Item *shoppingCart[100]; // An array of pointers to Items
	Action nextAction = Quit;
	int numItems = 0;

	std::cout << "Welcome to your shopping cart! What do you want to do next?"
		<< std::endl;
	do
	{
		nextAction = getUserAction();
		switch (nextAction){
			case Add:
				shoppingCart[numItems] = new Item;
				addItem(shoppingCart[numItems++]);
				break;
		 	case List:
				listCart(shoppingCart, numItems);
				break;
			case Total:
				totalCart(shoppingCart, numItems);
				break;
			case Quit:
				break;
			default:
				std::cout << "Unrecognized command; please try again." << std::endl;
				break;
		}
	}
	while (nextAction != Quit);

  // Clean up memory before exiting
	for (int i=0; i< numItems; i++)
		delete(shoppingCart[i]);
}

/**********************************************
 * 		Purpose:
 * 		Arguments:
 * 		Returns:
 *********************************************/
void addItem(Item * itemPtr)
{
	std::string tmpString;

	std::cout << "Item name: ";
		getline(std::cin, (*itemPtr).Name);
	std::cout << "Price: ";
		getline(std::cin, tmpString);
		(*itemPtr).Price = atof ( tmpString.c_str());
	std::cout << "Quantity: ";
		getline(std::cin, tmpString);
		(*itemPtr).Qty = atoi ( tmpString.c_str());
}
/**********************************************
 * 		Purpose:
 * 		Arguments:
 * 		Returns:
 *********************************************/
void listCart(Item ** cartPtr, int numItems)
{
	for (int i=0; i<numItems;i++)
	{
		std::cout << "Item:    " << (*(cartPtr[i])).Name << std::endl
			<< "  Price: " << cartPtr[i]->Price << std::endl
			<< "  Qty:   " << cartPtr[i]->Qty << std::endl;
	}
}
/**********************************************
 * 		Purpose:
 * 		Arguments:
 * 		Returns:
 *********************************************/
void totalCart(Item ** cartPtr, int numItems)
{
	double priceTotal = 0.0;
	for (int i=0; i<numItems;i++)
	{
			priceTotal +=  ((cartPtr[i]->Price) * (cartPtr[i]->Qty));
	}
	std::cout << "Total price of all items: $" << priceTotal<< std::endl;
}
/**********************************************
 * 		Purpose:
 * 		Arguments:
 * 		Returns:
 *********************************************/
void emptyCart(Item ** cartPtr, int numItems)
{
	// In theory we could release all the memory here
}
/**********************************************
 * 		Purpose:
 * 		Arguments:
 * 		Returns:
 *********************************************/
Action	 getUserAction()
{
	char Menu[] = {'A','L','T','Q'};
	char userInput;
	Action menuChoice;
	int buflen=1024;
	char buffer[buflen];
	int i;

	std::cout << "[A]dd item, [L]ist cart, [T]otal item price, [Q]uit: ";
  userInput = std::cin.get();	
	std::cin.getline(buffer,buflen);
	for (i=0; i<4; i++ )
	{
		if ( toupper(userInput) == Menu[i] )
		{
			menuChoice = (Action) i;
			return (menuChoice);
		}
	}
	// users's choice wasn't found in the menu
	
	return(unknown);
}
