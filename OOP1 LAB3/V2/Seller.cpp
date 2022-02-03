#include "Seller.h"

void Seller::copy(const Seller& s) {
	this->name = s.name;
	for (int i = 0; i < s.catalog.size(); i++) {
		catalog += new Triplet(s.catalog[i]->item, s.catalog[i]->margin, s.catalog[i]->daysForGetting);
	}
}

void Seller::move(Seller& s) {
	this->name = s.name;
	for (int i = 0; i < s.catalog.size(); i++) {
		catalog += s.catalog[i];
		s.catalog[i] = nullptr;
	}
}

void Seller::del() {
	for (int i = catalog.size() - 1; i >= 0 ; i--) {
		delete catalog[i];
		catalog[i] = nullptr;
	}
}

Triplet* Seller::findItem(string nameOfItem) const {
	for (int i = 0; i < catalog.size(); i++) {
		if (catalog[i]->item.getName() == nameOfItem) {
			return catalog[i];
		}
	}
	return nullptr;
}

Seller::Seller(string n) {
	this->name = n;
}

Seller::Seller(const Seller& s) {
	copy(s);
}

Seller::Seller(Seller&& s) {
	move(s);
}

Seller& Seller::operator=(const Seller& s) {
	if (this != &s) {
		del();
		copy(s);
	}
	return *this;
}

Seller& Seller::operator=(Seller&& s) {
	if (this != &s) {
		del();
		move(s);
	}
	return *this;
}

Seller::~Seller() {
	del();
}

double Seller::price(string nameOfItem) const {
	Triplet* temp = findItem(nameOfItem);
	if (temp) {
		return temp->item.getPurPrice() * temp->margin;
	}
	return 0;
}

Seller& Seller::addItem(Item& item, double margin, int daysForGetting) {
	catalog += new Triplet(item, margin, daysForGetting);
	return *this;
}

string Seller::getName() {
	return name;
}

Seller* Seller::vCopy() {
	Seller* newSeller = new Seller(this->name);
	Triplet* tempTriplet = nullptr; //da ne bi tri puta radio catalog[i]
	for (int i = 0; i < catalog.size(); i++) {
		tempTriplet = catalog[i];
		newSeller->addItem(tempTriplet->item, tempTriplet->margin, tempTriplet->daysForGetting);
	}
	return newSeller;
}

void Seller::countDetails(Package* p) {
	Triplet* tr = findItem(p->item->getName());
	if(tr)
		p->details.daysForDelivery += tr->daysForGetting;
	p->details.packagePrice += price(p->item->getName());
}
