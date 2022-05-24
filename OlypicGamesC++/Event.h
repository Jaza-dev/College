#pragma once
#include "includes.h"

class Sport;

class Event {
private:
	string disciplin, type;
	Sport* sport;
public:
	Event(string disciplin, string type, Sport* sport):disciplin(disciplin), type(type), sport(sport) {}
	string& getDisciplin() { return this->disciplin; }
	string& getType() { return this->type; }
	Sport* getSport() { return this->sport; }
};
