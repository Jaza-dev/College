#pragma once
#include "includes.h"
#include "Operator.h"
#include "List.h"
#include "Package.h"
#include "Item.h"

struct Triplet {
	Item item;
	double margin;
	int daysForGetting;
	Triplet(Item i, double m, int d) :item(i) {
		margin = m;
		daysForGetting = d;
	}
};
class Seller: public Operator {
private:
	string name;
	List<Triplet*> catalog;
	void copy(const Seller& s);
	void move(Seller& s);
	void del();
	Triplet* findItem(string nameOfItem) const; 
public:
	Seller(string n);
	Seller(const Seller& s);
	Seller(Seller&& s);
	Seller& operator=(const Seller& s);
	Seller& operator=(Seller&& s);
	~Seller() override;
	double price(string nameOfItem) const;
	Seller& addItem(Item& item, double margin, int days);
	string getName();
	Seller* vCopy() override;
	void countDetails(Package* p) override;
};

