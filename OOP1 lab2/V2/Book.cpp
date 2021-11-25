#include "Book.h"

Book::Book(string n, string a) {
	id++;
	bookId = id;
	name = n;
	author = a;
}

string& Book::getName() {
	return name;
}

string &Book::getAutor() {
	return author;
}

int Book::getId() {
	return bookId;
}

Book* Book::operator!(){
	return new Book(name, author);
}
