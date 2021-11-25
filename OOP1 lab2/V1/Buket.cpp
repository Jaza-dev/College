#include "Buket.h"
void Buket::obrisi() {
	NodeC* curr = cvetovi, * sled = nullptr;
	while (curr != nullptr) {
		sled = curr->sled;
		delete curr;
		curr = sled;
	}
	cvetovi = nullptr;
}
void Buket::kopiraj(const Buket& buket) {
	brCvetova = buket.brCvetova;
	NodeC* curr = buket.cvetovi, * prev = nullptr, * newNode;
	while (curr != nullptr) {
		newNode = new NodeC(curr->cvet);
		if (cvetovi == nullptr) {
			cvetovi = newNode;
		}
		else {
			prev->sled = newNode;
		}
		prev = newNode;
		curr = curr->sled;
	}
}
void Buket::premesti(Buket& buket) {
	brCvetova = buket.brCvetova;
	cvetovi = buket.cvetovi;
	buket.cvetovi = nullptr;
}
Buket::~Buket() {
	obrisi();
}
Buket::Buket(const Buket& buket) {
	kopiraj(buket);
}
Buket::Buket(Buket&& buket) {
	premesti(buket);
}
Buket& Buket::operator=(const Buket& buket) {
	if (this != &buket) {
		obrisi();
		kopiraj(buket);
	}
	return *this;
}
Buket& Buket::operator=(Buket&& buket) {
	if (this != &buket) {
		obrisi();
		premesti(buket);
	}
	return *this;
}
void Buket::dodajCvet(Cvet& c) {
	NodeC* node = new NodeC(&c);
	if (cvetovi == nullptr) {
		cvetovi = node;
		lstCvetovi = node;
		brCvetova++;
		return;
	}
	lstCvetovi->sled = node;
	lstCvetovi = node;
	brCvetova++;
}
int Buket::nabCena() const{
	NodeC* curr = cvetovi;
	int cena = 0;
	while (curr != nullptr) {
		cena += curr->cvet->getNcena();
		curr = curr->sled;
	}
	return cena;
}
int Buket::prodCena() const {
	NodeC* curr = cvetovi;
	int cena = 0;
	while (curr != nullptr) {
		cena += curr->cvet->getPcena();
		curr = curr->sled;
	}
	return cena;
}
int Buket::zarada() const {
	NodeC* curr = cvetovi;
	int zarada = 0;
	while (curr != nullptr) {
		zarada += curr->cvet->zarada();
		curr = curr->sled;
	}
	return zarada;
}
bool Buket::operator>(Buket& b) const {
	return this->prodCena() > b.prodCena();
}

