/* vim: ts=2
 *
 *  Author: Shoshana Abrass   abrasss@onid.oregonstate.edu
 *  Date Created: 2014/11/24
 *  Last Modification date: 2014/11/30
 *  Filename: 
 *
 *  Overview:
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>

enum Action {Add, List, Total, Quit, unknown};
Action	 getUserAction();
/****************************************************************/
class Item {
	std::string Name;
	double Price;
	int Qty;
 public:
	Item(std::string name, double price, int qty);
	void setItem(std::string name, double price, int qty);
	double getPrice();
	std::string getName();
	int getQty();
};
Item::Item(std::string name, double price, int qty)
{
	Name = name;
	if ( price < 0 )
	{
		std::cout << "Warning: can't have a negative price. Setting price to $0" << std::endl;
		Price = 0;
	}
	else
	{
		Price = price;
	}
	if ( qty < 0 )
	{
		std::cout << "Warning: can't have a negative quantity. Setting  quantity to 0" << std::endl;
		Qty = 0;
	}
	else
	{
		Qty = qty;
	}
}
void Item::setItem(std::string name, double price, int qty)
{
	Name = name;
	Price = price;
	Qty = qty;
}
double Item::getPrice()
{
	return Price;
}
std::string Item::getName()
{
	return Name;
}
int Item::getQty()
{
	return Qty;
}
/****************************************************************/
class ShoppingCart {
	std::vector <Item> Items;

 public:
	void addItem(Item item);
	void listItems();
	void totalPrice();
};
/****************************************************************/

void newItem(ShoppingCart&);
int main () 
{
	ShoppingCart Cart;
	Action nextAction = Quit;

	std::cout << "Welcome to your shopping cart! What do you want to do next?"
		<< std::endl;
	do
	{
		nextAction = getUserAction();
		switch (nextAction){
			case Add:
				newItem(Cart);
				break;
		 	case List:
				Cart.listItems();
				break;
			case Total:
				Cart.totalPrice();
				break;
			case Quit:
				break;
			default:
				std::cout << "Unrecognized command; please try again." << std::endl;
				break;
		}
	}
	while (nextAction != Quit);

}

/**********************************************
 * 		Purpose:
 * 		Arguments:
 * 		Returns:
 *********************************************/
void newItem(ShoppingCart &Cart)
{
	std::string tmpString;
	std::string tmpName;
	int tmpQty;
	double tmpPrice;

	std::cout << "Item name: ";
		getline(std::cin, tmpName);
	std::cout << "Price: ";
		getline(std::cin, tmpString);
		tmpPrice = atof ( tmpString.c_str());
	std::cout << "Quantity: ";
		getline(std::cin, tmpString);
		tmpQty = atoi ( tmpString.c_str());
  
	Item item(tmpString, tmpPrice, tmpQty);
	Cart.addItem(item);
}
void ShoppingCart::addItem(Item item)
{
	Items.push_back(item);
}
void ShoppingCart::listItems()
{
	for (int i=0; i< Items.size(); i++)
	{
		std::cout << "Item:    " << Items[i].getName() << std::endl
			<< "  Price: " << std::fixed << std::setprecision(2) << Items[i].getPrice() << std::endl
			<< "  Qty:   " << Items[i].getQty() << std::endl;
	}
}
/**********************************************
 * 		Purpose:
 * 		Arguments:
 * 		Returns:
 *********************************************/
void ShoppingCart::totalPrice()
{
	double priceTotal = 0.0;
	for (int i=0; i< Items.size(); i++)
	{
			priceTotal += ( (Items[i].getPrice()) * (Items[i].getQty()));
	}
	std::cout << "Total price of all items: $" << std::fixed<< std::setprecision(2)<< priceTotal<< std::endl;
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
