#pragma once
#include "includes.h"
#include "Player.h"

class Team {
private:
	void copy(const Team& t);
	void move(Team& t);
	void del();
protected:
	string teamName;
	int maxNumberOfPlayers, currentSize = 0;
	Player** players;
	virtual void print(ostream& os) const;
public:
	Team(string tn, int mp);
	Team(const Team& t);
	Team(Team&& t);
	Team& operator=(const Team& t);
	Team& operator=(Team&& t);
	virtual ~Team();
	virtual Team* vCopy();
	virtual Team& addPlayer(int i, Player* p);
	int getCurrentSize() const;
	Player* operator[](int i);
	double teamValue();
	bool operator==(const Team& t2);
	friend ostream& operator<<(ostream& os, const Team& t);
};

