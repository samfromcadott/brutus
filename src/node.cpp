#include "node.hpp"
#include <cstdarg>
#include <cassert>

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

Node* &Node::operator()(int c...) {
	va_list args;
	va_start(args, f);

	Node* n = this;
	for (int i = 0; i < count; i++) {
		int x = va_arg(args, int); // Index of the next child node
		assert(x >= 0 && x <= 7);
		assert(n->branch != NULL);
		n = n->brach->leaf[x]
	}
	return branch->leaf[i];

}

void Node::subdivide() {
	branch = new Branch;

	for (int i = 0; i < SUBDIVS; i++) {
		branch->leaf[i] = new Node(this, value, width/2, center);
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
