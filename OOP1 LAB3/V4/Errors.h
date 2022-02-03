#pragma once
#include "includes.h"

class ELowValueOfPlayer {
	friend ostream& operator<<(ostream& os, const ELowValueOfPlayer& error) {
		return os << "GRESKA: Vrednost igraca je manja od minimalne dozvoljene!" << endl;
	}
};

class EMatchNotPlayed {
	friend ostream& operator<<(ostream& os, const EMatchNotPlayed& error) {
		return os << "GRESKA: Mec nije odigran!" << endl;
	}
};