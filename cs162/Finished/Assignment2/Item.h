//vim:ts=2
//
/***********************************************************
 *
 * Item header file
 *
 *
 *
 *
 */
#ifndef Book_h
#define Book_h

#include <string>

class Item
{
private:
	std::string Name;
	std::string Unit;
	int Qty;
	float UnitPrice;
public:
  Item();
  Item(std::string _Name, std::string _Unit,int _Qty, float _UnitPrice);

	std::string getName();
	std::string getUnit();
	int getQty();
	float getUnitPrice();

	void setQty(int _Qty);
	void setUnitPrice(float _UnitPrice);
};
#endif
