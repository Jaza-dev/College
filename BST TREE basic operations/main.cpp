#define _CRT_SECURE_NO_WARNINGS
#include "node.h"
#include "tree.h"
#include <iostream>
#include <string>

using namespace std;

bool checkTree(Tree tree) {
	if (tree.getRoot()->getInfo() == "0" && tree.getRoot()->getKey() == "0")
		return false;
	return true;
}

Tree tree;
int main() {
	int problem, op;
	cout << "IZBOR ZADATKA 1 ili 2: ";
	cin >> problem;
	if (problem == 1) {
		cout << "Dobro dosli u zadatak 2!" << endl;
		string key, info;
		while (true) {
			cout << "Uneti redni broj zeljene operacije" << endl;
			cout << "(1) Formiranje stabla na osnovu zadatog skupa reci i njihovog prevoda" << endl;
			cout << "(2) Pretraga stabla na zadatu rec i dohvatanje prevoda" << endl;
			cout << "(3) Umetanje u stablo novog para reci" << endl;
			cout << "(4) Ispis sadrzaja stabla" << endl;
			cout << "(5) Brisanje zadatog kljuca" << endl;
			cout << "(6) Brisanje stabla iz memorije" << endl;
			cout << "(7) Pronaci sve prefikse" << endl;
			cout << "(0) KRAJ PROGRAMA" << endl;
			cout << "Zeljena operacija: ";
			cin >> op;
			Node* node; //isto zasto mora izvan switcha
			switch (op)
			{
			case 0:
				exit(0);
			case 1:
				if (!checkTree(tree)) {
					char subOp;
					cout << "(a) Citanje sa standardnog ulaza" << endl;
					cout << "(b) Citanje iz datoteke" << endl;
					cin >> subOp;
					if (subOp == 'a') {
						int n;
						cout << "DUZINA NIZA: ";
						cin >> n;

						tree = Tree(n);
						tree.printTree();
					}
					else {
						FILE* in = fopen("input.txt", "r");
						tree = Tree(in);
						fclose(in);
						tree.printTree();
					}
				}
				else {
					cout << "Stablo vec postoji u memoriji";
				}
				cout << endl << "-----------------------------" << endl; break;
			case 2:
				if (checkTree(tree)) {
					cout << "Rec koju trazite: ";
					cin >> key;
					node = tree.getNode(key);
					if (node != nullptr) {
						cout << "Prevod reci " << key << " : " << node->getInfo();
					}
					else {
						cout << "Rec " << key << " ne postoj u recniku";
					}
				}
				else
					cout << "Stablo nije formirano!";
				cout << endl << "-----------------------------" << endl; break;
			case 3:
				if (checkTree(tree)) {
					cout << "KLJUC: ";
					cin >> key;
					cout << "PREVOD: ";
					cin >> info;
					node = new Node(key, info);
					tree.addNode(node);
					tree.printTree();
				}
				else
					cout << "Stablo nije formirano!";
				cout << endl << "-----------------------------" << endl; break;
			case 4:
				if (checkTree(tree)) {
					cout << "STABLO:" << endl;
					tree.printTree();
				}
				else
					cout << "Stablo nije formirano!";
				cout << endl << "-----------------------------" << endl; break;
			case 5:
				if (checkTree(tree)) {
					cout << "Kljuc koji zelite da oberisete: ";
					cin >> key;
					if (tree.getNode(key) == tree.getRoot() &&
						tree.getRoot()->getLeft() == nullptr
						&& tree.getRoot()->getRight() == nullptr) {
						delete tree.getRoot();
						tree = Tree();
						cout << "Stablo je obrisano iz memorije" << endl;
					}
					else {
						tree.deleteNode(key);
						cout << "STABLO:" << endl;
						tree.printTree();
					}

				}
				else
					cout << "Stablo nije formirano!";
				cout << endl << "-----------------------------" << endl; break;
			case 6:
				if (checkTree(tree)) {
					tree.deleteTree();
					cout << "STABLO JE USPESNO OBRISANO";
					tree = Tree();
				}
				else
					cout << "Stablo nije formirano!";
				cout << endl << "-----------------------------" << endl; break;
			case 7:
				if (checkTree(tree)) {
					string prefix;
					cout << "Trazeni prefiks: ";
					cin >> prefix;
					tree.searchWithPrefix(prefix);
				}
				else
					cout << "Stablo nije formirano!";
				cout << endl << "-----------------------------" << endl; break;
			default:
				cout << "Nepravilan unos" << endl;
				exit(0);
			}
		}
	} else if (problem == 2) {
		cout << "Dobro dosli u zadatak 2!" << endl;
		double low, high, mid, err;
		int count;
		string answer;
		while (true) {
			count = 0;
			cout << "Donja granica opsega (realan ili ceo broj): ";
			cin >> low;
			cout << "Goranja granica opsega (realan ili ceo broj): ";
			cin >> high;
			cout << "Greska: ";
			cin >> err;
			cout << "Odgovarati na pitanja sa da ili ne" << endl;
			while (true) {
				cout << "Trenutan interval [" << low << "-" << high  << "]" << endl;
				cout << "Da li se broj nalazi u prvih 20% inervala -> [" << low << "-" << low + (high-low) * 0.2 << "]" << endl;
				cin >> answer;
				if (answer == "da") {
					high = low + (high - low) * 0.2;
					count++;
					break;
				}
				else {
					low = low + (high - low) * 0.2;
					count++;
				}
				cout << "Trenutan interval [" << low << "-" << high << "]" << endl;
				cout << "Da li se broj nalazi u poslednih 20% inervala -> [" << high - (high-low)*0.2 << "-" << high << "]" << endl;
				cin >> answer;
				if (answer == "da") {
					low = high - (high - low) * 0.2;
					count++;
					break;
				}else{
					high = high - (high - low) * 0.2;
					count++;
				}
				cout << "Trenutan interval [" << low << "-" << high << "]" << endl;
				cout << "Da li se broj nalazi u prvih 40% inervala -> [" << low << "-" << low + (high - low) * 0.4 << "]" << endl;
				cin >> answer;
				if (answer == "da") {
					high = low + (high - low) * 0.4;
					count++;
					break;
				}else{
					low = low + (high - low) * 0.4;
					count++;
				}
				cout << "Trenutan interval [" << low << "-" << high << "]" << endl;
				cout << "Da li se broj nalazi u poslednjih 40% inervala -> [" << high - (high-low) * 0.4 << "-" << high << "]" << endl;
				cin >> answer;
				if (answer == "da") {
					low = high - (high - low) * 0.4;
					count++;
					break;
				}
				else {
					high = high - (high - low) * 0.4;
					count++;
				}
				break;
			}
			cout << "---------------------------------" << endl;
			cout << "Odgovarati na pitanja sa da ili ne, ukoliko je broj pronaden ukucati bilo sta != da/ne" << endl;
			cout << "Broj se nalazi u intervalu [" << low << "-" << high << "]" << endl;
			string answ2;
			while (true) {
				mid = (low + high) / 2;
				cout << "Da li je mozda resenje u opsegu [" << mid - err << "-" << mid + err << "]? ";
				cin >> answ2;
				if (answ2 == "da") break; 
				cout << "Da li je trazeni broj veci od " << mid << "? ";
				cin >> answer;
				if (answer == "da") {
					low = mid + err;
				}
				else if (answer == "ne") {
					high = mid - err;
				}
				else {
					count++;
					break;
				}
				count++;
			}
			cout << "Bilo je potrebno " << count << " koraka za prodnalazak trazenog broja!" << endl;
			cout << "---------------------------------" << endl;
		}
	}
	else {
		cout << "Pogresan unos vise srece drugi put!";
	}
}