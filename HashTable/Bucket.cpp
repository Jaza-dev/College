#include "Bucket.h"

void Bucket::addStudent(Student* student) {
	for (int i = 0; i < cap; i++) {
		if (sizeWithDeleted == 0) compareValue = atoi(&student->getIndex()[0]);
		if (students[i] == nullptr || students[i]->DELETED()) {
			students[i] = student;
			student = nullptr;
			size++;
			if(sizeWithDeleted < cap)
				sizeWithDeleted++;
			return;
		}
	}
}

Student* Bucket::searchStudent(string& key) {
	for (int i = 0; i < cap; i++) {
		if (students[i] != nullptr && key == students[i]->getIndex()) {
			return students[i];
		}
	}
	return nullptr;
}

void Bucket::clear() {
	for (int i = 0; i < cap; i++) {
		delete students[i];
		students[i] = nullptr;
	}
	size = 0;
}

int& Bucket::getSize(){
	return this->size;
}

int Bucket::getCap() const {
	return this->cap;
}

bool Bucket::isFull() {
	return this->getSize() == getCap();
}

bool Bucket::isFullWithDeleted() const {
	return this->sizeWithDeleted == this->getCap();
}

int Bucket::getCompareValue() {
	return this->compareValue;
}

ostream& operator<<(ostream& os, const Bucket& bucket) {
	for (int i = 0; i < bucket.cap; i++) {
		if (i) os << " | ";
		if (bucket.students[i] == nullptr)
			os << "EMPTY";
		else if (bucket.students[i]->DELETED())
			os << "DELETED";
		//else os << *bucket.students[i];
		else bucket.students[i]->printIndex();
	}
	return os;
}