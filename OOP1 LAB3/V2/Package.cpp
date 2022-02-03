#include "Package.h"

int Package::generatedId = 1;

void Package::copy(const Package& p) {
	for (int i = 0; i < operators.size(); i++) {
		operators += operators[i]->vCopy();
	}
	details.daysForDelivery = p.details.daysForDelivery;
	details.packagePrice = p.details.packagePrice;
	item = new Item(p.item->getName(), p.item->getBarCode(), p.item->getPurPrice());
}

void Package::move(Package& p) {
	id = p.id;
	for (int i = 0; i < operators.size(); i++) {
		operators += p.operators[i];
		p.operators[i] = nullptr;
	}
	details.daysForDelivery = p.details.daysForDelivery;
	details.packagePrice = p.details.packagePrice;
	item = p.item;
	p.item = nullptr;
	p.details.daysForDelivery = 0;
	p.details.packagePrice = 0;
}

void Package::del() {
	delete item;
	for (int i = 0; i < operators.size(); i++) {
		delete operators[i];
	};
}

Package::Package(Item* itm): item(new Item(*itm)) {
	id = generatedId++;
}

Package::Package(const Package& p) {
	copy(p);
}

Package::Package(Package&& p) {
	move(p);
}

Package& Package::operator=(const Package& p) {
	if (this != &p) {
		del();
		copy(p);
	}
	return *this;
}

Package& Package::operator=(Package&& p) {
	if (this != &p) {
		del();
		move(p);
	}
	return *this;
}

Package& Package::operator+=(Operator* op) {
	if (details.packagePrice || details.daysForDelivery) throw EAlreadyCountedDetials();
	operators += op->vCopy();
	return *this;
}

void Package::countDetailsForPackage() {
	details.daysForDelivery = 0;
	details.packagePrice = 0;
	for (int i = 0; i < operators.size(); i++) {
		operators[i]->countDetails(this);
	}
}

Package::~Package() {
	del();
}

Details& Package::getPackageDetails() {
	if (!details.packagePrice || !details.daysForDelivery) throw EPriceOrDaysNotCounted();
	return details;
}

Item* Package::getItem() {
	return item;
}

int Package::getId() {
	return id;
}

ostream& operator<<(ostream& os, const Package& p) {
	return os << "Posiljka[" << p.id << ", " << p.item->getName() << "]";
}
