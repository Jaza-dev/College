#include "Athlete.h"

vector<Athlete*>& Athlete::getVectorOfAthletes() {
	return v;
}

ostream& operator<< (ostream& os, const Athlete& ath) {
	return os << ath.id << ". " << ath.name;
}