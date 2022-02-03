#ifndef _errors_h_
#define _errors_h_
#include "includes.h"

class ENoData : public exception {
	friend ostream& operator<< (ostream& os, const ENoData& error) {
		return os << "GRESKA: Na zadatoj poziciji ne postoji podatak!";
	}
};

class EAlreadyInList : public exception {
	friend ostream& operator<< (ostream& os, const EAlreadyInList& error) {
		return os << "GRESKA: Tacka sa tim koordinatama vec postoji u listi tacaka!";
	}
};

#endif // !_errors_h_

