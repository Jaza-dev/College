#include "Tree.h"

void Tree::sortVector(vector<string>& v) {
	int i, j;
	for (i = 0; i < (int)v.size() - 1; i++) {
		for (j = i + 1; j < (int)v.size(); j++) {
			if (v[i] > v[j]) {
				string temp = v[i];
				v[i] = v[j];
				v[j] = temp;
			}
		}
	}
}

Tree::Tree(int m) {
	this->m = m;
	rootMax = (int)(2 * floor((2 * m - 2) / 3.0));
	nodeMin = (int)ceil((2 * m - 1) / 3.0) - 1;
	nodeMax = m - 1;
	leftSize = (int)floor((2 * m - 2) / 3.0);
	middleSize = (int)floor((2 * m - 1) / 3.0);
	rightSize = (int)floor((2 * m) / 3.0);
	root = new Node(rootMax);
}

Tree::~Tree() {
	int size;
	queue<Node*> que;
	Node* curr = root;
	que.push(curr);
	while (true) {
		size = que.size();
		if (size == 0) return;
		while (size > 0) {
			curr = que.front();
			que.pop();
			for (int i = 0; i <= curr->getSize(); i++) {
				if (curr->getNodes()[i] != nullptr)
					que.push(curr->getNodes()[i]);
			}
			delete curr;
			size--;
		}
	}
}
void Tree::setRoot(Node* node) {
	this->root = node;
}
bool Tree::addWord(string& word) {
	Node* node = searchWordPointer(word);
	if(node != nullptr) {
		if (node->addWord(word)) { return true; }
		else {
			Node* rightB = node->right(), * leftB = node->left();
			if (rightB != nullptr && rightB->getSize() < nodeMax) { //ako desni brat postoji i ima mesta prelivanje
				node->putInRight(rightB, word);
				return true;
			}
			else if (leftB != nullptr && leftB->getSize() < nodeMax) { //ako levi brat postoji i ima mesta prelivanje
				node->putInLeft(leftB, word);
				return true;
			}
			else { //ako desni i levi brat ne postoje/ nemaju mesta - prelamanje
				if (node->getParent() == nullptr) {
					node->rootBreak(word, rootMax , nodeMax);
					return true;
				}
				else {
					node->nodeBreak(word, nodeMax, rootMax, leftSize, middleSize, rightSize);
					return true;
				}
			}
		}
	}
	return false;
}

Node* Tree::searchWordPointer(string& word) { //metoda vraca nullptr ako kljuc vec postoji, vraca pokazicav na list gde bi trebao da se nalazi kljuc
	int queSize, nodeSize, i;
	queue<Node*> que;
	Node* curr = root, *lstNode = nullptr;
	que.push(curr);
	while (true) {
		queSize = que.size();
		if (queSize == 0) return lstNode; //AKO REC NIJE U STABLU VRACAM POLSENJI CVOR GDE BI TREBAO DA BUDE
		while (queSize > 0) {
			lstNode = curr = que.front();
			que.pop();
			nodeSize = curr->getSize();
			for (i = 0; i < nodeSize; i++) {
				if (word == curr->getWords()[i]) return nullptr; //AKO JE REC VEC U STABLO VRACAM nullptr
			}
			for (i = 0; i < nodeSize; i++) {
				if (curr->getNodes()[i] != nullptr && curr->getWords()[i] > word) {
					que.push(curr->getNodes()[i]);
					break;
				}
				if (curr->getNodes()[i+1] != nullptr && i == nodeSize-1) {
					que.push(curr->getNodes()[i+1]);
				}
			}
			queSize--;
		}
	}
}

Node* Tree::searchWord(string& word) { //metoda vraca nullptr ako kljuc ne postoji, vraca pokazicav na node gde se nalazi kljuc
	int queSize, nodeSize, i;
	queue<Node*> que;
	Node* curr = root, * lstNode = nullptr;
	que.push(curr);
	while (true) {
		queSize = que.size();
		if (queSize == 0) return nullptr;
		while (queSize > 0) {
			lstNode = curr = que.front();
			que.pop();
			nodeSize = curr->getSize();
			for (i = 0; i < nodeSize; i++) {
				if (word == curr->getWords()[i]) return curr; //AKO JE REC VEC U STABLO VRACAM nullptr
			}
			for (i = 0; i < nodeSize; i++) {
				if (curr->getNodes()[i] != nullptr && curr->getWords()[i] > word) {
					que.push(curr->getNodes()[i]);
					break;
				}
				if (curr->getNodes()[i + 1] != nullptr && i == nodeSize - 1) {
					que.push(curr->getNodes()[i + 1]);
				}
			}
			queSize--;
		}
	}
}

