#include "User.h"

User::User(string n, string e): name(n), emailAddress(e) { }

string& User::getName() {
	return this->name;
}

string& User::getEmailAddress() {
	return this->emailAddress;
}

ostream& operator<<(ostream& os, const User& user) {
	return os << "(" << user.name << ") " << user.emailAddress;
}