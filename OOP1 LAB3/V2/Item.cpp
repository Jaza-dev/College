#include "Item.h"

Item::Item(string n, int bc, double pp) {
	name = n;
	barCode = bc;
	purPrice = pp;
}

string& Item::getName() {
	return name;
}

int Item::getBarCode() {
	return barCode;
}

double Item::getPurPrice() {
	return purPrice;
}

bool operator==(const Item& i1, const Item& i2) {
	return i1.barCode == i2.barCode;
}