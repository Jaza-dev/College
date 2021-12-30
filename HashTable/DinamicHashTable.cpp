#include "DinamicHashTable.h"


int DinamicHashTable::hash(string& key) {
	int numKey = atoi(&key[0]);
	return mod(numKey, p);
}

int DinamicHashTable::mod(int number, int p) {
	return ((1 << p) - 1) & number;
}
DinamicHashTable::~DinamicHashTable() {
	clear();
}
bool DinamicHashTable::insertKey(Student* student) {
	int address = hash(student->getIndex());
	bool check = buckets[address]->addStudent(student);
	if (check)
		this->size++;
	return check;
}

Student* DinamicHashTable::findeKey(string key, bool del) {
	int address = hash(key);
	Student* stud = buckets[address]->searchStudent(key);
	if (stud != nullptr && del == true) {
		buckets[address]->getSize()--;
	}
	if (stud->DELETED())
		return nullptr;
	return stud;
}

bool DinamicHashTable::deleteKey(string& key) {
	Student* student = findeKey(key, true);
	if (student != nullptr)
	{
		student->setDELETED();
		size--;
		return true;
	}
	return false;
}

void DinamicHashTable::clear() {
	for (int i = 0; i < cap; i++) {
		buckets[i]->clear();
	}
}

int DinamicHashTable::keyCount() const {
	return size;
}

int DinamicHashTable::tableSize() const {
	return cap * pow(2, b);
}

ostream& operator<<(ostream& os, const DinamicHashTable& table) {
	for (int i = 0; i < table.cap; i++) {
		os << (i+1) << ". " << *table.buckets[i] << endl;
	}
	return os;
}