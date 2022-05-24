#include "Sport.h"

Sport::~Sport() {
	for (Event* e : events) {
		delete e;
	}
}

Event* Sport::getEvent(string& disciplin, string& type, Sport* sport)
{
	for (Event* e : events) {
		//eather return already created event, or makes new one and returns it
		if (e->getDisciplin() == disciplin && e->getType() == type) return e;
	}
	Event* newEvent = new Event(disciplin, type, sport);
	events.push_back(newEvent);
	return newEvent;
}