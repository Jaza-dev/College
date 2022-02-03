#include "PrivilegedTeam.h"

void PrivilegedTeam::print(ostream& os) const {
    os << teamName << "(" << minPlayerValue << ")[";
    int temp = currentSize;
    for (int i = 0; i < maxNumberOfPlayers; i++) {
        if (players[i] != nullptr) {
            os << *players[i];
            temp--;
            if (temp) os << ',';
        }
    }
    os << "]";
}

PrivilegedTeam* PrivilegedTeam::vCopy() {
    return new PrivilegedTeam(*this);
}

PrivilegedTeam::PrivilegedTeam(string tn, int mp, int minPV):Team::Team(tn, mp), minPlayerValue(minPV) { }

PrivilegedTeam& PrivilegedTeam::addPlayer(int i, Player* p) {
    if (p->getValue() < minPlayerValue) throw ELowValueOfPlayer();
    else Team::addPlayer(i, p);
    return *this;
}

ostream& operator<<(ostream& os, const PrivilegedTeam& pt) {
    pt.print(os);
    return os;
}
