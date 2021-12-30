#include "DinamicBucket.h"

int DinamicBucket::getPBit(int key, int p) { 
	//vraca 0 ako je na p-poziciji 0 ili neki stepen dvojke ako nije 0
	return ((1 << p)) & key;
}

DinamicBucket::~DinamicBucket() {
	clear();
}

bool DinamicBucket::addStudent(Student* student) {
	Student* tempStudent = nullptr;
	if (this->isFull()) return false; 
	if (((tempStudent = searchStudent(student->getIndex())) != nullptr) && !tempStudent->DELETED()) return false;
	else if (tempStudent != nullptr) {
		tempStudent->getIndex() = student->getIndex();
		tempStudent->getName() = student->getName();
		tempStudent->getSurname() = student->getSurname();
		tempStudent->clearExams();
		tempStudent->setExams(student->getExams());
		tempStudent->DELETED() = false;
		return true;
	}
	Node* curr = root, *parent = nullptr;
	int i = p + 1;
	bool left = false;
	int key = atoi(&(student->getIndex())[0]); //indeks
	if (root != nullptr) {
		while (!curr->info) {
			parent = curr;
			if (getPBit(key, i)) {
				curr = curr->right;
				left = false;
			}
			else {
				curr = curr->left;
				left = true;
			}
			i++;
		}
		Node* newNodeRoot = new Node();
		if (parent == nullptr)
			root = newNodeRoot;
		else if (left)
			parent->left = newNodeRoot;
		else
			parent->right = newNodeRoot;
		Node* newNode = new Node();
		newNode->info = true;
		newNode->student = student;
		if (getPBit(key, i)) {
			newNodeRoot->right = newNode;
			newNodeRoot->left = curr;
		}
		else {
			newNodeRoot->right = curr;
			newNodeRoot->left = newNode;
		}
	}
	else {
		Node* newNode = new Node();
		root = newNode;
		newNode->info = true;
		newNode->student = student;
	}
	size++;
	return true;
}

Student* DinamicBucket::searchStudent(string& key) {
	Node* curr = root;
	if (curr == nullptr)
		return nullptr;
	int levleSize;
	queue<Node*> que;
	que.push(root);
	while (true) {
		levleSize = que.size();
		if (levleSize == 0) return nullptr;
		while (levleSize > 0) {
			curr = que.front();
			que.pop();
			if (curr->info && curr->student->getIndex() == key) {
				return curr->student;
			}
			if (curr->left != nullptr) {
				que.push(curr->left);
			}
			if (curr->right != nullptr) {
				que.push(curr->right);
			}
			levleSize--;
		}
	}
}

void DinamicBucket::clear() {
	Node* curr = root;
	if (curr == nullptr)
		return;
	int levleSize;
	queue<Node*> que;
	que.push(root);
	while (true) {
		levleSize = que.size();
		if (levleSize == 0) {
			root = nullptr;
			return;
		}
		while (levleSize > 0) {
			curr = que.front();
			que.pop();
			if (curr->left != nullptr) {
				que.push(curr->left);
			}
			if (curr->right != nullptr) {
				que.push(curr->right);
			}
			delete curr;
			levleSize--;
		}
	}
}

ostream& operator<<(ostream& os, const DinamicBucket& bucket) {
	Node* curr = bucket.root;
	if (curr == nullptr)
		return os << "EMPTY";
	int levleSize;
	queue<Node*> que;
	que.push(bucket.root);
	while (true) {
		levleSize = que.size();
		if (levleSize == 0) return os;
		while (levleSize > 0) {
			curr = que.front();
			que.pop();
			if (curr->info) {
				if (curr->student->DELETED())
					os << "DELETED ";
				else
					os << curr->student->getIndex() << " ";
			}
			if (curr->left != nullptr) {
				que.push(curr->left);
			}
			if (curr->right != nullptr) {
				que.push(curr->right);
			}
			levleSize--;
		}
	}
}