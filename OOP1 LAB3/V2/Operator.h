#pragma once
#include "Item.h"

class Package;

class Operator {
private:
public:
	virtual ~Operator() {};
	virtual Operator* vCopy() = 0;
	virtual void countDetails(Package* p) = 0;
};

