#pragma once
#include <string>
#include <iostream>
#include "list.h"
using namespace std;


class Node {
private:
	string key;
	myListNode* info;
	Node* left, *right, *parent;
public:
	Node(string k = "0", string i = "0", Node* p = nullptr, Node* l = nullptr, Node* r = nullptr) {
		key = k;
		info = new myListNode;
		info->info = i;
		info->next = nullptr;
		left = l; right = r; parent = p;
	}
	string& getKey();
	string getInfo();
	Node* getLeft();
	Node* getRight();
	Node* getParent();
	void setLeft(Node* lnode);
	void setRight(Node* rnode);
	void setParent(Node* pnode);
	void addInfo(string moreInfo);
	void deleteInfo();
};