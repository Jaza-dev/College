#include "Node.h"
void Node::sortArray(string* strArr, int size) {
	int i, j;
	for (i = 0; i < size-1; i++) {
		for (j = i+1; j < size; j++) {
			if (strArr[i] > strArr[j]) {
				string temp = strArr[i];
				strArr[i] = strArr[j];
				strArr[j] = temp;
			}
		}
	}
}

void Node::sortNodes(Node** nodes , int size) {
	int i, j;
	for (i = 0; i < size - 1; i++) {
		for (j = i + 1; j < size; j++) {
			if (nodes[i]->getWords()[0] > nodes[j]->getWords()[0]) {
				Node* temp = nodes[i];
				nodes[i] = nodes[j];
				nodes[j] = temp;
			}
		}
	}
}
 
Node::Node(int c): cap(c), words(new string[c]), nodes(new Node*[c+1]){
	int i;
	for( i= 0; i < cap; i++) {
		words[i] = "";
		nodes[i] = nullptr;
	}
	nodes[i] = nullptr;
}
Node::Node(const Node& node) {
	size = node.size, cap = node.cap;
	words = node.words;
	parent = node.parent;
	nodes = node.nodes;
}
Node::~Node() {
	delete[] words;
	delete[] nodes;
}
int Node::getCap() const { return cap; }
int& Node::getSize() { return size; }
string* Node::getWords() { return words; }
Node* Node::getParent() { return parent; }
Node** Node::getNodes() { return nodes; }
void Node::setParent(Node* p) { parent = p; }
bool Node::isFull() const {
	return cap == size;
}

Node* Node::right() {
	Node* rightB = nullptr;
	if (parent != nullptr) {
		for (int i = 0; i < parent->size; i++) {
			if (parent->nodes[i] == this) {
				rightB = parent->nodes[i + 1];
			}
		}
	}
	return rightB;
}
Node* Node::left() {
	Node* leftB = nullptr;
	if (parent != nullptr) {
		for (int i = 1; i <= parent->size; i++) {
			if (parent->nodes[i] == this) {
				leftB = parent->nodes[i - 1];
			}
		}
	}
	return leftB;
}
void Node::putInRight(Node* rightB, string word) {
	int i;
	string fromNode = words[size - 1], fromFather;
	for (i = 0; i < parent->size; i++) {
		if (parent->words[i] > fromNode) {
			fromFather = parent->words[i];
			break;
		}
	}
	if (word < fromNode && word != "") {
		parent->words[i] = fromNode;
		rightB->addWord(fromFather);
		removeWord(fromNode);
		addWord(word);
	}
	else if (word > fromNode && word != "") {
		parent->words[i] = word;
		rightB->addWord(fromFather);
	}
	else if (word == "") {
		parent->words[i] = fromNode;
		rightB->addWord(fromFather);
		removeWord(fromNode);
	}
}
void Node::putInLeft(Node* leftB, string word) {
	int i = 0;
	string fromNode = words[0], fromFather;
	if (parent->size > 1) { //ako ima vise str idem redom dok ne naidjem na prvi veci, znaci onaj pre njega je razdelni
		for (i = 1; i < parent->size; i++) {
			if (parent->words[i] > fromNode) {
				fromFather = parent->words[--i];
				break;
			}
		}
		if (fromFather == "")
			fromFather = parent->words[--i];
	}
	else {//ako postoji samo jedan str njega uzimam
		fromFather = parent->words[0];
	}
	if (word > fromNode && word != "") {
		parent->words[i] = fromNode;
		leftB->addWord(fromFather);
		removeWord(fromNode);
		addWord(word);
	}
	else if (word < fromNode && word != "") {
		parent->words[i] = word;
		leftB->addWord(fromFather);
	}
	else if (word == "") {
		parent->words[i] = fromNode;
		leftB->addWord(fromFather);
		removeWord(fromNode);
	}
}

