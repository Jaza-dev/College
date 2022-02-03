#include "Vehicle.h"

const double Vehicle::unitPrice = 0.1;

void Vehicle::print(ostream& os) const{
	os << model;
}

Vehicle::Vehicle(string m) {
	model = m;
}

double Vehicle::transportPrice(Road& r) {
	return 0;
}

ostream& operator<<(ostream& os, const Vehicle& v) {
	v.print(os);
	return os;
}
