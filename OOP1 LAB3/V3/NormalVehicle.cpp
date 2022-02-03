#include "NormalVehicle.h"

NormalVehicle::NormalVehicle(string m): Vehicle(m) { }

double NormalVehicle::transportPrice(Road& r) {
	return startPrice + r.length() * unitPrice;
}