void Node::rootBreak(string& word, int m, int nodeMax, Node* overload) {
	int i, j;
	string* strArr = new string[cap + 1];
	for (i = 0; i < cap; i++) {
		strArr[i] = words[i];
		words[i] = "";
	}
	strArr[i] = word;
	sortArray(strArr, cap + 1);
	Node* newNode1 = new Node(nodeMax);
	Node* newNode2 = new Node(nodeMax);
	if (overload != nullptr) { //ukoliko je doslo do preloma na nizim nivoioma i poslat je cvor do korena koji je pun
		int mid = (int)ceil((cap + 1) / 2.0), o;
		for (o = 0; o < mid; o++) {
			newNode1->nodes[o] = nodes[o];
			nodes[o]->parent = newNode1;
		}
		for (o = mid; o < cap + 1; o++) {
			newNode2->nodes[o-mid] = nodes[o];
			nodes[o]->parent = newNode2;
		}
		newNode2->nodes[o-mid] = overload;
		overload->parent = newNode2;
	}
	nodes[0] = newNode1;
	newNode1->parent = this;
	nodes[1] = newNode2;
	newNode2->parent = this;
	for (int i = 2; i < cap + 1; i++) {
		nodes[i] = nullptr;
	}
	i = (int)floor(m / 2.0);
	for (j = 0; j < i; j++) {
		newNode1->addWord(strArr[j]);
	}
	this->size = 0;
	addWord(strArr[i]);
	for (j = i+1; j < cap + 1; j++) {
		newNode2->addWord(strArr[j]);
	}
	delete[] strArr;
}
void Node::nodeBreak(string& word, int m, int rootM, int leftSize, int middleSize, int rightSize, Node* overload) {
	Node* rightB, *leftB;
	if ((rightB=right()) != nullptr) {
		int i, j, parentNodePos = 0;
		Node* newNode = new Node(m);
		newNode->parent = parent;
		if (overload != nullptr) {
			if (rightB->getSize() < m) {
				this->putInRight(rightB, word);
				Node* fromLeftNode = nodes[size];//prevezujem sinove tako da se kranji desni sin veze u desnog brata kao najdesnji
				for (i = rightB->size; i > 0; i--) {
					rightB->nodes[i] = rightB->nodes[i - 1];
				}
				nodes[size] = overload;
				overload->parent = this;
				rightB->nodes[0] = fromLeftNode;
				fromLeftNode->parent = rightB;
				return;
			}
			else {
				for (i = 0; i < middleSize;i++) {
					newNode->nodes[i] = nodes[leftSize+i+1];
					newNode->nodes[i]->parent = newNode;
					nodes[leftSize + i + 1] = nullptr;
				}
				newNode->nodes[middleSize] = overload;
				overload->parent = overload;
			}
		}
		string* strArr = new string[m * 2 + 2];
		for (i = 0; i < m; i++) {
			strArr[i] = this->getWords()[i];
			words[i] = "";
		}
		size = 0;
		for (i = 0; i < m; i++) {
			strArr[m + i] = rightB->getWords()[i];
			rightB->words[i] = "";
		}
		rightB->size = 0;
		strArr[2 * m] = word;
		for (i = 0; i < parent->getSize(); i++) {
			if (parent->getNodes()[i] == this) {
				parentNodePos = i;
				strArr[2 * m + 1] = parent->getWords()[i];
				parent->removeWord(strArr[2 * m + 1]);
				break;
			}
		}
		sortArray(strArr, 2 * m + 2);
		for (i = 0; i < leftSize; i++) {
			this->addWord(strArr[i]);
		}
		parent->addWord(strArr[i++]);
		for (j = i; j < i+middleSize; j++) {
			newNode->addWord(strArr[j]);
		} 
		parent->getNodes()[parentNodePos + 1] = newNode;
		if (!parent->addWord(strArr[j])) {
			if (parent->parent == nullptr) {
				parent->rootBreak(strArr[j], rootM, m, rightB);
			}
			else {
				parent->nodeBreak(strArr[j], m, rootM, leftSize, middleSize, rightSize, rightB);
			}
		}
		else {
			parent->getNodes()[parentNodePos + 2] = rightB;
			rightB->parent = parent;
		}
		j++;
		for (i = j; i < j + rightSize; i++) {
			rightB->addWord(strArr[i]);
		}
	}
	else {
		leftB = left();
		int i, j, parentNodePos = 0;
		Node* newNode = new Node(m);
		newNode->parent = parent;
		if (overload != nullptr) {
			if (leftB->getSize() < m) {
				this->putInLeft(leftB, word);
				Node* fromRightNode = nodes[0];//prevezujem sinove tako da se kranji levi sin veze u levog brata kao najdesnji
				for (i = 0; i < size; i++) {
					nodes[i] = nodes[i + 1];
				}
				nodes[i] = overload;
				overload->parent = this;
				leftB->nodes[size] = fromRightNode;
				fromRightNode->parent = leftB;
				return;
			}
			else {
				Node* fromRightNode = nodes[0];
				for (i = 0; i < size; i++) {
					nodes[i] = nodes[i + 1];
				}
				nodes[i] = overload;
				overload->parent = this;
				for (i = leftSize+1; i < leftSize+middleSize+1; i++) {
					newNode->nodes[i-leftSize-1] = leftB->nodes[i];
					newNode->nodes[i - leftSize - 1]->parent = newNode;
					leftB->nodes[i] = nullptr;
				}
				newNode->nodes[i - leftSize-1] = fromRightNode;
				fromRightNode->parent = newNode;
			}
		}
		string* strArr = new string[m * 2 + 2];
		for (i = 0; i < m; i++) {
			strArr[i] = this->getWords()[i];
			words[i] = "";
		}
		size = 0;
		for (i = 0; i < m; i++) {
			strArr[m + i] = leftB->getWords()[i];
			leftB->words[i] = "";
		}
		leftB->size = 0;
		strArr[2 * m] = word;
		for (i = 0; i < parent->getSize(); i++) {
			if (parent->getNodes()[i] == this) {
				parentNodePos = i;
				strArr[2 * m + 1] = parent->getWords()[i];
				parent->removeWord(strArr[2 * m + 1]);
				break;
			}
			if (i == parent->getSize()-1 && parent->getNodes()[i+1] == this) {
				parentNodePos = i;
				strArr[2 * m + 1] = parent->getWords()[i];
				parent->removeWord(strArr[2 * m + 1]);
				break;
			}
		}
		sortArray(strArr, 2 * m + 2);
		for (i = 0; i < leftSize; i++) {
			leftB->addWord(strArr[i]);
		}
		parent->addWord(strArr[i++]);
		for (j = i; j < i + middleSize; j++) {
			newNode->addWord(strArr[j]);
		}
		parent->getNodes()[parentNodePos + 1] = newNode;
		if (!parent->addWord(strArr[j])) {
			if (parent->parent == nullptr) {
				parent->rootBreak(strArr[j], rootM, m, this);
			}
			else {
				parent->nodeBreak(strArr[j], m, rootM, leftSize, middleSize, rightSize, this);
			}
		}
		else {
			parent->getNodes()[parentNodePos + 2] = this;
		}
		j++;
		for (i = j; i < j + rightSize; i++) {
			this->addWord(strArr[i]);
		}
	}
}

