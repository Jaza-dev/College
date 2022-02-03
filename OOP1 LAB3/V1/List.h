#pragma once
#include "includes.h"
#include "Errors.h"

template<typename T>
class List {
private:
	struct Node {
		T info;
		Node* next;
		Node(const T& i, Node* n = nullptr) {
			this->info = i;
			this->next = n;
		}
	};
	int size = 0;
	Node* head = nullptr, * tail = nullptr;
	mutable Node*curr = nullptr;
	void copy(const List& l);
	void move(List& l);
	void del();
public:
	List() = default;
	List(const List& l);
	List(List&& l);
	List& operator=(const List& l);
	List& operator=(List&& l);
	~List();
	List& add(const T& info);
	int getSize() const;
	List& setToHead();
	const List& setToHead() const;
	List& setNext();
	const List& setNext() const;
	bool checkCurr() const;
	T& getCurrValue();
};

template<typename T>
void List<T>::copy(const List& l) {
	head = nullptr, tail = nullptr, curr = nullptr;
	l.setToHead();
	while (l.curr) {
		tail = (!head ? head : tail->next) = new Node(l.curr->info);
		l.setNext();
	}
	size = l.size;
}

template<typename T>
void List<T>::move(List& l) {
	head = l.head;
	tail = l.tail;
	curr = l.curr;
	size = l.size;
	l.head = l.tail = l.curr = nullptr;
}

template<typename T>
void List<T>::del() {
	Node* next = nullptr;
	curr = head;
	while (curr) {
		next = curr->next;
		delete curr;
		curr = next;
	}
	head = nullptr, tail = nullptr, curr = nullptr;
}

template<typename T>
List<T>::List(const List& l) {
	copy(l);
}

template<typename T>
List<T>::List(List&& l) {
	move(l);
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& l) {
	if (this != &l) {
		del();
		copy(l);
	}
	return *this;
}

template<typename T>
List<T>& List<T>::operator=(List<T>&& l) {
	if (this != &l) {
		del();
		move(l);
	}
	return *this;
}

template<typename T>
List<T>::~List() {
	this->del();
}

template<typename T>
List<T>& List<T>::add(const T& info) {
	tail = (!head ? head : tail->next) = new Node(info);
	size++;
	return *this;
}

template<typename T>
int List<T>::getSize() const {
	return this->size;
}

template<typename T>
List<T>& List<T>::setToHead() {
	curr = head;
	return *this;
}

template<typename T>
const List<T>& List<T>::setToHead() const {
	curr = head;
	return *this;
}

template<typename T>
List<T>& List<T>::setNext() {
	if (!this->checkCurr()) throw ENoCurrElement();
	else {
		curr = curr->next;
	}
	return *this;
}

template<typename T>
const List<T>& List<T>::setNext() const {
	if (!this->checkCurr()) throw ENoCurrElement();
	else {
		curr = curr->next;
	}
	return *this;
}

template<typename T>
bool List<T>::checkCurr() const {
	return curr != nullptr;
}

template<typename T>
T& List<T>::getCurrValue() {
	if (!this->checkCurr()) throw ENoCurrElement();
	else
		return curr->info;
}

