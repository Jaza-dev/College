#include "Cvet.h"

Cvet::Cvet(string naziv, int ncena, int pcena) {
	this->naziv = naziv;
	this->ncena = ncena;
	this->pcena = pcena;
}

string& Cvet::getNaziv(){
	return naziv;
}

int Cvet::getNcena() const {
	return ncena;
}

int Cvet::getPcena() const {
	return pcena;
}

int Cvet::zarada() const {
	return pcena - ncena;
}

bool Cvet::operator==(const Cvet& c) const {
	return naziv == c.naziv;
}