bool Node::searchWord(string& word) const {
	if (getSearchIndex(word) >= 0) return true;
	return false;
}

int Node::getSearchIndex(string& word)const {
	for (int i = 0; i < size; i++) {
		if (words[i] == word) return i;
	}
	return -1;
}

bool Node::addWord(string& word) {
	if (!searchWord(word) && size < cap) {
		int i, j;
		for (i = 0; i < size && words[i] < word; i++);
		for (j = size++; j > i; j--) {
			words[j] = words[j - 1];
		}
		words[i] = word;
		return true;
	}
	return false;
}

bool Node::removeWord(string& word) {
	int indx, i;
	if ((indx = getSearchIndex(word)) >= 0) {
		for (i = indx; i < size - 1; i++) {
			words[i] = words[i + 1];
		}
		words[i] = "";
		size--;
		return true;
	}
	return false;
}

Node* Node::switchWithSucc(string& word) { //this je srednji cvor
	int i;
	queue<Node*> que;
	Node* curr = this; //u thisu je word
	for (i = 0; i < curr->getSize(); i++) {
		if (curr->getWords()[i] == word) {
			curr = curr->getNodes()[i + 1];
			break;
		}
	}
	que.push(curr);
	while (true) {
		curr = que.front();
		que.pop();
		if (curr->nodes[0] == nullptr) break;
		que.push(curr->getNodes()[0]);
	}
	string temp = curr->getWords()[0];
	curr->removeWord(temp);
	curr->addWord(word);
	this->removeWord(word);
	this->addWord(temp);
	return curr;
}

