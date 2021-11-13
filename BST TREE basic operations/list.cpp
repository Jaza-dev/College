#include "list.h"
void addMyListNode(myListNode* head, string info) {
	myListNode* curr = head;
	myListNode* newNode = new myListNode;
	newNode->info = info;
	newNode->next = nullptr;
	while (curr->next != nullptr) {
		curr = curr->next;
	}
	curr->next = newNode;
}
void freeMyList(myListNode* head) {
	myListNode* curr = head, * nextListNode;
	while (curr != nullptr) {
		nextListNode = curr->next;
		delete curr;
		curr = nextListNode;
	}
}

string readMyList(myListNode* head) {
	string info = "";
	myListNode* curr = head;
	while (curr->next != nullptr) {
		info += curr->info + "; ";
		curr = curr->next;
	}
	info += curr->info;
	return info;
}