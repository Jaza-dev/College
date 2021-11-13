#include "que.h"

Que::Que() {
	front = nullptr;
}
Que::Que(int n) {
	front = nullptr;
	Element* prev = nullptr, *elem;
	for (int i = 0; i < n; i++) {
		elem = new Element;
		if (front == nullptr) {
			front = elem;
			prev = elem;
		}
		else {
			prev->next = elem;
			prev = elem;
		}
	}
}
Element* Que::getFront()
{
	return front;
}
void Que::insert(Node* node) {
	Element* newElem = new Element;
	newElem->elem = node;
	newElem->next = nullptr;
	if (front == nullptr) {
		front = newElem;
		return;
	}
	Element* curr = front;
	while (curr->next != nullptr) {
		curr = curr->next;
	}
	curr->next = newElem;
}
Node* Que::remove() {
	Node* forReturn = front->elem;
	Element* forDelete = front;
	front = front->next;
	delete forDelete;
	return forReturn;
}
int Que::queSize() {
	int size = 0;
	Element* curr = front;
	while (curr != nullptr) {
		size++;
		curr = curr->next;
	}
	return size;
}
void Que::deleteQue() {
	Element* curr = front, *nextElem;
	while (curr != nullptr) {
		nextElem = curr->next;
		delete curr;
		curr = nextElem;
	}
}
Node* Que::peek() {
	Element* curr = front;
	if (front == nullptr) return nullptr;
	while (curr->next != nullptr) {
		curr = curr->next;
	}
	return curr->elem;
}

void Que::printQue() {
	Element* curr = front;
	while (curr != nullptr) {
		cout << curr->elem->getKey() << " ";
		curr = curr->next;
	}
	cout << endl;
}