Node* Node::threeToTwo(Node* rightB, Node* leftB, Node* root) {
	int nodeMin = leftB->size , i= 0, j = 0;
	int nodeMax = leftB->cap, arrSize = 3 * nodeMin - 1 + 2, nodesSize = 3 * (nodeMin + 1) - 1;
	string* strArr = new string[arrSize];
	Node** strNodes = new Node*[nodesSize]; //cuvam sve pokazivace na sinove
	for (i = 0; i < nodeMin; i++) {
		strArr[i] = leftB->getWords()[i];
		strNodes[i] = leftB->getNodes()[i];
		leftB->getNodes()[i] = nullptr;
		leftB->getWords()[i] = "";
	}
	leftB->size = 0;
	strNodes[i] = leftB->getNodes()[i];
	leftB->getNodes()[i] = nullptr;
	for (j = i; j < nodeMin + i - 1; j++) {
		strArr[j] = this->getWords()[j - i];
		strNodes[j+1] = this->getNodes()[j-i];
		this->getNodes()[j - i] = nullptr;
		this->getWords()[j - i] = "";
	}
	this->size = 0;
	strNodes[j+1] = this->getNodes()[j - i];
	this->getNodes()[j - i] = nullptr;
	for (i = j; i < nodeMin + j; i++) {
		strArr[i] = rightB->getWords()[i - j];
		strNodes[i+2] = rightB->getNodes()[i - j];
		rightB->getNodes()[i - j] = nullptr;
		rightB->getWords()[i - j] = "";
	}
	rightB->size = 0;
	strNodes[i+2] = rightB->getNodes()[i - j];
	rightB->getNodes()[i - j] = nullptr;
	for (j = i; j < parent->size + i; j++) {
		if (parent->getNodes()[j - i] == leftB) {
			strArr[i] = parent->getWords()[j - i];
			parent->getWords()[j - i] = "";
			strArr[++i] = parent->getWords()[j - i + 2];
			parent->getWords()[j - i + 2] = "";
			break;
		}
	}
	sortArray(strArr, arrSize);
	if(strNodes[0] != nullptr)
		sortNodes(strNodes, nodesSize);
	//leftB izbacujem i brisem a koristim this i rightB za 2 nova noda pokazivace mrdam samo ulevo
	j = j - i + 1;//pozicija leftB u parentu
	for (i = j; i< parent->size; i++) { //izbacujem leftB
		parent->getNodes()[i] = parent->getNodes()[i + 1];
	}
	parent->size -= 2;
	int mid = (int)floor(arrSize / 2);
	for (i = 0; i < mid; i++) {
		this->addWord(strArr[i]);
		this->getNodes()[i] = strNodes[i];
		if(this->getNodes()[i] != nullptr)
			this->getNodes()[i]->parent = this;
	}
	this->getNodes()[i] = strNodes[i];
	if (this->getNodes()[i] != nullptr)
		this->getNodes()[i]->parent = this;
	parent->addWord(strArr[i++]);
	for (j = i; j < nodeMax+i; j++) {
		rightB->addWord(strArr[j]);
		rightB->getNodes()[j-i] = strNodes[j];
		if (rightB->getNodes()[j-i] != nullptr)
			rightB->getNodes()[j-i]->parent = rightB;
	}
	rightB->getNodes()[j-i] = strNodes[j];
	if (rightB->getNodes()[j-i] != nullptr)
		rightB->getNodes()[j-i]->parent = rightB;
	if (parent->size < nodeMin) {
		Node* node = parent, *rightB = nullptr, *leftB = nullptr, * leftLeftB = nullptr, *rightRightB = nullptr;
		if ((rightB = node->right()) != nullptr && rightB->getSize() > nodeMin) {
			rightB->putInLeft(node);
			return root;
		}
		else if ((leftB = node->left()) != nullptr && leftB->getSize() > nodeMin) {
			leftB->putInRight(node);
			return root;
		}
		else if (rightB != nullptr && (rightRightB = rightB->right()) != nullptr && rightRightB->getSize() > nodeMin) {
			rightRightB->putInLeft(rightB);
			rightB->putInLeft(node);
			return root;
		}
		else if (leftB != nullptr && (leftLeftB = leftB->left()) != nullptr && leftLeftB->getSize() > nodeMin) {
			leftLeftB->putInRight(leftB);
			leftB->putInRight(node);
			return root;
		}
		else {
			if (rightB != nullptr && leftB != nullptr) {
				return node->threeToTwo(rightB, leftB, root);
			}
			else if (leftB == nullptr && rightB != nullptr && rightRightB != nullptr) {
				return node->threeToTwoR(rightB, rightRightB, root);
			}
			else if (rightB == nullptr && leftB != nullptr && leftLeftB != nullptr) {
				return node->threeToTwoL(leftB, leftLeftB, root);
			}
			else if (leftB == nullptr && rightRightB == nullptr && rightB != nullptr) {
				return node->twoToOneR(rightB, root);
			}
			else if (rightB == nullptr && leftLeftB == nullptr && leftB != nullptr) {
				return node->twoToOneL(leftB, 0, root);
			}
		}
	}
	return root;
}

