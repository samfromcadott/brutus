#include "node.hpp"
#include <limits>

Node::Node() {

}

Node::~Node() {

}

void Node::subdivide() {
	for (int i = 0; i < 8; i++) {
		child[i] = new Node;
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

int Node::level() {
	//Returns the root node of this octree
	Node* n = parent;
	int level = 0;

	//Move up the tree while the parent is not null
	while (n) {
		n = n->parent;
		level++;
	}

	return level;

}
