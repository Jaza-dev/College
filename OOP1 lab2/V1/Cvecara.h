#pragma once
#include "Buket.h"
struct NodeB {
	Buket* buket;
	NodeB* sled = nullptr;
	NodeB(Buket* b) {
		buket = b;
	}
	~NodeB() {
		buket->~Buket();
	}
};
class Cvecara {
	NodeB* buketi = nullptr;
	int zarada = 1000, kolicina = 0;
	void obrisi();
	void kopiraj(const Cvecara& cvecara);
	void premesti(Cvecara& cvecara);
public:
	Cvecara() = default;
	Cvecara(const Cvecara& cvecara);
	Cvecara(Cvecara&& cvecara);
	~Cvecara();
	Cvecara& operator=(const Cvecara& cvecara);
	Cvecara& operator=(Cvecara&& cvecara);
	void dodajBuket(Buket* b);
	void prodajBuket(int poz);
	friend ostream& operator<<(ostream& os, const Cvecara& cv);
};