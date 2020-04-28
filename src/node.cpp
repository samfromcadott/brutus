#include "node.hpp"

Node::Node(Node* parent, int value, float width, float center[3]) {
	this->parent = parent;
	this->value = value;
	this->width = width;
	this->center[0] = center[0];
	this->center[1] = center[1];
	this->center[2] = center[2];

}

Node::~Node() {

}

void Node::subdivide() {
	for (int i = 0; i < 8; i++) {
		child[i] = new Node(this, value, width/2, center);
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
