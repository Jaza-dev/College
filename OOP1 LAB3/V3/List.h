#pragma once
#include "includes.h"
#include "Errors.h"

template <typename T>
class List {
private:
	struct Node {
		T info;
		Node* next;
		Node(const T& data, Node* n = nullptr) {
			info = data;
			next = n;
		}
	};
	Node* head = nullptr, * tail = nullptr;
	int currentSize = 0;
	void copy(const List& l);
	void move(List& l);
	void del();
public:
	List() = default;
	List(const List & l);
	List(List && l);
	List& operator=(const List & l);
	List& operator=(List && l);
	~List();
	List& operator+=(const T & data);
	int size() const;
	T& operator[](int i) const;
};

template<typename T>
List<T>& List<T>::operator+=(const T& data) {
	tail = (!head ? head : tail->next) = new Node(data);
	currentSize++;
	return *this;
}

template<typename T>
int List<T>::size() const {
	return this->currentSize;
}

template<typename T>
T& List<T>::operator[](int i)const {
	if (i < 0 || i > this->currentSize) throw ENoData();
	Node* curr = head;
	int j = 0;
	while (j < i) {
		curr = curr->next;
		j++;
	}
	return curr->info;
}

template<typename T>
void List<T>::copy(const List& l) {
	Node* curr = l.head;
	while (curr) {
		tail = (!head ? head : tail->next) = new Node(curr->info);
		curr = curr->next;
	}
	currentSize = l.currentSize;
}

template<typename T>
void List<T>::move(List& l) {
	head = l.head;
	tail = l.tail;
	currentSize = l.currentSize;
	l.head = l.tail = nullptr;
	l.currentSize = 0;
}

template<typename T>
void List<T>::del() {
	Node* curr = head, * next = nullptr;
	while (curr) {
		next = curr->next;
		delete curr;
		curr = next;
	}
	head = tail = nullptr;
	currentSize = 0;
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
List<T>& List<T>::operator=(const List& l) {
	if (this != &l) {
		del();
		copy(l);
	}
	return *this;
}

template<typename T>
List<T>& List<T>::operator=(List&& l) {
	if (this != &l) {
		del();
		move(l);
	}
	return *this;
}

template<typename T>
List<T>::~List() {
	del();
}

