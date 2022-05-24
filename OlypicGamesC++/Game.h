#pragma once
#include "includes.h"
#include "Sport.h"
#include "Athlete.h"
#include "Team.h"

class Game {
private:
	int year;
	string season, city;
	vector<Sport*> sports; //all sports played on that specific olypic game that year
	map<string, vector<Competitor*>> countries; //all countries and players that year
public:
	Game(int y, string s, string c) : year(y), season(s), city(c) {}
	~Game();
	int getYear() { return this->year; }
	string& getSeason() { return this->season; }
	string& getCity() { return this->city; }
	map<string, vector<Competitor*>>& getCountries() { return countries; }

	Sport* getSport(string& name);
	bool hasSport(string& name);
	void addCompetitor(string& country, Competitor* competitor);
};