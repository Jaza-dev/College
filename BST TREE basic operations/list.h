#pragma once
#include <string>
#include <iostream>
using namespace std;

struct myListNode {
	string info;
	myListNode* next = nullptr;
};
void addMyListNode(myListNode* head, string info);
void freeMyList(myListNode* head);
string readMyList(myListNode* head);