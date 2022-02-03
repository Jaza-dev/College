#pragma once
#include "includes.h"

template<typename T>
class Pair {
private:
	T* p1; //pointer1
	T* p2;
	void copy(const Pair& pair);
	void move(Pair& pair);
	void del();
public:
	Pair(T* p1, T* p2);
	Pair(const Pair& pair);
	Pair(Pair&& pair);
	Pair& operator=(const Pair& pair);
	Pair& operator=(Pair&& pair);
	~Pair();
	void setPointer1(T* p);
	void setPointer2(T* p);
	T* getPointer1();
	T* getPointer2();
	bool operator==(const Pair<T> pair2);
	template<typename T>friend ostream& operator<<(ostream& os, const Pair<T>& pair);
};

template<typename T>
void Pair<T>::copy(const Pair& pair) {
	p1 = new T(*pair.p1);
	p2 = new T(*pair.p2);
}

template<typename T>
void Pair<T>::move(Pair& pair) {
	p1 = pair.p1;
	pair.p1 = nullptr;
	p2 = pair.p2;
	pair.p2 = nullptr;
}

template<typename T>
void Pair<T>::del() {
	delete p1;
	delete p2;
}

template<typename T>
Pair<T>::Pair(T* p1, T* p2) : p1(new T(*p1)), p2(new T(*p2)) { }

template<typename T>
Pair<T>::Pair(const Pair& pair) {
	copy(pair);
}

template<typename T>
Pair<T>::Pair(Pair&& pair) {
	move(pair);
}

template<typename T>
Pair<T>& Pair<T>::operator=(const Pair& pair) {
	if (this != &pair) {
		del();
		copy(pair);
	}
	return *this;
}

template<typename T>
Pair<T>& Pair<T>::operator=(Pair&& pair) {
	if (this != &pair) {
		del();
		move(pair);
	}
	return *this;
}

template<typename T>
Pair<T>::~Pair() {
	del();
}

template<typename T>
void Pair<T>::setPointer1(T* p) {
	p1 = p;
}

template<typename T>
void Pair<T>::setPointer2(T* p) {
	p2 = p;
}

template<typename T>
T* Pair<T>::getPointer1() {
	return p1;
}

template<typename T>
T* Pair<T>::getPointer2() {
	return p2;
}

template<typename T>
bool Pair<T>::operator==(const Pair<T> pair2) {
	return (*p1 == *pair2.p1 && *p2 == *pair2.p2);
}

template<typename T>
ostream& operator<<(ostream& os, const Pair<T>& pair) {
	return os << "[" << *pair.p1 << "-" << *pair.p2 << "]";
}


