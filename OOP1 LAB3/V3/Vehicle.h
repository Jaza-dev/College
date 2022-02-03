#pragma once
#include "Road.h"

class Vehicle {
private:
protected:
	static const double unitPrice;
	string model;
	int startPrice = 0;
	virtual void print(ostream& os) const;
public:
	Vehicle(string m);
	virtual ~Vehicle() = default;
	virtual double transportPrice(Road& r);
	friend ostream& operator<<(ostream& os, const Vehicle& v);
};

