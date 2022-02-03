#pragma once
#include "Vehicle.h"

class NormalVehicle: public Vehicle {
private:
protected:
	int startPrice = 120;
public:
	NormalVehicle(string m);
	~NormalVehicle() override{}
	double transportPrice(Road& r) override;
};

