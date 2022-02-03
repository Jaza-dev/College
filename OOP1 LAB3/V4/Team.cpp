#include "Team.h"

void Team::copy(const Team& t) {
    teamName = t.teamName;
    maxNumberOfPlayers = t.maxNumberOfPlayers;
    currentSize = t.currentSize;
    players = new Player * [maxNumberOfPlayers];
    for (int i = 0; i < maxNumberOfPlayers; i++) {
        if (t.players[i] != nullptr)
            players[i] = new Player(*t.players[i]);
        else players[i] = nullptr;
    }
}

void Team::move(Team& t) {
    teamName = t.teamName;
    maxNumberOfPlayers = t.maxNumberOfPlayers;
    currentSize = t.currentSize;
    players = t.players;
    t.teamName = "";
    t.maxNumberOfPlayers = t.currentSize = 0;
    t.players = nullptr;
}

void Team::del() {
    for (int i = 0; i < maxNumberOfPlayers; i++) {
        delete players[i];
    }
    delete players;
    teamName = "";
    maxNumberOfPlayers = currentSize = 0;
    players = nullptr;
}

void Team::print(ostream& os) const {
    os << teamName << "[";
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

Team* Team::vCopy() {
    return new Team(*this);
}

Team::Team(string tn, int mp) : teamName(tn), maxNumberOfPlayers(mp), players(new Player* [mp]) {
    for (int i = 0; i < maxNumberOfPlayers; i++) {
        players[i] = nullptr;
    }
}

Team::Team(const Team& t) {
    copy(t);
}

Team::Team(Team&& t) {
    move(t);
}

Team& Team::operator=(const Team& t) {
    if (this != &t) {
        del();
        copy(t);
    }
    return *this;
}

Team& Team::operator=(Team&& t) {
    if (this != &t) {
        del();
        move(t);
    }
    return *this;
}

Team::~Team() {
    del();
}

Team& Team::addPlayer(int i, Player* p) {
    if (i < 0 || i >= maxNumberOfPlayers) return *this;
    players[i] = new Player(*p);
    currentSize++;
    return *this;
}

int Team::getCurrentSize() const {
    return this->currentSize;
}

Player* Team::operator[](int i) {
    if (i < 0 || i >= maxNumberOfPlayers) return nullptr;
    return players[i];
}

double Team::teamValue() {
    double value = 0;
    for (int i = 0; i < maxNumberOfPlayers; i++) {
        if(players[i] != nullptr)
            value += players[i]->getValue();
    }
    return (value * 1.0) / currentSize;
}

bool Team::operator==(const Team& t2) {
    if (teamName != t2.teamName || maxNumberOfPlayers != t2.maxNumberOfPlayers || currentSize != t2.currentSize) return false;
    for (int i = 0; i < maxNumberOfPlayers; i++) {
        if (players[i] != nullptr && t2.players[i] != nullptr) {
            if (!(*players[i] == *t2.players[i])) return false;
        }
        else {
            if (players[i] != t2.players[i]) return false;
        }
    }
    return true;
}

ostream& operator<<(ostream& os, const Team& t) {
    t.print(os);
    return os;
}
