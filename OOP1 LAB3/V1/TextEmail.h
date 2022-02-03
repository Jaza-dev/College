#pragma once
#include "includes.h"
#include "Email.h"
#include "Errors.h"

class TextEmail: public Email {
private:
	string text;
protected:
	TextEmail* vCopy() override;
	void print(ostream& os) const override;
public:
	TextEmail(User* s, User* r, string t);
	TextEmail& setText(string t);
	friend ostream& operator<<(ostream& os, const TextEmail& te);
};

