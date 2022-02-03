#include "includes.h"
#include "Point.h"
#include "Road.h"
#include "Vehicle.h"
#include "NormalVehicle.h"
#include "Errors.h"

int main() {
	try {
		Point p1(1, 1);
		Point p2(2, 2);
		Point p3(3, 3);
		Point p4(4, 4);
		/*cout << range(p1, p2) << endl;
		cout << p1 << endl;
		cout << p2 << endl;*/
		Road r;
		r += &p1;
		r += &p2;
		r += &p3;
		r += &p4;
		Road r2 = r;
		/*cout << r2.length() << endl;
		cout << r << endl;
		cout << r2 << endl;*/
		Vehicle v("BMW");
		cout << v << endl;
		cout << v.transportPrice(r) << endl;
		NormalVehicle v1("Mercedes");
		cout << v1 << endl;
		cout << v1.transportPrice(r) << endl;
	}
	catch (ENoData err) {
		cout << err;
	}
	catch (EAlreadyInList err) {
		cout << err;
	}
	

	return 0;
}