Node* Node::threeToTwoR(Node* rightB, Node* rightRithtB, Node* root) { //this je najlevlji cvor
	int nodeMin = rightB->size, i = 0, j = 0;
	int nodeMax = this->cap, arrSize = 3 * nodeMin - 1 + 2, nodesSize = 3 * (nodeMin + 1) - 1;
	string* strArr = new string[arrSize];
	Node** strNodes = new Node * [nodesSize]; //cuvam sve pokazivace na sinove
	for (i = 0; i < nodeMin; i++) {
		strArr[i] = rightB->getWords()[i];
		strNodes[i] = rightB->getNodes()[i];
		rightB->getNodes()[i] = nullptr;
		rightB->getWords()[i] = "";
	}
	rightB->size = 0;
	strNodes[i] = rightB->getNodes()[i];
	rightB->getNodes()[i] = nullptr;
	for (j = i; j < nodeMin + i - 1; j++) {
		strArr[j] = this->getWords()[j - i];
		strNodes[j + 1] = this->getNodes()[j - i];
		this->getNodes()[j - i] = nullptr;
		this->getWords()[j - i] = "";
	}
	this->size = 0;
	strNodes[j + 1] = this->getNodes()[j - i];
	this->getNodes()[j - i] = nullptr;
	for (i = j; i < nodeMin + j; i++) {
		strArr[i] = rightRithtB->getWords()[i - j];
		strNodes[i + 2] = rightRithtB->getNodes()[i - j];
		rightRithtB->getNodes()[i - j] = nullptr;
		rightRithtB->getWords()[i - j] = "";
	}
	rightRithtB->size = 0;
	strNodes[i + 2] = rightRithtB->getNodes()[i - j];
	rightRithtB->getNodes()[i - j] = nullptr;
	for (j = i; j < parent->size + i; j++) {
		if (parent->getNodes()[j - i] == this) {
			strArr[i] = parent->getWords()[j - i];
			parent->getWords()[j - i] = "";
			strArr[++i] = parent->getWords()[j - i + 2];
			parent->getWords()[j - i + 2] = "";
			break;
		}
	}
	sortArray(strArr, arrSize);
	if(strNodes[0] != nullptr)
		sortNodes(strNodes, nodesSize);
	//this izbacujem i brisem a koristim rightB i rightRightB za 2 nova noda pokazivace mrdam samo ulevo
	j = j - i + 1;//pozicija this u parentu
	for (i = j; i < parent->size; i++) { //izbacujem this
		parent->getNodes()[i] = parent->getNodes()[i + 1];
	}
	parent->size -= 2;
	int mid = (int)floor(arrSize / 2);
	for (i = 0; i < mid; i++) {
		rightB->addWord(strArr[i]);
		rightB->getNodes()[i] = strNodes[i];
		if (rightB->getNodes()[i] != nullptr)
			rightB->getNodes()[i]->parent = rightB;
	}
	rightB->getNodes()[i] = strNodes[i];
	if (rightB->getNodes()[i] != nullptr)
		rightB->getNodes()[i]->parent = rightB;
	parent->addWord(strArr[i++]);
	for (j = i; j < nodeMax + i; j++) {
		rightRithtB->addWord(strArr[j]);
		rightRithtB->getNodes()[j - i] = strNodes[j];
		if (rightRithtB->getNodes()[j - i] != nullptr)
			rightRithtB->getNodes()[j - i]->parent = rightRithtB;
	}
	rightRithtB->getNodes()[j - i] = strNodes[j];
	if (rightRithtB->getNodes()[j - i] != nullptr)
		rightRithtB->getNodes()[j - i]->parent = rightRithtB;
	if (parent->size < nodeMin) {
		Node* node = parent, * rightB = nullptr, * leftB = nullptr, * leftLeftB = nullptr, * rightRightB = nullptr;
		if ((rightB = node->right()) != nullptr && rightB->getSize() > nodeMin) {
			rightB->putInLeft(node);
			return root;
		}
		else if ((leftB = node->left()) != nullptr && leftB->getSize() > nodeMin) {
			leftB->putInRight(node);
			return root;
		}
		else if (rightB != nullptr && (rightRightB = rightB->right()) != nullptr && rightRightB->getSize() > nodeMin) {
			rightRightB->putInLeft(rightB);
			rightB->putInLeft(node);
			return root;
		}
		else if (leftB != nullptr && (leftLeftB = leftB->left()) != nullptr && leftLeftB->getSize() > nodeMin) {
			leftLeftB->putInRight(leftB);
			leftB->putInRight(node);
			return root;
		}
		else {
			if (rightB != nullptr && leftB != nullptr) {
				return node->threeToTwo(rightB, leftB, root);
			}
			else if (leftB == nullptr && rightB != nullptr && rightRightB != nullptr) {
				return node->threeToTwoR(rightB, rightRightB, root);
			}
			else if (rightB == nullptr && leftB != nullptr && leftLeftB != nullptr) {
				return node->threeToTwoL(leftB, leftLeftB, root);
			}
			else if (leftB == nullptr && rightRightB == nullptr && rightB != nullptr) {
				return node->twoToOneR(rightB, root);
			}
			else if (rightB == nullptr && leftLeftB == nullptr && leftB != nullptr) {
				return node->twoToOneL(leftB, 0, root); 
			}
		}
	}
	return root;
}

