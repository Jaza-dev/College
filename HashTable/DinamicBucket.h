#pragma once
#include "includes.h"
#include "Student.h"

struct Node {
	Student* student = nullptr;
	bool info = false;
	Node* left = nullptr, * right = nullptr;
};

class DinamicBucket {
private:
	int cap, p , size = 0, sizeWithDeleted = 0;
	Node* root = nullptr;
	int getPBit(int key, int p);
public:
	DinamicBucket(int cap, int p) : cap(cap), p(p) {};
	~DinamicBucket();
	bool isFull() { return cap == size; }
	bool isFullWithDeleted() { return cap == sizeWithDeleted; }
	bool addStudent(Student* student);
	Student* searchStudent(string& key);
	int& getSize() { return size; }
	void clear();
	friend ostream& operator<<(ostream& os, const DinamicBucket& bucket);
};
