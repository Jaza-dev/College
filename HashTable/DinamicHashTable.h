#pragma once
#include "includes.h"
#include "DinamicBucket.h"
class DinamicHashTable {
private:
	int b,p, cap, size = 0;
	DinamicBucket** buckets = nullptr;
	int hash(string& key);
	int mod(int number, int p);
public:
	DinamicHashTable(int p, int b) :b(b), p(p),cap(pow(2, p)) , buckets(new DinamicBucket*[cap]){
		for (int i = 0; i < cap; i++) {
			buckets[i] = new DinamicBucket(pow(2, b), p);
		}
	}
	~DinamicHashTable();
	Student* findeKey(string key, bool del = false);
	bool insertKey(Student* student);
	bool deleteKey(string& key);
	void clear();
	int keyCount() const;
	int tableSize() const;
	friend ostream& operator<<(ostream& os, const DinamicHashTable& table);
	double fillRatio() const { return (keyCount()*1.0) / (cap* pow(2, b)); }
};

