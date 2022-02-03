#ifndef _errors_h_
#define _errors_h_
#include "includes.h"

class ENoData : public exception {
	friend ostream& operator<< (ostream& os, const ENoData& error) {
		return os << "GRESKA: Na zadatoj poziciji ne postoji podatak!";
	}
};

class EPriceOrDaysNotCounted : public exception {
	friend ostream& operator<< (ostream& os, const EPriceOrDaysNotCounted& error) {
		return os << "GRESKA: Dani ili cena jos uvek nisu izracunati!";
	}
};

class EAlreadyCountedDetials : public exception {
	friend ostream& operator<< (ostream& os, const EAlreadyCountedDetials& error) {
		return os << "GRESKA: Detalji posiljke su vec izracunti, nije dozovljeno naknadno dodavanje rukovaoca!";
	}
};

#endif // !_errors_h_

