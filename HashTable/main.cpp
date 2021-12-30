#include "includes.h"
#include "Bucket.h"
#include "HashTable.h"
#include "AddressFunction.h"
#include "SplitSequenceLinearHashing.h"
#include "DinamicHashTable.h"

int main() {
	int assigment;
	cout << "Zadatak 1 il 2: ";
	cin >> assigment;
	if (assigment == 1) {
		HashTable* table = nullptr;
		AddressFunction* function = new SplitSequenceLinearHashing;
		Student* student;
		int option, p, bucketCap;
		string key;
		ifstream input("students_10000.csv");
		getline(input, key); //preskacem zaglavlje
		while (true) {
			cout << "1. Pronaci zadati kljuc" << endl;
			cout << "2. Dodavanje studenta u tabelu" << endl;
			cout << "3. Brisanje kljuca iz tabele" << endl;
			cout << "4. Isprazniti tabelu" << endl;
			cout << "5. Broj kljuceva u tabeli" << endl;
			cout << "6. Velicina tabele" << endl;
			cout << "7. Ispis tabele" << endl;
			cout << "8. Stepen popunjenosti tabele" << endl;
			cout << "9. Prijaviti ispit studentu" << endl;
			cout << "10. Odjaviti ispit studentu" << endl;
			cout << "0. Kraj programa" << endl;
			cout << "Opcija: ";
			cin >> option;
			switch (option) {
			case 0:
				exit(0);
			case 1:
				if (table != nullptr) {
					cout << "Kljuc: ";
					cin >> key;
					if ((student = table->findeKey(key)) != nullptr) {
						cout << "Kljuc se nalazi u tabeli" << endl;
						cout << *student << endl;
					}
					else { cout << "Kljuc se ne nalazi u tabeli" << endl; }
				}
				else cout << "Tabla nije kreirana" << endl;
				break;
			case 2:
				if (table == nullptr) {
					cout << "Tabela jos uvek nije kreirana unesite p: ";
					cin >> p;
					cout << "Kapacitet baketa: ";
					cin >> bucketCap;
					table = new HashTable(p, bucketCap, function);
				}
				cout << "1. Dodaj studenta sa standardnog ulaza(indeks,ime prezime,[ispiti])\n";
				cout << "2. Dodaj studenta iz datoteke\n";
				cout << "Opcija: ";
				cin >> option;
				if (option == 1) {
					cout << "Student: ";
					cin.ignore();
					getline(cin,key);
					student = new Student(key);
					if (table->insertKey(student)) {
						cout << "Uspesno zapamcen student: " << *student << endl;
					}
					else {
						cout << "Neuspesan upis studenta: " << *student << endl;
					}
				}
				else if (option == 2) {
					if (!input.is_open()) {
						cout << "Greska pri radu sa datotekom" << endl;
						exit(-1);
					}
					while (getline(input, key)) {
						student = new Student(key);
						if (table->insertKey(student)) {
							cout << "Uspesno zapamcen student: " << *student << endl;
						}
						else {
							cout << "Neuspesan upis studenta: " << *student << endl;
						}
					}
				}
				else { cout << "Nepostojana opcija!" << endl; }
				break;
			case 3:
				cout << "Kljuc: ";
				cin >> key;
				if (table != nullptr) {
					if (table->deleteKey(key)) {
						cout << "Uspesno obrisan kljuc " << key << endl;
					}
					else { cout << "Neuspesno obrisan kljuc " << key << endl; }
				}
				else cout << "Tabla nije kreirana" << endl;
				break;
			case 4:
				if (table != nullptr)
					table->clear();
				else cout << "Tabla nije kreirana" << endl;
				break;
			case 5:
				if (table != nullptr)
					cout << "Broj kljuceva u tabeli: " << table->keyCount() << endl;
				else cout << "Tabla nije kreirana" << endl;
				break;
			case 6:
				if(table != nullptr)
					cout << "Velicina tabele: " << table->tableSize() << endl;
				else cout << "Tabla nije kreirana" << endl;
				break;
			case 7:
				if (table != nullptr)
					cout << *table;
				else cout << "Tabla nije kreirana" << endl;
				break;
			case 8:
				if(table != nullptr)
					cout << "Tabela je popunjena " << table->fillRatio() << endl;
				else cout << "Tabla nije kreirana" << endl;
				break;
			case 9:
				if (table != nullptr) {
					cout << "Kljuc: ";
					cin >> key;
					if ((student = table->findeKey(key)) != nullptr) {
						cout << "Student: " << * student << endl;
						cout << "Ispit koji zelite da dodate: ";
						cin >> key;
						student->AddExam(key);
						cout << "Ispit uspesno dodat: " << *student << endl;
					}
					else { cout << "Kljuc se ne nalazi u tabeli" << endl; }
				}
				else cout << "Tabla nije kreirana" << endl;
				break;
			case 10:
				if (table != nullptr) {
					cout << "Kljuc: ";
					cin >> key;
					if ((student = table->findeKey(key)) != nullptr) {
						cout << "Student: " << *student << endl;
						cout << "Ispit koji zelite da obrisete: ";
						cin >> key;
						student->RemoveExam(key);
						cout << "Ispit uspesno obrisan: " << *student << endl;
					}
					else { cout << "Kljuc se ne nalazi u tabeli" << endl; }
				}
				else cout << "Tabla nije kreirana" << endl;
				break;
			default:
				cout << "?" << endl;
				break;
			}
		}
		input.close();
	}
	else if(assigment == 2) {
		DinamicHashTable* table = nullptr;
		Student* student;
		int option, p, b;
		string key;
		ifstream input("students_10000.csv");
		getline(input, key); //preskacem zaglavlje
		while (true) {
			cout << "1. Pronaci zadati kljuc" << endl;
			cout << "2. Dodavanje studenta u tabelu" << endl;
			cout << "3. Brisanje kljuca iz tabele" << endl;
			cout << "4. Isprazniti tabelu" << endl;
			cout << "5. Broj kljuceva u tabeli" << endl;
			cout << "6. Velicina tabele" << endl;
			cout << "7. Ispis tabele" << endl;
			cout << "8. Stepen popunjenosti tabele" << endl;
			cout << "9. Prijaviti ispit studentu" << endl;
			cout << "10. Odjaviti ispit studentu" << endl;
			cout << "0. Kraj programa" << endl;
			cout << "Opcija: ";
			cin >> option;
			switch (option) {
			case 0:
				exit(0);
			case 1:
				if (table != nullptr) {
					cout << "Kljuc: ";
					cin >> key;
					if ((student = table->findeKey(key)) != nullptr) {
						cout << "Kljuc se nalazi u tabeli" << endl;
						cout << *student << endl;
					}
					else { cout << "Kljuc se ne nalazi u tabeli" << endl; }
				}
				else cout << "Tabla nije kreirana" << endl;
				break;
			case 2:
				if (table == nullptr) {
					cout << "Tabela jos uvek nije kreirana unesite p: ";
					cin >> p;
					cout << "Unesite b: ";
					cin >> b;
					table = new DinamicHashTable(p,b);
				}
				cout << "1. Dodaj studenta sa standardnog ulaza(indeks,ime prezime,[ispiti])\n";
				cout << "2. Dodaj studenta iz datoteke\n";
				cout << "Opcija: ";
				cin >> option;
				if (option == 1) {
					cout << "Student: ";
					cin.ignore();
					getline(cin, key);
					student = new Student(key);
					if (table->insertKey(student)) {
						cout << "Uspesno zapamcen student: " << *student << endl;
					}
					else {
						cout << "Neuspesan upis studenta: " << *student << endl;
					}
				}
				else if (option == 2) {
					if (!input.is_open()) {
						cout << "Greska pri radu sa datotekom" << endl;
						exit(-1);
					}
					while (getline(input, key)) {
						student = new Student(key);
						if (table->insertKey(student)) {
							cout << "Uspesno zapamcen student: " << *student << endl;
						}
						else {
							cout << "Neuspesan upis studenta: " << *student << endl;
						}
					}
				}
				else { cout << "Nepostojana opcija!" << endl; }
				break;
			case 3:
				cout << "Kljuc: ";
				cin >> key;
				if (table != nullptr) {
					if (table->deleteKey(key)) {
						cout << "Uspesno obrisan kljuc " << key << endl;
					}
					else { cout << "Neuspesno obrisan kljuc " << key << endl; }
				}
				else cout << "Tabla nije kreirana" << endl;
				break;
			case 4:
				if (table != nullptr)
					table->clear();
				else cout << "Tabla nije kreirana" << endl;
				break;
			case 5:
				if (table != nullptr)
					cout << "Broj kljuceva u tabeli: " << table->keyCount() << endl;
				else cout << "Tabla nije kreirana" << endl;
				break;
			case 6:
				if (table != nullptr)
					cout << "Velicina tabele: " << table->tableSize() << endl;
				else cout << "Tabla nije kreirana" << endl;
				break;
			case 7:
				if (table != nullptr)
					cout << *table;
				else cout << "Tabla nije kreirana" << endl;
				break;
			case 8:
				if (table != nullptr)
					cout << "Tabela je popunjena " << table->fillRatio() << endl;
				else cout << "Tabla nije kreirana" << endl;
				break;
			case 9:
				if (table != nullptr) {
					cout << "Kljuc: ";
					cin >> key;
					if ((student = table->findeKey(key)) != nullptr) {
						cout << "Student: " << *student << endl;
						cout << "Ispit koji zelite da dodate: ";
						cin >> key;
						student->AddExam(key);
						cout << "Ispit uspesno dodat: " << *student << endl;
					}
					else { cout << "Kljuc se ne nalazi u tabeli" << endl; }
				}
				else cout << "Tabla nije kreirana" << endl;
				break;
			case 10:
				if (table != nullptr) {
					cout << "Kljuc: ";
					cin >> key;
					if ((student = table->findeKey(key)) != nullptr) {
						cout << "Student: " << *student << endl;
						cout << "Ispit koji zelite da obrisete: ";
						cin >> key;
						student->RemoveExam(key);
						cout << "Ispit uspesno obrisan: " << *student << endl;
					}
					else { cout << "Kljuc se ne nalazi u tabeli" << endl; }
				}
				else cout << "Tabla nije kreirana" << endl;
				break;
			default:
				cout << "?" << endl;
				break;
			}
		}
		input.close();
	}
	else {
		cout << "Nepostojeci zadatk!" << endl;
		exit('?');
	}
	
}