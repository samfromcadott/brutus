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

unsigned int Node::width() {
	//Returns the width of the node relative to the width of the root node
	return 0;
}
