#pragma once
#include "node.h"
struct Element {
	Node* elem = nullptr;
	Element* next = nullptr;
};
class Que {
private:
	Element* front;
public:
	Que();
	Que(int n);
	Element* getFront();
	void insert(Node* node);
	Node* remove();
	int queSize();
	void deleteQue();
	Node* peek();
	void printQue();
};