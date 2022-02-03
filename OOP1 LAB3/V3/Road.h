#pragma once
#include "includes.h"
#include "List.h"
#include "Point.h"
#include "Errors.h"

class Road {
private:
	List<Point*> points;
	bool isIn(Point* p);
	void copy(const Road& r);
	void move(Road& r);
	void del();
public:
	Road() = default;
	Road(const Road& r);
	Road(Road&& r);
	Road& operator=(const Road& r);
	Road& operator=(Road&& r);
	~Road();
	Road& operator+=(Point* p);
	double length() const;
	friend ostream& operator<<(ostream& os, const Road& r);
};

