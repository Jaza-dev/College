#pragma once
#include "includes.h"
#include "Pair.h"
#include "Team.h"
#include "Errors.h"


static enum result { NOT_PLAYED, WIN_A, DRAW, WIN_B };
class Match {
private:
	Pair<Team> teams;//tim A - domacin, tim B - gost
	int pA = 0, pB = 0;
	result res;
public:
	Match(Team* team1, Team* team2);
	Pair<Team>& getTeamPair();
	void playMatch();
	bool isMatchPlayed();
	Pair<int>* getPointPair();
	friend ostream& operator<<(ostream& os, const Match& m);
};

