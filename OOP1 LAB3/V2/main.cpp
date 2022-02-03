#include "includes.h"
#include "List.h"
#include "Item.h"
#include "Operator.h"
#include "Seller.h"
#include "Package.h"
#include "Errors.h"

int main() {
	try {
		Item i1("Sok", 112342, 70.6);
		Item i2("Voda", 112341, 55.2);
		Item i3("Pecivo", 536258, 25.2);
		Item i4("Cips", 536288, 105.2);
		//cout << i1.getBarCode() << endl << i1.getName() << endl << i1.getPurPrice();
		//cout << (i3 == i4);
		Seller s1("Pera");
		Seller s2("Zika");
		Seller s3("Luka");
		s1.addItem(i1, 2.3, 6);
		s1.addItem(i2, 2.5, 5);
		s2.addItem(i2, 2.5, 9);
		s2.addItem(i3, 8.5, 8);
		s3.addItem(i2, 2.5, 9);
		s3.addItem(i4, 10, 6);
		Package p1(&i2);
		p1 += &s1;
		p1 += &s2;
		p1 += &s3;
		p1.countDetailsForPackage();
		cout << p1.getId() << endl;
		cout << p1.getPackageDetails().packagePrice << endl;
		cout << p1.getPackageDetails().daysForDelivery << endl;
		cout << p1 << endl;
	}
	catch (ENoData err) {
		cout << err;
	}
	catch (EPriceOrDaysNotCounted err) {
		cout << err;
	}
	catch (EAlreadyCountedDetials err) {
		cout << err;
	}
	
	return 0;
}