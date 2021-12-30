#pragma once
#include "includes.h"
#include "AddressFunction.h"
class SplitSequenceLinearHashing:public AddressFunction {
	int getAddress(string& key, int mAddress, int attemptCount, int tableCap, int compareValue) override;
};

