#pragma once
#include "includes.h"

class User {
private:
	string name, emailAddress;
public:
	User(string n, string e);
	string& getName();
	string& getEmailAddress();
	User(const User&) = delete;
	User& operator=(const User&) = delete;
	friend ostream& operator<<(ostream& os, const User& user);
};

