#include "Cvecara.h"

void Cvecara::obrisi() {
	NodeB* curr = buketi, * sled = nullptr;
	while (curr != nullptr) {
		sled = curr->sled;
		delete curr;
		curr = sled;
	}
	buketi = nullptr;
}

void Cvecara::kopiraj(const Cvecara& cvecara) {
	zarada = cvecara.zarada;
	kolicina = cvecara.kolicina;
	NodeB* curr = cvecara.buketi, * prev = nullptr, * newNode;
	Buket* newBuket = nullptr;
	while (curr != nullptr) {
		newBuket = new Buket(*curr->buket);
		newNode = new NodeB(newBuket);
		if (buketi == nullptr) {
			buketi = newNode;
		}
		else {
			prev->sled = newNode;
		}
		prev = newNode;
		curr = curr->sled;
	}
}

void Cvecara::premesti(Cvecara& cvecara) {
	zarada = cvecara.zarada;
	kolicina = cvecara.kolicina;
	buketi = cvecara.buketi;
	cvecara.buketi = nullptr;
}

Cvecara::Cvecara(const Cvecara& cvecara) {
	kopiraj(cvecara);
}

Cvecara::Cvecara(Cvecara&& cvecara) {
	premesti(cvecara);
}

Cvecara::~Cvecara() {
	obrisi();
}

Cvecara& Cvecara::operator=(const Cvecara& cvecara) {
	if (this != &cvecara) {
		obrisi();
		kopiraj(cvecara);
	}
	return *this;
}

Cvecara& Cvecara::operator=(Cvecara&& cvecara) {
	if (this != &cvecara) {
		obrisi();
		premesti(cvecara);
	}
	return *this;
}

void Cvecara::dodajBuket(Buket* b) {
	if((double)b->zarada() > 0.2*b->nabCena()){
		NodeB* newBuket = new NodeB(b);
		if (buketi == nullptr) {
			buketi = newBuket;
		}
		else {
			NodeB* curr = buketi, *prev = nullptr;
			while (curr != nullptr && curr->buket->prodCena() < newBuket->buket->prodCena()) {
				prev = curr;
				curr = curr->sled;
			}
			if (prev != nullptr) {
				prev->sled = newBuket;
				newBuket->sled = curr;
			}
			else {
				newBuket->sled = curr;
				buketi = newBuket;
			}
		}
		zarada -= newBuket->buket->nabCena();
		kolicina++;
	}
}

void Cvecara::prodajBuket(int poz) {
	if (poz >= kolicina) {
		cout << "Nema buketa na toj poziciji" << endl;
		return;
	}
	int i = 0;
	NodeB* curr = buketi, *prev = nullptr;
	while (curr != nullptr && i < poz) {
		prev = curr;
		curr = curr->sled;
		i++;
	}
	zarada += curr->buket->prodCena();
	if (prev != nullptr)
		prev->sled = curr->sled;
	else
		buketi = curr->sled;
	delete curr;
}
