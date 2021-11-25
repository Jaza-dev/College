#include "Library.h"

ostream& operator<<(ostream& os, Book& b) {
	return os << "KNJIGA " << b.getId() << " : " << b.getName() << " - " << b.getAutor();
}
ostream& operator<<(ostream& os, Library& lib) {
	os << "BIBLIOTEKA " << lib.getName() << " " << lib.getCount() << " / " << lib.getMaxCap() << endl;
	NodeB* curr = lib.books;
	while (curr != nullptr) {
		cout << *curr->book << endl;
		curr = curr->next;
	}
	return os;
}
int Book::id = 0;
int main() {
	Book b1 = { "Druzina prstena", "Tolkin" };
	Book b2 = { "Dve kule", "Tolkin" };
	Book b3 = { "Ime vetra", "Patrik Rotfus" };
	Book* b4 = !b3;
	cout << *b4 << endl;
	Book* b5 = !*b4;
	cout << *b5 << endl;
	cout << "-------------------------" << endl;
	Library lib("Kralj", 1000);
	lib += b1;
	lib += b2;
	lib += b3;
	lib += *b4;
	cout << *lib.getBook(8) << endl;
	lib += Book("C++", "Laslo Kraus");
	cout << lib;
	cout << lib;
	cout << "--------------------------" << endl;
	Library lib2(lib);
	cout << lib2;
}