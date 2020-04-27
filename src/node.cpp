#include "node.hpp"
#include <limits>

Node::Node() {

}

Node::~Node() {

}

void Node::subdivide() {
	child = new Node[8];

	for (int i = 0; i < 8; i++) {
		child[i].level = level + 1;
		child[i].parent = this;
	}

}

Node* Node::root() {
	//Returns the root node of this octree
	Node* n = parent;

	//Move up the tree while the parent is not null
	while (n) {
		n = n->parent;
	}

	return n;

}

unsigned int Node::width() {
	//Returns the width of the node relative to the width of the root node
	return 0;
}
