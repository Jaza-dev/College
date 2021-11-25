#include "Library.h"

Library::Library(string n, int mc) {
	name = n;
	maxCap = mc;
}
void Library::copy(const Library& lib) {
	name = lib.name;
	count = lib.count;
	maxCap = lib.maxCap;
	NodeB* curr = lib.books, *newNode = nullptr;
	while (curr != nullptr) {
		newNode = new NodeB(!*curr->book);
		if (books == nullptr) {
			books = newNode;
			lstBooks = newNode;
		}
		else {
			lstBooks->next = newNode;
			lstBooks = newNode;
		}
		curr = curr->next;
	}
}

void Library::move(Library& lib) {
	name = lib.name;
	count = lib.count;
	maxCap = lib.maxCap;
	books = lib.books;
	lib.books = nullptr;
}

void Library::del() {
	NodeB* curr = books, *next;
	while (curr != nullptr) {
		next = curr->next;
		delete curr;
		curr = next;
	}
}

Library::Library(const Library& lib) {
	copy(lib);
}

Library::Library(Library&& lib) {
	move(lib);
}

string& Library::getName() { return name; }

Library& Library::operator=(const Library& lib) {
	if (this != &lib) {
		del();
		copy(lib);
	}
	return *this;
}

int Library::getCount() { return count; }

Library& Library::operator=(Library&& lib) {
	if (this != &lib) {
		del();
		move(lib);
	}
	return *this;
}

int Library::getMaxCap() { return maxCap; }

Library::~Library() {
	del();
}

Library& Library::operator+=(Book& book) {
	NodeB* newNode = new NodeB(!book);
	count++;
	if (books == nullptr) {
		books = newNode;
		lstBooks = newNode;
	}
	else {
		lstBooks->next = newNode;
		lstBooks = newNode;
	}
	return *this;
}

Library& Library::operator+=(Book&& book) {
	NodeB* newNode = new NodeB(!book);
	count++;
	if (books == nullptr) {
		books = newNode;
		lstBooks = newNode;
	}
	else {
		lstBooks->next = newNode;
		lstBooks = newNode;
	}
	return *this;
}

Book* Library::getBook(int id) {
	if (id < 0) id = 0;
	NodeB* curr = books;
	while (curr != nullptr) {
		if (curr->book->getId() == id) return curr->book;
		curr = curr->next;
	}
	return nullptr;
}
