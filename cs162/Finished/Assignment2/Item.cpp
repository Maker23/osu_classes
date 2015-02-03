#include <string>
#include "Item.h"

/******** Item:: Constructors ********/
Item::Item(std::string _Name, std::string _Unit,int _Qty, float _UnitPrice)
{
	Name = _Name;	
	Unit = _Unit;

	// TODO: Allow negative prices if the item name contains "coupon"
	if (_UnitPrice < 0.0 ) 
		UnitPrice = 0.0;
	else 
		UnitPrice = _UnitPrice;

	// No negative quantities; these would be "returns", not supported in this version
	// TODO: allow decimal qualities (even less than 1) if the unit is
	// a measure of weight. Not supported in this version.
	if (_Qty < 1 ) 
		Qty = 0;
	else 
		Qty = _Qty;
}

Item::Item()
{
	Name = "";	
	Unit = "";
	UnitPrice = 0.0;
	Qty = 0;
}

/******** Item:: Getters ********/

std::string Item::getName()
{
	return Name;
}

std::string Item::getUnit()
{
	return Unit;
}

int Item::getQty()
{
	return Qty;
}

float Item::getUnitPrice()
{
	return UnitPrice;
}

/******** Item:: Setters ********/
void Item::setQty(int _Qty)
{
	if (_Qty < 1 ) 
		Qty = 0;
	else 
		Qty = _Qty;
}

void Item::setUnitPrice(float _UnitPrice)
{
	// TODO: Allow negative prices if the item name contains "coupon"
	if (_UnitPrice < 0.0 ) 
		UnitPrice = 0.0;
	else 
		UnitPrice = _UnitPrice;
}
