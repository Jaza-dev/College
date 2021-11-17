#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

constexpr auto LEN = 10000;;

void print4(bool i[4]) { //ispis 4bitne reci
	cout << i[0] << i[1] << i[2] << i[3];
}
void print7(bool i[7]) { //ispis 7bitne reci
	cout << i[0] << i[1] << i[2] << i[3] << i[4] << i[5] << i[6];
}

void generisiRec(bool v[4], bool G[4][7], bool kod[7] = nullptr) { //funkcija pravi od 4bitne reci - 7bitnu rec
	//v je 4bitni broj, G matrica, kod je generisana rec
	bool i[4], bit; //i ce biti vektor u kome cuvam bitove pre xorovanja (a nakon mnozenja) te kolone , u t cuvam poslednji bit
	for (int j = 0; j <= 6; j++) {
		for (int p = 0; p < 4; p++) {
			i[p] = v[p] & G[p][j];
		}
		bit = i[0] ^ i[1] ^ i[2] ^ i[3]; //xor cele kolone pomnozene sa i i ispis
		if(kod != nullptr) kod[j] = bit;
		cout << bit; 
	}
}
void regenerisiRec(bool i[7], bool G[4][7], bool dest[4]) { //na osnovu 7bitne reci dobijamo poslatu rec 4bitnu
	cout << (dest[3] = ((G[0][6] & i[6]) ^ (G[1][6] & i[6]) ^ (G[2][6] & i[6]) ^ (G[3][6] & i[6])));
	cout << (dest[2] = ((G[0][5] & i[5]) ^ (G[1][5] & i[5]) ^ (G[2][5] & i[5]) ^ (G[3][5] & i[5])));
	cout << (dest[1] = ((G[0][4] & i[4]) ^ (G[1][4] & i[4]) ^ (G[2][4] & i[4]) ^ (G[3][4] & i[4])));
	cout << (dest[0] = ((G[0][2] & i[2]) ^ (G[1][2] & i[2]) ^ (G[2][2] & i[2]) ^ (G[3][2] & i[2])));
}