bool Tree::searchWordBool(string& word) {
	if (searchWordPointer(word) == nullptr) return true;
	return false;
}

bool Tree::deleteKey(string& word) {
	Node* node = searchWord(word), * rightB = nullptr, * leftB = nullptr, *rightRightB = nullptr, *leftLeftB = nullptr;
	if (node != nullptr) {
		if (node->getNodes()[0] != nullptr)//ako nije list menjam sa sledbenikom
			node = node->switchWithSucc(word);
		node->removeWord(word); //izbacujem rec pa gledam da li je poremecen neki uslov
		if (node->getSize() < nodeMin) { 
			if ((rightB = node->right()) != nullptr && rightB->getSize() > nodeMin) {
				rightB->putInLeft(node);
			}
			else if ((leftB = node->left()) != nullptr && leftB->getSize() > nodeMin) {
				leftB->putInRight(node);
			}
			else if (rightB != nullptr && (rightRightB = rightB->right()) != nullptr && rightRightB->getSize() > nodeMin) {
				rightRightB->putInLeft(rightB);
				rightB->putInLeft(node);
			}
			else if (leftB != nullptr && (leftLeftB = leftB->left()) != nullptr && leftLeftB->getSize() > nodeMin) {
				leftLeftB->putInRight(leftB);
				leftB->putInRight(node);
			}
			else {
				if (rightB != nullptr && leftB != nullptr) {
					this->root = node->threeToTwo(rightB, leftB, this->root);
				}else if(leftB == nullptr && rightB != nullptr && rightRightB != nullptr){
					this->root = node->threeToTwoR(rightB, rightRightB, this->root);
				}
				else if (rightB == nullptr && leftB != nullptr && leftLeftB != nullptr) {
					this->root = node->threeToTwoL(leftB, leftLeftB, this->root);
				}
				else if (leftB == nullptr && rightRightB == nullptr && rightB != nullptr) {
					this->root = node->twoToOneR(rightB, this->root);
				}
				else if (rightB == nullptr && leftLeftB == nullptr && leftB != nullptr) {
					this->root = node->twoToOneL(leftB, 0, this->root);
				}
			}
			return true;
		}
		else { return true; }
	}
	return false;
}

string Tree::searchKSmallestKey(int k) { //!!!
	if (k <= 0) {
		cout << "Nevalidno k" << endl;
		exit(-1);
	}
	vector<string> v;
	int size;
	queue<Node*> que;
	Node* curr = root;
	que.push(curr);
	while (true) {
		size = que.size();
		if (size == 0) break;
		while (size > 0) {
			curr = que.front();
			que.pop();
			for (int i = 0; i <= curr->getSize(); i++) {
				if (curr->getNodes()[i] != nullptr)
					que.push(curr->getNodes()[i]);
			}
			for (int i = 0; i < curr->getSize(); i++) {
				v.push_back(curr->getWords()[i]);
			}
			size--;
		}
	}
	if (k > (int)v.size()) {
		cout << "K je van opsega" << endl;
		exit(-1);
	}
	sortVector(v);
	return v[k - 1];
}

ostream& operator<<(ostream& os, Tree& tree) {
	int size;
	queue<Node*> que;
	Node* curr = tree.root;
	que.push(curr);
	while (true) {
		size = que.size();
		if (size == 0) return os;
		while (size > 0) {
			curr = que.front();
			que.pop();
			for (int i = 0; i <= curr->getSize(); i++) {
				if (curr->getNodes()[i] != nullptr)
					que.push(curr->getNodes()[i]);
			}
			os << *curr << "	";
			size--;
		}
		os << endl;
	}
}
