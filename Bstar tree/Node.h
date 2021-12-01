#ifndef _node_
#define _node_
#include "iostream"
#include "string"
#include "queue"
#include "fstream"
using namespace std;

class Node {
private:
	int size = 0, cap;
	string* words;
	Node* parent = nullptr;
	Node** nodes = nullptr;
	void sortArray(string* strArr, int size);
	void sortNodes(Node** nodes, int size);
public:
	Node(int c);
	~Node();
	Node(const Node& node);
	int getCap() const;
	int& getSize();
	string* getWords();
	Node* getParent();
	Node** getNodes();
	void setParent(Node* p);
	bool isFull() const;
	Node* right();
	Node* left();
	void putInRight(Node* rightB, string word = "");
	void putInLeft(Node* leftB, string word = "");
	Node& operator=(const Node& node) = delete;
	void rootBreak(string& word, int m,int nodeMax, Node* overload = nullptr);
	void nodeBreak(string& word, int m, int rootM, int leftSize, int middleSize, int rightSize, Node* overload = nullptr);
	bool searchWord(string& word) const;
	int getSearchIndex(string& word)const; //pretraga koja vraca indeks uspesne pretrage
	bool addWord(string& word);
	bool removeWord(string& word);
	Node* switchWithSucc(string& word);
	Node* threeToTwo(Node* rightB, Node* leftB, Node* tree);
	Node* threeToTwoR(Node* rightB, Node* rightRightB, Node* tree);
	Node* threeToTwoL(Node* leftB, Node* leftLeftB, Node* tree);
	Node* twoToOneR(Node* rightB, Node* tree);
	Node* twoToOneL(Node* leftB, int k , Node* tree); //k sluzi da se razlikuju f-je kao za operator++
	friend ostream& operator<<(ostream& os, Node& node);
};

#endif