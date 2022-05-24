#pragma once
#include "includes.h"

class Athlete;
class Event;

class Competitor {
private:
	enum Medal { GOLD, SILVER, BRONZE, NO_MEDAL };
	Event* event;
	Medal medal = NO_MEDAL;
public:
	Competitor(Event* e, string medal):event(e){
		if (medal == "Gold") this->medal = GOLD;
		else if (medal == "Silver") this->medal = SILVER;
		else if (medal == "Bronze") this->medal = BRONZE;
		else this->medal = NO_MEDAL;
	}
	Event* getEvent() { return this->event; }
	string getMedal() { 
		if (medal == GOLD) return "Gold";
		else if (medal == SILVER) return "Silver";
		else if (medal == BRONZE) return "Bronze";
		else return "NO MEDAL";
	}
	virtual vector<Athlete*>& getVectorOfAthletes() abstract;
};