Node* Node::threeToTwoL(Node* leftB, Node* leftLeftB, Node* root){ //this
	int nodeMin = leftB->size, i = 0, j = 0;
	int nodeMax = leftB->cap, arrSize = 3 * nodeMin - 1 + 2, nodesSize = 3 * (nodeMin + 1) - 1;
	string* strArr = new string[arrSize];
	Node** strNodes = new Node * [nodesSize]; //cuvam sve pokazivace na sinove
	for (i = 0; i < nodeMin; i++) {
		strArr[i] = leftB->getWords()[i];
		strNodes[i] = leftB->getNodes()[i];
		leftB->getNodes()[i] = nullptr;
		leftB->getWords()[i] = "";
	}
	leftB->size = 0;
	strNodes[i] = leftB->getNodes()[i];
	leftB->getNodes()[i] = nullptr;
	for (j = i; j < nodeMin + i - 1; j++) {
		strArr[j] = this->getWords()[j - i];
		strNodes[j + 1] = this->getNodes()[j - i];
		this->getNodes()[j - i] = nullptr;
		this->getWords()[j - i] = "";
	}
	this->size = 0;
	strNodes[j + 1] = this->getNodes()[j - i];
	this->getNodes()[j - i] = nullptr;
	for (i = j; i < nodeMin + j; i++) {
		strArr[i] = leftLeftB->getWords()[i - j];
		strNodes[i + 2] = leftLeftB->getNodes()[i - j];
		leftLeftB->getNodes()[i - j] = nullptr;
		leftLeftB->getWords()[i - j] = "";
	}
	leftLeftB->size = 0;
	strNodes[i + 2] = leftLeftB->getNodes()[i - j];
	leftLeftB->getNodes()[i - j] = nullptr;
	for (j = i; j < parent->size + i; j++) {
		if (parent->getNodes()[j - i] == leftLeftB) {
			strArr[i] = parent->getWords()[j - i];
			parent->getWords()[j - i] = "";
			strArr[++i] = parent->getWords()[j - i + 2];
			parent->getWords()[j - i + 2] = "";
			break;
		}
	}
	sortArray(strArr, arrSize);
	if (strNodes[0] != nullptr)
		sortNodes(strNodes, nodesSize);
	//leftLeftB izbacujem i brisem a koristim this i leftB za 2 nova noda pokazivace mrdam samo ulevo
	j = j - i + 1;//pozicija leftLeftB u parentu
	for (i = j; i < parent->size; i++) { //izbacujem leftB
		parent->getNodes()[i] = parent->getNodes()[i + 1];
	}
	parent->size -= 2;
	int mid = (int)floor(arrSize / 2);
	for (i = 0; i < mid; i++) {
		leftB->addWord(strArr[i]);
		leftB->getNodes()[i] = strNodes[i];
		if (leftB->getNodes()[i] != nullptr)
			leftB->getNodes()[i]->parent = leftB;
	}
	leftB->getNodes()[i] = strNodes[i];
	if (leftB->getNodes()[i] != nullptr)
		leftB->getNodes()[i]->parent = leftB;
	parent->addWord(strArr[i++]);
	for (j = i; j < nodeMax + i; j++) {
		this->addWord(strArr[j]);
		this->getNodes()[j - i] = strNodes[j];
		if (this->getNodes()[j - i] != nullptr)
			this->getNodes()[j - i]->parent = this;
	}
	this->getNodes()[j - i] = strNodes[j];
	if (this->getNodes()[j - i] != nullptr)
		this->getNodes()[j - i]->parent = this;
	if (parent->size < nodeMin) {
		Node* node = parent, * rightB = nullptr, * leftB = nullptr, * leftLeftB = nullptr, * rightRightB = nullptr;
		if ((rightB = node->right()) != nullptr && rightB->getSize() > nodeMin) {
			rightB->putInLeft(node);
			return root;
		}
		else if ((leftB = node->left()) != nullptr && leftB->getSize() > nodeMin) {
			leftB->putInRight(node);
			return root;
		}
		else if (rightB != nullptr && (rightRightB = rightB->right()) != nullptr && rightRightB->getSize() > nodeMin) {
			rightRightB->putInLeft(rightB);
			rightB->putInLeft(node);
			return root;
		}
		else if (leftB != nullptr && (leftLeftB = leftB->left()) != nullptr && leftLeftB->getSize() > nodeMin) {
			leftLeftB->putInRight(leftB);
			leftB->putInRight(node);
			return root;
		}
		else {
			if (rightB != nullptr && leftB != nullptr) {
				return node->threeToTwo(rightB, leftB, root);
			}
			else if (leftB == nullptr && rightB != nullptr && rightRightB != nullptr) {
				return node->threeToTwoR(rightB, rightRightB, root);
			}
			else if (rightB == nullptr && leftB != nullptr && leftLeftB != nullptr) {
				return node->threeToTwoL(leftB, leftLeftB, root);
			}
			else if (leftB == nullptr && rightRightB == nullptr && rightB != nullptr) {
				return node->twoToOneR(rightB, root);
			}
			else if (rightB == nullptr && leftLeftB == nullptr && leftB != nullptr) {
				return node->twoToOneL(leftB, 0, root);
			}
		}
	}
	return root;
}

