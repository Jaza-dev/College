#pragma once
#include "Cvet.h"
struct NodeC {
	Cvet* cvet;
	NodeC* sled = nullptr;
	NodeC(Cvet* c) {
		cvet = c;
	}
};
class Buket {
private:
	int brCvetova = 0;
	NodeC* cvetovi = nullptr, *lstCvetovi = nullptr;
	void obrisi();
	void kopiraj(const Buket& buket);
	void premesti(Buket& buket);
public:
	Buket() = default;
	~Buket();
	Buket(const Buket& buket);
	Buket(Buket&& buket);
	Buket& operator=(const Buket& buket);
	Buket& operator=(Buket&& buket);
	void dodajCvet(Cvet& c);
	int nabCena() const;
	int prodCena() const;
	int zarada() const;
	bool operator>(Buket& b) const;
	friend ostream& operator<<(ostream& os, const Buket& b);
};