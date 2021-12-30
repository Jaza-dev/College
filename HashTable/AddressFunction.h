#pragma once
#include "includes.h"

class AddressFunction {
public:
	virtual int getAddress(string& key, int mAddress, int attemptCount, int tableCap, int compareValue) = 0;
};

