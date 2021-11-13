#include "node.h"

string& Node::getKey() {
	return key;
}
string Node::getInfo() {
	return readMyList(info);
}
Node* Node::getLeft() {
	return left;
}
Node* Node::getRight() {
	return right;
}
Node* Node::getParent() {
	return parent;
}
void Node::setLeft(Node* lnode) {
	left = lnode;
}
void Node::setRight(Node* rnode) {
	right = rnode;
}
void Node::setParent(Node* pnode) {
	parent = pnode;
}
void Node::addInfo(string moreInfo) {
	addMyListNode(info, moreInfo);
}
void Node::deleteInfo() {
	freeMyList(info);
}