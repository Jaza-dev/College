#pragma once
#include "iostream"
#include "string.h"
using namespace std;


class Book {
private:
	static int id;
	string name, author;
	int bookId;
public:
	Book(string n, string a);
	Book(const Book& b) = delete;
	Book& operator=(const Book& b) = delete;
	string& getName();
	string& getAutor();
	int getId();
	Book* operator!();
	friend ostream& operator<<(ostream& os, Book& b);
};