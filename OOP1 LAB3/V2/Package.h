#pragma once
#include "includes.h"
#include "Item.h"
#include "List.h"
#include "Operator.h"
#include "Seller.h"

struct Details {
	int daysForDelivery = 0;
	double packagePrice = 0;
};
class Package {
private:
	static int generatedId;
	int id;
	Item* item;
	List<Operator*> operators;
	Details details;
	void copy(const Package& p);
	void move(Package& p);
	void del();
	friend class Operator;
	friend class Seller;
public:
	
	Package(Item* itm);
	Package(const Package& p);
	Package(Package&& p);
	Package& operator=(const Package& p);
	Package& operator=(Package&& p);
	Package& operator+=(Operator* op);
	~Package();
	void countDetailsForPackage();
	Details& getPackageDetails();
	Item* getItem();
	int getId();
	friend ostream& operator<<(ostream& os, const Package& p);
};

