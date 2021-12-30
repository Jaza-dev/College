#pragma once
#include "includes.h"
#include "Student.h"

class Bucket {
private:
	int cap, size = 0, sizeWithDeleted = 0, compareValue = 0;
	Student** students;
public:
	Bucket(int c): cap(c), students(new Student*[c]) { 
		for (int i = 0; i < c; i++) {
			students[i] = nullptr;
		}
	};
	int getCap() const;
	bool isFull();
	bool isFullWithDeleted() const;
	void addStudent(Student* student);
	Student* searchStudent(string& key);
	int getCompareValue();
	int& getSize();
	void clear();
	friend ostream& operator<<(ostream& os, const Bucket& bucket);
};

