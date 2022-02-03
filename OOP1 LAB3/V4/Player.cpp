#include "Player.h"

int Player::incValue(double percent) {
    return value += ceil(value*percent);
}


bool Player::operator==(const Player& p2) const{
    return (name == p2.name && value == p2.value);
}

ostream& operator<<(ostream& os, const Player& p) {
    return os << p.name << '#' << p.value;
}
