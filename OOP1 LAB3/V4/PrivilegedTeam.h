#pragma once
#include "Team.h"
#include "Errors.h"

class PrivilegedTeam: public Team {
private:
	int minPlayerValue;
protected:
	void print(ostream& os) const override;
public:
	PrivilegedTeam(string tn, int mp, int minPV);
	PrivilegedTeam& addPlayer(int i, Player* p) override;
	PrivilegedTeam* vCopy() override;
	friend ostream& operator<<(ostream& os, const PrivilegedTeam& pt);
};

