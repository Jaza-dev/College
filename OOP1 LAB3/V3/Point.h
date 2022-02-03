#pragma once
#include "includes.h"

class Point {
private:
	int x, y;

public:
	Point(int xx, int yy);
	bool operator==(const Point& p2) const;
	friend double range(const Point& p1, const Point& p2);
	friend ostream& operator<<(ostream& os, const Point& p);
};

