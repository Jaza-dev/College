#pragma once
#include "includes.h"
#include "User.h"

class Email {
public:
	static enum state { DRAFT, SENT, RECEIVED };
private:
	void copy(const Email& email);
	void move(Email& email);
	void del();
protected:
	string title;
	User* sender, * receiver;
	state currentState;
	virtual Email* vCopy();
	virtual void print(ostream& os) const;
public:
	Email(User* s, User* r, string t);
	Email(const Email& email);
	Email(Email&& email);
	Email& operator=(const Email& email);
	Email& operator=( Email&& email);
	virtual ~Email();
	string& getTitle();
	User* getSender();
	User* getReceiver();
	Email::state getState();
	virtual void sendEmail();
	friend ostream& operator<<(ostream& os, const Email& email);
};

