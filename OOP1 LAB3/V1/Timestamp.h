#pragma once
#include "includes.h"

class Timestamp {
private:
	int year, month, day, hour, minute;
public:
	Timestamp(int y, int m, int d, int h, int min): year(y), month(m), day(d), hour(h), minute(min) {}
	friend ostream& operator<< (ostream& os, const Timestamp& ts);
};

