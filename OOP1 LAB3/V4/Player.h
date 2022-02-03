#pragma once
#include "includes.h"

class Player {
private:
	string name;
	int value;
public:
	Player(string n, int v = 1000): name(n), value(v){}
	//string& getName() { return name; }
	int getValue() const { return value; }
	int incValue(double percent);
	bool operator==(const Player& p2) const;
	friend ostream& operator<<(ostream& os, const Player& p);
};

