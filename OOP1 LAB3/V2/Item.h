#pragma once
#include "includes.h"

class Item {
private:
	string name;
	int barCode;
	double purPrice;
public:
	Item(string n, int bc, double pp);
	string& getName();
	int getBarCode();
	double getPurPrice();
	friend bool operator==(const Item& i1, const Item& i2);
};

