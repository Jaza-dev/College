#include "Team.h"

vector<Athlete*>& Team::getVectorOfAthletes() {
	return athletes;
}

ostream& operator<<(ostream& os, const Team* team) {
	int i = 0;
	os << "[ ";
	for (Athlete* ath : team->athletes) {
		if (i != 0)os << ", ";
		os  << ath->getName();
		i++;
	}
	return os << " ]" << endl;
}