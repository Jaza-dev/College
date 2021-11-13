#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "que.h"
#include <cmath>
#include <string>

using namespace std;
class Tree {
private:
	Node* root;
public:
	Tree(string k = "0", string i = "0") {
		root = new Node(k, i, nullptr, nullptr, nullptr);
	}
	Tree(int n);
	Tree(FILE* in);
	Node* getRoot();
	int treeHeight();
	void addNode(Node* node);
	Node* getNode(string k);
	void printTree();
	void deleteTree();
	void deleteNode(string key);
	void searchWithPrefix(string prefix);
};