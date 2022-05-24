#pragma once
#include "includes.h"
#include "Event.h"

class Sport {
private:
	string name;
	vector<Event*> events;
public:
	Sport(string nameOfSport): name(nameOfSport) {}
	~Sport();
	string& getName() { return this->name; }

	Event* getEvent(string& disciplin, string& type, Sport* sport);
};