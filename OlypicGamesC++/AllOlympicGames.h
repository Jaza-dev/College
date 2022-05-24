#pragma once
#include "Game.h"

class AllOlympicGames {
private:
	static AllOlympicGames* allGames;
	vector<Game*> games;

	AllOlympicGames() {}
	Game* getGame(int year, string& season, string& city);
	void parseAllAthletes(string filename);
public:
	~AllOlympicGames();
	static AllOlympicGames* getAllOlympicGames() {
		if (allGames == nullptr) {
			allGames = new AllOlympicGames();
		}
		return allGames;
	}

	void parse(string filename, int year = -1);

	int countOfAllAthletes(string& sport, string& country, string& year, string& type, string& medal);
	int countOfAllDisciplins(string& sport, string& country, string& year, string& type, string& medal);
	double averageHight(string& sport, string& country, string& year, string& type, string& medal);
	double averageWeight(string& sport, string& country, string& year, string& type, string& medal);

	int numberOfSports(string& country);
	string* threeBestCountries(string& year, string& season);
	set<string> countriesThatWereTheBestOnce();
	vector<Athlete*> tenYoungestAthletesThatWonMedal();
	vector<pair<string, Athlete*>> getPairsWithMedalInIndividualAndTeam();
	set<Athlete*> allAthletesParticipatedOnPairOfGames(pair<Game*, Game*> pairOfGames);
	set<string> olympicCities();
	vector<Team*> getAllTeams(string& country, string& year, string& season);
};