Node* Node::twoToOneR(Node* rightB, Node* root) {
	int nodeMin = rightB->size, i = 0, j = 0;
	int nodeMax = rightB->cap, arrSize = 2 * nodeMin, nodesSize = 2 * (nodeMin + 1) - 1;
	string* strArr = new string[arrSize];
	Node** strNodes = new Node * [nodesSize]; //cuvam sve pokazivace na sinove
	for (i = 0; i < nodeMin; i++) {
		strArr[i] = rightB->getWords()[i];
		strNodes[i] = rightB->getNodes()[i];
		rightB->getNodes()[i] = nullptr;
		rightB->getWords()[i] = "";
	}
	rightB->size = 0;
	strNodes[i] = rightB->getNodes()[i];
	rightB->getNodes()[i] = nullptr;
	for (j = i; j < nodeMin + i - 1; j++) {
		strArr[j] = this->getWords()[j - i];
		strNodes[j + 1] = this->getNodes()[j - i];
		this->getNodes()[j - i] = nullptr;
		this->getWords()[j - i] = "";
	}
	this->size = 0;
	strNodes[j + 1] = this->getNodes()[j - i];
	this->getNodes()[j - i] = nullptr;
	for (i = j; i < parent->size + j; i++) {
		if (parent->getNodes()[i - j] == this) {
			strArr[j] = parent->getWords()[i - j];
			parent->getWords()[i - j] = "";
			break;
		}
	}
	sortArray(strArr, arrSize);
	if (strNodes[0] != nullptr)
		sortNodes(strNodes, nodesSize);
	//this izbacujem i brisem a koristim rightB za 1 novi node pokazivace mrdam samo ulevo
	i = i - j;//pozicija this u parentu
	for (j = i; j < parent->size; j++) { //izbacujem this
		parent->getNodes()[j] = parent->getNodes()[j + 1];
	}
	parent->size --;
	for (i = 0; i < arrSize; i++) {
		rightB->addWord(strArr[i]);
		rightB->getNodes()[i] = strNodes[i];
		if (rightB->getNodes()[i] != nullptr)
			rightB->getNodes()[i]->parent = rightB;
	}
	rightB->getNodes()[i] = strNodes[i];
	if (rightB->getNodes()[i] != nullptr)
		rightB->getNodes()[i]->parent = rightB;
	if (rightB->parent->size < nodeMin) {
		Node* node = rightB->parent, * rightBB = nullptr, * leftB = nullptr, * leftLeftB = nullptr, * rightRightB = nullptr;
		if (node->parent == nullptr) {
			rightB->parent = nullptr;
			return rightB;
		}
		if ((rightBB = node->right()) != nullptr && rightBB->getSize() > nodeMin) {
			rightBB->putInLeft(node);
			return root;
		}
		else if ((leftB = node->left()) != nullptr && leftB->getSize() > nodeMin) {
			leftB->putInRight(node);
			return root;
		}
		else if (rightBB != nullptr && (rightRightB = rightBB->right()) != nullptr && rightRightB->getSize() > nodeMin) {
			rightRightB->putInLeft(rightBB);
			rightBB->putInLeft(node);
			return root;
		}
		else if (leftB != nullptr && (leftLeftB = leftB->left()) != nullptr && leftLeftB->getSize() > nodeMin) {
			leftLeftB->putInRight(leftB);
			leftB->putInRight(node);
			return root;
		}
		else {
			if (rightBB != nullptr && leftB != nullptr) {
				return node->threeToTwo(rightBB, leftB, root);
			}
			else if (leftB == nullptr && rightBB != nullptr && rightRightB != nullptr) {
				return node->threeToTwoR(rightBB, rightRightB, root);
			}
			else if (rightBB == nullptr && leftB != nullptr && leftLeftB != nullptr) {
				return node->threeToTwoL(leftB, leftLeftB, root);
			}
			else if (leftB == nullptr && rightRightB == nullptr && rightBB != nullptr) {
				return node->twoToOneR(rightBB, root); 
			}
			else if (rightBB == nullptr && leftLeftB == nullptr && leftB != nullptr) {
				return node->twoToOneL(leftB, 0, root);
			}
		}
	}
	return root;
}

