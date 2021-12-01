#include "Tree.h"

bool checkIfTreeFormed(Tree* tree) {
	if (tree == nullptr) {
		cout << "STABLO NIJE FORMIRANO" << endl;
		return false;
	}
	return true;
}

int main() {
	Tree* tree = nullptr;
	short option, treeSize, k;
	string key;
	ifstream input;
	input.open("input.txt");
	while (1) {
		cout << "1. Stvaranje stabla" << endl;
		cout << "2. Pronalazenje kljuca u stablu" << endl;
		cout << "3. Ispis stabla" << endl;
		cout << "4. Ubacivanje kljuca u stablo" << endl;
		cout << "5. Brisanje kljuca iz stabla" << endl;
		cout << "6. Pronaci k-ti najmanji kljuc u stablu" << endl;
		cout << "7. Obrisati stablo" << endl;
		cout << "0. Kraj programa" << endl;
		cout << "Izbor: ";
		cin >> option;
		switch (option) {
		case 1:
			cout << "--------------------------------" << endl;
			cout << "Red stabla (3 - 10): ";
			cin >> treeSize;
			if (treeSize < 3 || treeSize > 10) {
				cout << "Zadati red je van opsega" << endl;
				break;
			}
			tree = new Tree(treeSize);
			break;
		case 2:
			cout << "--------------------------------" << endl;
			if (!checkIfTreeFormed(tree)) break;
			cout << "Kljuc za pretragu: ";
			cin >> key;
			if (tree->searchWordBool(key))
				cout << "Kljuc se nalazi u stablu" << endl;
			else
				cout << "Kljuc se ne nalazi u stablu" << endl;
			break;
		case 3:
			cout << "--------------------------------" << endl;
			if (!checkIfTreeFormed(tree)) break;
			cout << *tree << endl;
			break;
		case 4:
			cout << "--------------------------------" << endl;
			if (!checkIfTreeFormed(tree)) break;
			cout << "1 - Citanje sa standardnog ulaza" << endl;
			cout << "2 - Citanje iz datoteke" << endl;
			cin >> k;
			if (k == 1) {
				cout << "Kljuc za dodavanje: ";
				cin >> key;
				tree->addWord(key);
				cout << *tree;
				break;
			}else{
				
				if (!input.is_open()) {
					cout << "Greska pri radu sa datotekom" << endl;
					exit(-1);
				}
				input >> key;
				cout << "REC KOJA SE DODAJE: " << key << endl;
				tree->addWord(key);
				cout << *tree;
				break;
			}
		case 5:
			cout << "--------------------------------" << endl;
			if (!checkIfTreeFormed(tree)) break;
			cout << "Kljuc za brisanje: ";
			cin >> key;
			tree->deleteKey(key);
			cout << *tree;
			break;
		case 6:
			cout << "--------------------------------" << endl;
			if (!checkIfTreeFormed(tree)) break;
			cout << "K: ";
			cin >> k;
			cout << "Najmanji kljuc na " << k << ". poziciji je: " << tree->searchKSmallestKey(k) << endl;
			break;
		case 7:
			cout << "--------------------------------" << endl;
			if (!checkIfTreeFormed(tree)) break;
			break;
		case 0:
			exit(1);
			break;
		}
	}
	input.close();
}