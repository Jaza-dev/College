#include "Game.h"

Game::~Game() {
	for (Sport* sport : sports) {
		delete sport;
	}

	for (pair<string, vector<Competitor*>> p : countries) {
		for (Competitor* comp : p.second) {
			delete comp;
		}
	}
}

Sport* Game::getSport(string& name) {
	//eather returns already created sport or return newly created
	for (Sport* sport : sports) {
		if (sport->getName() == name) return sport;
	}
	Sport* newSport = new Sport(name);
	sports.push_back(newSport);
	return newSport;
}
bool Game::hasSport(string& name) {
	for (Sport* sport : sports) {
		if (sport->getName() == name) return true;
	}
	return false;
}

void Game::addCompetitor(string& country, Competitor* competitor) {
	//add competitor
	countries[country].push_back(competitor);
}
