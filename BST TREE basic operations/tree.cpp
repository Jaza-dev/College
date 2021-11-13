#include "tree.h"

void printSpace(int n) {
	for (int i = 0; i < n; i++) {
		cout << " ";
	}
}
Tree::Tree(int n) {
	//funkcija pravi stablo na osnovu liste cvorova (stavka 1)
	int i;
	string key, info;
	Node* newNode;
	for (i = 0; i < n; i++) {
		cout << i + 1 << ". rec: ";
		cin >> key;
		cout << "   prevod: ";
		cin >> info;
		newNode = new Node(key, info);
		if (i == 0) {
			root = newNode;
		}
		else {
			addNode(newNode);
		}
	}
}
Tree::Tree(FILE* in) {
	char key[256], info[256];
	short i = 0;
	Node* newNode;
	while(fscanf(in, "%s %s\n", &key, &info) == 2) {
		newNode = new Node(key, info);
		if (!i) {
			root = newNode;
			i++;
		}
		else {
			addNode(newNode);
		}
	}
}
Node* Tree::getRoot() {
	return root;
}
void Tree::addNode(Node* node) {
	//dodaje jedan cvor u stablo
	Node* curr = root;
	while (true) {
		if (curr->getKey() > node->getKey()) {
			if (curr->getLeft() == nullptr) {
				node->setParent(curr);
				curr->setLeft(node);
				break;
			}
			curr = curr->getLeft();
		}
		else if (curr->getKey() < node->getKey()) {
			if (curr->getRight() == nullptr) {
				node->setParent(curr);
				curr->setRight(node);
				break;
			}
			curr = curr->getRight();
		}
		else {	//ako su jednaki, cuvam ih u istom nodu, te ih razdvajam ;
			curr->addInfo(node->getInfo());
			delete node;
			break;
		}
	}
}
Node* Tree::getNode(string k) {
	Node* curr = root;
	while (true) {
		if (curr->getKey() > k) {
			curr = curr->getLeft();
		}
		else if (curr->getKey() < k) {
			curr = curr->getRight();
		}
		else {
			return curr;
		}
		if (curr == nullptr) {
			return nullptr;
		}
	}
}
int Tree::treeHeight() {
	int height = 0, size;
	Que* que = new Que;
	Node* curr = root;
	que->insert(root);
	while (true) {
		size = que->queSize();
		if (size == 0) return height;
		height++;
		while (size > 0) {
			curr = que->remove();
			if (curr->getLeft() != nullptr) {
				que->insert(curr->getLeft());
			}
			if (curr->getRight() != nullptr) {
				que->insert(curr->getRight());
			}
			size--;
		}
	}	
}

//po ugledu na algoritam sa sajta predmeta
void Tree::printTree() {
	if (!root)   return;
	else {
		Que* q = new Que;
		int i, line_len = 62;
		int first_skip = line_len, in_between_skip;

		q->insert(root);
		for (i = 0; i <= this->treeHeight(); i++) {
			int j = 1 << i, k, l;
			in_between_skip = first_skip;
			first_skip = (first_skip - 2) / 2;
			for (k = 0; k < first_skip; k++) cout << ' ';
			for (k = 0; k < j; k++) {
				Node* btn = q->remove();
				if (btn) {
					q->insert(btn->getLeft());
					q->insert(btn->getRight());
				}
				else {
					q->insert(0);
					q->insert(0);
				}
				if (btn)  cout << btn->getKey();// << " - " << btn->getInfo(); ako treba i prevod
				else       cout << "  ";
				for (l = 0; l < in_between_skip; l++) cout << ' ';
			}
			cout << endl;
			cout << endl;
		}
		q->deleteQue();
	}

}
void Tree::deleteTree() {
	Node* curr = root, * parent;
	if (root->getLeft() == nullptr) {
		if (root->getRight() != nullptr) {
			while (curr->getRight() != nullptr) {
				curr = curr->getRight();
			}
			parent = curr->getParent();
		}
	}
	while (true) {
		while (curr->getLeft() != nullptr) {
			curr = curr->getLeft();
		}
		if (curr == root && root->getRight() == nullptr) {
			delete root;
			break;
		}
		parent = curr->getParent();
		if (curr == parent->getLeft())
			parent->setLeft(nullptr);
		else if (curr == parent->getRight())
			parent->setRight(nullptr);
		delete curr;
		curr = parent;
		if (curr == nullptr) break;
		if (parent->getRight() != nullptr) {
			curr = parent->getRight();
		}
		else {
			if (curr == root && root->getRight() == nullptr) {
				delete root;
				break;
			}
			curr = parent->getParent();
			curr->setLeft(nullptr);
			curr->setRight(nullptr);
			delete parent;
		}
	}
}

//po ugledu iz knjige prof. Tomasevica
void Tree::deleteNode(string key) {
	Node* forDelete = getNode(key);
	Node* f, * rp, * s;
	if (forDelete == nullptr) {
		cout << "Kljuc NE POSTOJI u stablu" << endl;
		return;
	}
	Node* parent = forDelete->getParent();
	if (forDelete->getLeft() == nullptr) {
		rp = forDelete->getRight();
	}
	else if (forDelete->getRight() == nullptr) {
		rp = forDelete->getLeft();
	}
	else {
		f = forDelete;
		rp = forDelete->getRight();
		s = rp->getLeft();
		while (s != nullptr) {
			f = rp;
			rp = s;
			s = rp->getLeft();
		}
		if (f != forDelete) {
			f->setLeft(rp->getRight());
			if(rp->getRight() != nullptr)
				rp->getRight()->setParent(f);
			rp->setRight(forDelete->getRight());
			forDelete->getRight()->setParent(rp);
		}
		rp->setLeft(forDelete->getLeft());
		forDelete->getLeft()->setParent(rp);
	}
	if (parent == nullptr) {
		root = rp;
		rp->setParent(nullptr);
	}
	else if (forDelete == parent->getLeft()) {
		parent->setLeft(rp);
		if(rp != nullptr)
			rp->setParent(parent);
	}
	else {
		parent->setRight(rp);
		if(rp != nullptr)
			rp->setParent(parent);
	}
	forDelete->deleteInfo();
	delete forDelete;
	cout << "Kljuc je uspesno obrisan!";
}

void Tree::searchWithPrefix(string prefix) {
	Que* que1 = new Que, *que2 = new Que;
	int count, n = size(prefix);;
	Node* curr = root;
	que1->insert(root);
	while (true) {
		count = que1->queSize();
		if (count == 0) break;
		while (count > 0) {
			curr = que1->remove();
			if (curr->getKey()[0] == prefix[0] && size(curr->getKey()) >= n)
				que2->insert(curr);
			if (curr->getLeft() != nullptr) {
				que1->insert(curr->getLeft());
			}
			if (curr->getRight() != nullptr) {
				que1->insert(curr->getRight());
				
			}
			count--;
		}
	}
	que1->deleteQue();
	count = que2->queSize();
	Node* temp = nullptr;
	if (n == 1) {
		while (count--) {
			temp = que2->remove();
			cout << temp->getKey() << " - " << temp->getInfo() << endl;
		}
		return;
	}
	short test = 0;
	while (count--) {
		test = 0;
		temp = que2->remove();
		for (int i = 1; i < n; i++) {
			if (temp->getKey()[i] != prefix[i]) {
				test = 1;
				break;
			}
		}
		if (test) {
			continue;
		}
		cout << temp->getKey() << " - " << temp->getInfo() << endl;
	}
}

