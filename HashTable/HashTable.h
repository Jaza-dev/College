#pragma once
#include "includes.h"
#include "Bucket.h"
#include "AddressFunction.h"
//obrisani student ce imati index = DELETED, ostale vrednosti prazni stringovi
//prazna polja ce imati nullptr
class HashTable {
private:
	int p, bucketCap;
	int cap, size = 0;
	Bucket** buckets;
	AddressFunction* function;
	int mod(int number, int p);
	int hash(string& key);
public:
	HashTable(int p,int k, AddressFunction* function);
	~HashTable();
	Student* findeKey(string& key, bool del = false);
	bool insertKey(Student* student);
	bool deleteKey(string& key);
	void clear();
	int keyCount() const;
	int tableSize() const;
	friend ostream& operator<<(ostream& os, const HashTable& table);
	double fillRatio() const;
};	

