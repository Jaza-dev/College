#include "Road.h"

bool Road::isIn(Point* p) {
    for (int i = 0; i < points.size(); i++) {
        if (*points[i] == *p) return true;
    }
    return false;
}

void Road::copy(const Road& r) {
    for (int i = 0; i < r.points.size(); i++) {
        *this += r.points[i];
    }
}

void Road::move(Road& r) {
    for (int i = 0; i < r.points.size(); i++) {
        this->points += r.points[i];
        r.points[i] = nullptr;
    }
}

void Road::del() {
    for (int i = 0; i < points.size(); i++) {
        delete points[i];
    }
}

Road::Road(const Road& r) {
    copy(r);
}

Road::Road(Road&& r) {
    move(r);
}

Road& Road::operator=(const Road& r) {
    if (this != &r) {
        del();
        copy(r);
    }
    return *this;
}

Road& Road::operator=(Road&& r) {
    if (this != &r) {
        del();
        move(r);
    }
    return *this;
}

Road::~Road() {
    del();
}

Road& Road::operator+=(Point* p) {
    if (isIn(p)) throw EAlreadyInList();
    points += new Point(*p);
}

double Road::length() const {
    double len = 0;
    for (int i = 0; i < points.size() - 1; i++) {
        len += range(*points[i], *points[i + 1]);
    }
    return len;
}

ostream& operator<<(ostream& os, const Road& r) {
    int i;
    for (i = 0; i < r.points.size() - 1; i++) {
        os << *r.points[i] << endl;
    }
    return os << *r.points[i];
}
