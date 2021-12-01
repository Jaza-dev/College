#ifndef _tree_
#define _tree_
#include "Node.h"

class Tree {
private:
	Node* root;
	int m;
	int rootMin = 1, rootMax, nodeMin, nodeMax; //broj cvororova unutar noda
	int leftSize, middleSize, rightSize; //broj cvororova unutar noda
	void sortVector(vector<string>& v);
public:
	Tree(int m);
	~Tree();
	void setRoot(Node* node);
	bool addWord(string& word);
	Node* searchWordPointer(string& word);
	bool searchWordBool(string& word);
	Node* searchWord(string& word);
	bool deleteKey(string& word);
	string searchKSmallestKey(int k);
	friend ostream& operator<<(ostream& os, Tree& tree);
};

#endif