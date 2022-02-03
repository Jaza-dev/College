#include "Point.h"

Point::Point(int xx, int yy): x(xx), y(yy) { }

bool Point::operator==(const Point& p2) const {
	return (x == p2.x && y == p2.y);
}

double range(const Point& p1, const Point& p2) {
	return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}

ostream& operator<<(ostream& os, const Point& p) {
	return os << "(" << p.x << "," << p.y << ")";
}
