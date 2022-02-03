#ifndef _errors_h_
#define _errors_h_
#include "includes.h"

class ENoCurrElement {
	friend ostream& operator<<(ostream& os, const ENoCurrElement& error) {
		os << "GRESKA: Nema tekuci element!";
		return os;
	}
};

class EAlrdySentMessage {
	friend ostream& operator<<(ostream& os, const EAlrdySentMessage& error) {
		os << "GRESKA: Poruka je vec poslata!";
		return os;
	}
};

#endif // !_errors_h_

