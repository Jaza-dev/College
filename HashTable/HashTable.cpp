#include "HashTable.h" 

int pow(int a, int b) {
	int rez = 1;
	for (int i = 0; i <= b - 1; i++) {
		rez *= a;
	}
	return rez;
}

int HashTable::hash(string& key) {
	int numKey = atoi(&key[0]);
	return mod(numKey, p);
}

int HashTable::mod(int number, int p) {
	return ((1 << p) - 1) & number;
}

HashTable::HashTable(int p,int k, AddressFunction* function): p(p), bucketCap(k), cap(pow(2,p)), buckets(new Bucket*[cap]), function(function) {
	for (int i = 0; i < cap; i++) {
		buckets[i] = new Bucket(bucketCap);
	}
}

HashTable::~HashTable() {
	for (int i = 0; i < cap; i++) {
		delete buckets[i];
	}
	delete[] buckets;
	buckets = nullptr;
}

Student* HashTable::findeKey(string& key, bool del) {
	int hashAddress = hash(key), compareValue, seconHashAddress;
	Student* student = nullptr;
	if ((student = buckets[hashAddress]->searchStudent(key)) == nullptr && !buckets[hashAddress]->isFullWithDeleted()) { //ukoliko student nije na inicijalnoj adresi, a bucket nije pun to znaci da sigurno nije u tabeli
		return nullptr;
	}
	else if (student != nullptr && student->DELETED()) { //ako je student pronadjen, ali ima oznaku deleted znaci da nije tabeli
		return nullptr;
	}
	else if (student != nullptr) { //student je na inicijalnoj adresi
		if (del)//kada radim brisanje samo smanjujem size bucketa
			buckets[hashAddress]->getSize()--;
		return student;
	}
	else { // slucaj kada student nije na inicijalnoj adresi a bucket je pun znaci ima sanse da je negde drugde
		compareValue = buckets[hashAddress]->getCompareValue(); //vrednost koju koristim za porednjenje pri izvrsavanju druge hash funkcije
		for (int i = 0; i < cap; i++) {
			seconHashAddress = mod(function->getAddress(key, hashAddress, i + 1, cap, compareValue), p);
			if ((student = buckets[seconHashAddress]->searchStudent(key)) != nullptr) {
				if (!student->DELETED()) {
					if (del)
						buckets[seconHashAddress]->getSize()--;
					return student;
				}
				else return nullptr;
			}
			else {
				if (!buckets[seconHashAddress]->isFullWithDeleted())
					return nullptr;
			}
			compareValue = buckets[seconHashAddress]->getCompareValue();
		}
	}
	return nullptr;
}

bool HashTable::insertKey(Student* student) {
	if (cap * bucketCap == size) return false;
	if (findeKey(student->getIndex()) != nullptr) 
		return false;
	int hashAddress = hash(student->getIndex());
	int seconHashAddress, compareValue;
	if (!buckets[hashAddress]->isFull()){
		buckets[hashAddress]->addStudent(student);
		size++;
		return true;
	}
	else {
		compareValue = buckets[hashAddress]->getCompareValue();
		for (int i = 0; i < cap; i++) {
			seconHashAddress = mod(function->getAddress(student->getIndex(), hashAddress, i+1, cap, compareValue), p);
			if (!buckets[seconHashAddress]->isFull()) {
				buckets[seconHashAddress]->addStudent(student);
				size++;
				return true;
			}
			compareValue = buckets[seconHashAddress]->getCompareValue();
		}
	}
	return false;
}

bool HashTable::deleteKey(string& key) {
	Student* student = nullptr;
	if ((student = findeKey(key, true)) != nullptr) {
		student->setDELETED();
		size--;
		return true;
	}
	else return false;
}

void HashTable::clear() {
	for (int i = 0; i < cap; i++) {
		buckets[i]->clear();
	}
	size = 0;
}

int HashTable::keyCount() const { return size; }

int HashTable::tableSize() const { return cap*bucketCap; }

double HashTable::fillRatio() const {
	double dCap = cap * 1.0;
	return (size*1.0)/(dCap*bucketCap);
}

ostream& operator<<(ostream& os, const HashTable& table) {
	for (int i = 0; i < table.cap; i++) {
		os << i << ". " << * table.buckets[i] << endl;
	}
	return os;
}
