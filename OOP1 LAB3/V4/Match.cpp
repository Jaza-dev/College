#include "Match.h"

Match::Match(Team* team1, Team* team2):teams(Pair<Team>(team1, team2)), res(NOT_PLAYED) { }

Pair<Team>& Match::getTeamPair() {
	return teams;
}

void Match::playMatch() {
	int val1 = teams.getPointer1()->teamValue(), val2 = teams.getPointer2()->teamValue();
	if (val1 > val2) res = WIN_A;
	else if (val1 < val2) res = WIN_B;
	else res = DRAW;
	if (res == DRAW) {
		pA++;
		pB++;
	}
	else if (res == WIN_A) {
		for(int i = 0, j = 0; j < teams.getPointer1()->getCurrentSize(); i++){
			if ((*teams.getPointer1())[j] != nullptr) {
				(*teams.getPointer1())[j]->incValue(0.1);
				j++;
			}
		}
		for (int i = 0, j = 0; j < teams.getPointer2()->getCurrentSize(); i++) {
			if ((*teams.getPointer2())[j] != nullptr) {
				(*teams.getPointer2())[j]->incValue(-0.1);
				j++;
			}
		}
		pA += 3;
	}
	else if (res == WIN_B) {
		for (int i = 0, j = 0; j < teams.getPointer1()->getCurrentSize(); i++) {
			if ((*teams.getPointer1())[j] != nullptr) {
				((*teams.getPointer1())[j])->incValue(-0.1);
				j++;
			}
		}
		for (int i = 0, j = 0; j < teams.getPointer2()->getCurrentSize(); i++) {
			if ((*teams.getPointer2())[j] != nullptr) {
				(*teams.getPointer2())[j]->incValue(0.1);
				j++;
			}
		}
		pB += 3;
	}
}

bool Match::isMatchPlayed() {
	return res != NOT_PLAYED;
}

Pair<int>* Match::getPointPair() {
	if (res == NOT_PLAYED) throw EMatchNotPlayed();
	return new Pair<int>(&pA, &pB);
}

ostream& operator<<(ostream& os, const Match& m) {
	os << m.teams;
	if (m.res == NOT_PLAYED) return os;
	if (m.res == DRAW) return os << "NERESENO";
	else if (m.res == WIN_A) return os << "POBEDA_DOMACIN";
	else return os << "POBEDA_GOST";
}
