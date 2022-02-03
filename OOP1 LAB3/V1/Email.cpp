#include "Email.h"

void Email::copy(const Email& email) {
	this->title = email.title;
	this->sender = new User(email.sender->getName(), email.sender->getEmailAddress());
	this->receiver = new User(email.receiver->getName(), email.receiver->getEmailAddress());
	this->currentState = email.currentState;
}

void Email::move(Email& email) {
	this->title = email.title;
	this->sender = email.sender;
	this->receiver = email.receiver;
	this->currentState = email.currentState;
	email.sender = nullptr;
	email.receiver = nullptr;
}

void Email::del() {
	delete this->sender;
	delete this->receiver;
	this->sender = nullptr;
	this->receiver = nullptr;
}

Email* Email::vCopy() {
	return new Email(sender, receiver, title);
}

void Email::print(ostream& os) const{
	os << title << endl << *sender << endl << *receiver;
}

Email::Email(User* s, User* r, string t)
	:sender(new User(s->getName(), s->getEmailAddress())), receiver(new User(r->getName(), r->getEmailAddress())), title(t)
{
	currentState = DRAFT;
}

Email::Email(const Email& email) {
	copy(email);
}

Email::Email(Email&& email) {
	move(email);
}

Email& Email::operator=(const Email& email) {
	if (this != &email) {
		del();
		copy(email);
	}
	return *this;
}

Email& Email::operator=(Email&& email) {
	if (this != &email) {
		del();
		move(email);
	}
	return *this;
}

Email::~Email() {
	del();
}

string& Email::getTitle() {
	return this->title;
}

User* Email::getSender() {
	return this->sender;
}

User* Email::getReceiver() {
	return this->receiver;
}

Email::state Email::getState() {
	return this->currentState;
}

void Email::sendEmail() { }

ostream& operator<<(ostream& os, const Email& email) {
	email.print(os);
	return os;
}
