#include "Cvecara.h"
ostream& operator<<(ostream& os, const Cvet& c){
	return os << c.naziv;
}
ostream& operator<<(ostream& os, const Buket& b){
	string* unikati = new string[b.brCvetova];
	int brUnikata = 0, i;

	NodeC* curr = b.cvetovi;
	if (curr != nullptr) {
		os << "(";
		while (curr != nullptr) {
			for (i = 0; i < brUnikata; i++) {
				if (curr->cvet->getNaziv() == unikati[i])
					break;	
			}
			if (i == brUnikata) {
				if (i != 0) os << ",";
				os << * (curr->cvet);
				unikati[brUnikata] = curr->cvet->getNaziv();
				brUnikata++;
			}
			curr = curr->sled;
		}
		return (os << ")" << b.prodCena() << "RSD");
	}
	else {
		return (os << "()0RSD");
	}
}

ostream& operator<<(ostream& os, const Cvecara& cv) {
	NodeB* curr = cv.buketi;
	os << "zarada=" << cv.zarada << "RSD" << endl;
	while (curr != nullptr) {
		os << *curr->buket << endl;
		curr = curr->sled;
	}
	return os;
}

int main() {
	Cvet c1{ "Ljubicica1", 50, 100 };
	Cvet c2{ "Ljubicica2", 50, 100 };
	Cvet c3{ "Ljubicica3", 60, 120 };
	Cvet c4{ "Nana1", 30, 120 };
	Cvet c5{ "Nana2", 45, 105 };
	Cvet c6{ "Nana3", 84, 125 };
	Cvet c7{ "Lotus1", 98, 133 };
	Cvet c8{ "Lotus2", 46, 95 };
	Cvet c9{ "Lotus3", 90, 120 };
	Cvet c10{ "Nar1", 100, 150 };
	Cvet c11{ "Nar2", 80, 195 };
	Cvet c12{ "Nar3", 90, 170 };
	Cvet c13{ "Nar3", 100, 50 };
	Cvet c14{ "Nar3", 50, 500 };
	Buket buket1, buket2, buket3, buket4;
	buket1.dodajCvet(c1);
	buket1.dodajCvet(c2);
	buket1.dodajCvet(c3);
	cout << buket1 << endl;
	buket2.dodajCvet(c14);
	buket2.dodajCvet(c14);
	buket2.dodajCvet(c14);
	cout << buket2 << endl;
	buket3.dodajCvet(c14);
	buket3.dodajCvet(c8);
	buket3.dodajCvet(c9);
	cout << buket3 << endl;
	buket4.dodajCvet(c14);
	buket4.dodajCvet(c14);
	buket4.dodajCvet(c14);
	buket4.dodajCvet(c14);
	buket4.dodajCvet(c14);
	cout << buket4 << endl;
	Cvecara cvecara, cvecara3;
	cvecara.dodajBuket(&buket4);
	cvecara.dodajBuket(&buket1);
	cvecara.dodajBuket(&buket2);
	cvecara.dodajBuket(&buket3);
	cout << "----------------------------------" << endl;
	Cvecara cvecara2 = cvecara;
	cout << cvecara2;
	cout << "----------------------------------" << endl;
	cvecara3 = move(cvecara2);
	cout << cvecara3;
	cout << "----------------------------------" << endl;
	cout << cvecara;
	cvecara.prodajBuket(3);
	cout << cvecara;
	cvecara.prodajBuket(2);
	cout << cvecara;
	cvecara.prodajBuket(1);
	cout << cvecara;
	cvecara.prodajBuket(0);
	cout << cvecara;
	cout << "----------------------------------" << endl;
	cout << cvecara2;
	cvecara2.prodajBuket(0);
	cvecara2.prodajBuket(0);
	cout << cvecara3;
}