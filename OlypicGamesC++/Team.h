#pragma once
#include "includes.h"
#include "Competitor.h"
#include "Athlete.h"

class Event;

class Team :public Competitor {
private:
	vector<Athlete*> athletes;
public:
	Team(Event* e, string& medal): Competitor(e, medal){}
	void addAthlete(Athlete* athlete) {
		athletes.push_back(athlete);
	}
	int getSize() { return athletes.size(); }
	vector<Athlete*>& getVectorOfAthletes() override;
	friend ostream& operator<<(ostream& os, const Team* team);
};