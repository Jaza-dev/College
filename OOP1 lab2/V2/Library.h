#pragma once
#include "Book.h"

struct NodeB {
	Book* book;
	NodeB* next = nullptr;
	NodeB(Book* b) {
		book = b;
	}
};

class Library {
private:
	string name;
	int count = 0, maxCap;
	NodeB* books = nullptr, *lstBooks = nullptr;
	void copy(const Library& lib);
	void move(Library& lib);
	void del();
public:
	Library(string n, int mc);
	Library(const Library& lib);
	Library(Library&& lib);
	Library& operator=(const Library& lib);
	Library& operator=(Library&& lib);
	~Library();
	string& getName();
	int getCount();
	int getMaxCap();
	Library& operator+=(Book& book);
	Library& operator+=(Book&& book);
	Book* getBook(int id);
	friend ostream& operator<<(ostream& os, Library& lib);
};