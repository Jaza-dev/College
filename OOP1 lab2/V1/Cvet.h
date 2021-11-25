#pragma once
#include <string>
#include <iostream>
using namespace std;

class Cvet {
private:
	string naziv;
	int ncena, pcena;
public:
	Cvet(string naziv, int ncena, int pcena);
	string& getNaziv();
	int getNcena() const;
	int getPcena() const;
	int zarada() const;
	bool operator==(const Cvet& c) const;
	friend ostream& operator<<(ostream& os, const Cvet& c);
};