Node* Node::twoToOneL(Node* leftB, int k, Node* root) {
	int nodeMin = leftB->size, i = 0, j = 0;
	int nodeMax = leftB->cap, arrSize = 2 * nodeMin, nodesSize = 2 * (nodeMin + 1) - 1;
	string* strArr = new string[arrSize];
	Node** strNodes = new Node * [nodesSize]; //cuvam sve pokazivace na sinove
	for (i = 0; i < nodeMin; i++) {
		strArr[i] = leftB->getWords()[i];
		strNodes[i] = leftB->getNodes()[i];
		leftB->getNodes()[i] = nullptr;
		leftB->getWords()[i] = "";
	}
	leftB->size = 0;
	strNodes[i] = leftB->getNodes()[i];
	leftB->getNodes()[i] = nullptr;
	for (j = i; j < nodeMin + i - 1; j++) {
		strArr[j] = this->getWords()[j - i];
		strNodes[j + 1] = this->getNodes()[j - i];
		this->getNodes()[j - i] = nullptr;
		this->getWords()[j - i] = "";
	}
	this->size = 0;
	strNodes[j + 1] = this->getNodes()[j - i];
	this->getNodes()[j - i] = nullptr;
	for (i = j; i < parent->size + j; i++) {
		if (parent->getNodes()[i - j] == leftB) {
			strArr[j] = parent->getWords()[i - j];
			parent->getWords()[i - j] = "";
			break;
		}
	}
	sortArray(strArr, arrSize);
	if (strNodes[0] != nullptr)
		sortNodes(strNodes, nodesSize);
	//leftB izbacujem i brisem a koristim this za 1 novi node pokazivace mrdam samo ulevo
	i = i - j;//pozicija leftB u parentu
	for (j = i; j < parent->size; j++) { //izbacujem leftB
		parent->getNodes()[j] = parent->getNodes()[j + 1];
		parent->getNodes()[j + 1] = nullptr;
	}
	parent->size--;
	for (i = 0; i < arrSize; i++) {
		this->addWord(strArr[i]);
		this->getNodes()[i] = strNodes[i];
		if (this->getNodes()[i] != nullptr)
			this->getNodes()[i]->parent = this;
	}
	this->getNodes()[i] = strNodes[i];
	if (this->getNodes()[i] != nullptr)
		this->getNodes()[i]->parent = this;
	if (parent->size < nodeMin) {
		Node* node = parent, * rightB = nullptr, * leftB = nullptr, * leftLeftB = nullptr, * rightRightB = nullptr;
		if (node->parent == nullptr) {
			this->parent = nullptr;
			return this;
		}
		if ((rightB = node->right()) != nullptr && rightB->getSize() > nodeMin) {
			rightB->putInLeft(node);
			return root;
		}
		else if ((leftB = node->left()) != nullptr && leftB->getSize() > nodeMin) {
			leftB->putInRight(node);
			return root;
		}
		else if (rightB != nullptr && (rightRightB = rightB->right()) != nullptr && rightRightB->getSize() > nodeMin) {
			rightRightB->putInLeft(rightB);
			rightB->putInLeft(node);
			return root;
		}
		else if (leftB != nullptr && (leftLeftB = leftB->left()) != nullptr && leftLeftB->getSize() > nodeMin) {
			leftLeftB->putInRight(leftB);
			leftB->putInRight(node);
			return root;
		}
		else {
			if (rightB != nullptr && leftB != nullptr) {
				return node->threeToTwo(rightB, leftB, root);
			}
			else if (leftB == nullptr && rightB != nullptr && rightRightB != nullptr) {
				return node->threeToTwoR(rightB, rightRightB, root);
			}
			else if (rightB == nullptr && leftB != nullptr && leftLeftB != nullptr) {
				return node->threeToTwoL(leftB, leftLeftB, root);
			}
			else if (leftB == nullptr && rightRightB == nullptr && rightB != nullptr) {
				return node->twoToOneR(rightB, root);
			}
			else if (rightB == nullptr && leftLeftB == nullptr && leftB != nullptr) {
				return node->twoToOneL(leftB, 0, root);
			}
		}
	}
	return root;
}

ostream& operator<<(ostream& os, Node& node) {
	int i;
	for (i = 0; i < node.size - 1; i++) {
		os << node.words[i] << "|";
	}
	return os << node.words[i];
}