void generisiI(bool I[LEN][4]) { //generisanje nasmuicne 4bitne reci
	for (int i = 0; i < LEN; i++) {
		I[i][0] = rand() % 2;
		I[i][1] = rand() % 2;
		I[i][2] = rand() % 2;
		I[i][3] = rand() % 2;
	}
}
int main() {
	srand((unsigned int)time(nullptr));
	cout << "****************ZADATAK 1****************" << endl;
	//G je generisuca matrica
	bool G[4][7] = { {true,true,true,false,false,false,false},{true,false,false,true,true,false,false}
	,{false,true,false,true,false,true,false}, {true,true,false,true,false,false,true} };
	//v je i vektor [0000 - 1111] od kog se generise 7bitni kod
	bool v[16][4] = { {false,false,false,false} , {false,false,false,true},{false,false,true,false},{false,false,true,true},
	{false,true,false,false},{false,true,false,true},{false,true,true,false},{false,true,true,true},{true,false,false,false},
	{true,false,false,true},{true,false,true,false},{true,false,true,true},{true,true,false,false},{true,true,false,true},
	{true,true,true,false},{true,true,true,true} }; 
	//generisu se 2^4 7bitnih reci
	for (int i = 0; i < pow(2, 4); i++) {
		cout << v[i][0] << v[i][1] << v[i][2] << v[i][3] << "-> ";
		generisiRec(v[i], G);
		cout << endl;
	}
	/*
		a) Parametri: (7,4)
		b)
			Kodna rec 1: 0000000, d=0
			Kodna rec 2: 1101001, d=4
			Kodna rec 3: 0101010, d=3
			Kodna rec 4: 1000011, d=3
			Kodna rec 5: 1001100, d=3
			Kodna rec 6: 0100101, d=3
			Kodna rec 7: 1100110, d=4
			Kodna rec 8: 0001111, d=4
			Kodna rec 9: 1110000, d=3
			Kodna rec 10: 0011001, d=3
			Kodna rec 11: 1011010, d=4
			Kodna rec 12: 0110011, d=4
			Kodna rec 13: 0111100, d=4
			Kodna rec 14: 1010101, d=4
			Kodna rec 15: 0010110, d=3
			Kodna rec 16: 1111111, d=7
			
			1 kodna rec sa d=0
			7 kodnih reci sa d=3
			7 kodnih reci sa d=4
			1 kodna rec sa d=7
		c)
			d min = 3 -> d >= 2ec + 1 -> Posto je d = 3 -> ec = 1 sto znaci da kod moze da ispravi 1 gresku
			ako ec stavimo da je 0 -> d >= ec + ed + 1 -> moze da detektuje 2 greske, ako ostavimo ec = 1 moze max 1 da detektuje
	*/
	cout << "****************ZADATAK 2****************" << endl;
	cout << "Pritisnuti neko dugme za drugi zadatak" << endl; 
	system("pause");
	bool I[LEN][4]; //nasumicno dobijenih 10000 reci
	bool kodovi[LEN][7]; //7bitne reci dobijene od nasumicnih 4bitnih reci
	generisiI(I); // funkcija generise 10000 random 4bitnih reci 
	for (int j = 0; j < LEN; j++) {
		print4(I[j]);
		cout << "--->";
		generisiRec(I[j], G, kodovi[j]); //generisu se 7bitne reci pomocu generisuce matrice
		cout << "       ";
		if (j % 8 == 0) cout << endl;
	}
	system("pause");
	cout << "*************GRESKE U KANALU****************" << endl;
	int l, pomeraj = 0; //l koliko uzastopnih pozicija je greska, pomeraj od koje pozicije krece greska
	int i, j, brojac = 0;
	cout << "Od koje pozicije: ";
	cin >> pomeraj;
	cout << "L: ";
	cin >> l;
	if (l > 0) {
		for (i = 0; i < 7; i++) {
			for (j = (!i ? pomeraj : j - LEN); j < LEN; j += 1) {
				brojac++;
				kodovi[j][i] = kodovi[j][i] ^ true;
				if (brojac == l) {
					brojac = 0;
					j += 100;
				}
			}
		}
	}
	for (int j = 0; j < LEN; j++) {
		print7(kodovi[j]);
		cout << "       ";
		if (j % 8 == 0) cout << endl;
	}
	//Deinterlivin i dekodovanje
	cout << "***********DEINTERLIVING**********" << endl;
	//(7,4)
	bool Irez[LEN][4]; //upisuju se ISPRAVLJENE reci
	for (int j = 0; j < LEN; j++) {
		int S = (kodovi[j][0] ^ kodovi[j][2] ^ kodovi[j][4] ^ kodovi[j][6]) * 1 +
			(kodovi[j][1] ^ kodovi[j][2] ^ kodovi[j][5] ^ kodovi[j][6]) * 2 +
			(kodovi[j][3] ^ kodovi[j][4] ^ kodovi[j][5] ^ kodovi[j][6])* 4-1; //racunanje sindroma
		cout << "Primljen kod: ";
		print7(kodovi[j]); //primljeni kod sa greskom
		cout << " | Dekodovani: "; 
		if (S != -1) { kodovi[j][S] = (kodovi[j][S] ? false : true); } //ispravlja se greska ako je doslo do greske (-1 je jer bitovi krecu od 0 ne od 1)
		regenerisiRec(kodovi[j], G , Irez[j]);
		cout << "       ";
		if (j % 4 == 0) cout << endl;
	}

	cout << endl << "*******GRESKE********" << endl;
	
	int brGresaka = 0;
	for (int i = 0; i < LEN; i++) {
		if (I[i][0] != Irez[i][0] || I[i][1] != Irez[i][1] || I[i][2] != Irez[i][2] || I[i][3] != Irez[i][3]) brGresaka++;
	}
	cout << "Broj ne ispravljenih gresaka: " << brGresaka << endl;
	double procenat = ((double)brGresaka / LEN) * 100;
	cout << "Primeljen je kod sa " << procenat << "% greske";
	/*
		Pe = (7 3) p^3(1-p)^4 + (7 5)p^5(1-p)2 + (7 7)p^7 = 3.5*10^-8
	*/
}