#include <cstddef>
#include <iostream>
#include "node.hpp"

int main() {
	float c[] = {0.0, 0.0, 0.0};
	Node root(NULL, 1, 1.0, c);

	std::cout << "Size of short: " << sizeof(short) << '\n';
	std::cout << "Size of int: " << sizeof(int) << '\n';
	std::cout << "Size of Node: " << sizeof(Node) << '\n';
	root.subdivide();

	std::cout << "Level of root node: " << root.level() << '\n';
	// std::cout << "Level of its children: " << root[1]->level() << '\n';
	// root[1]->value = 5;
	// std::cout << "Value of root[1]: " << root[1]->value << '\n';
	// root[1]->subdivide();
	// std::cout << "Level of its children: " << *(root[1])[0]->level() << '\n';
	// std::cout << "Level of the parent of its children: " << root.child[1]->root()->level() << '\n';
	// root.child[1]->subdivide();
	// std::cout << "Another level deep: " << root.child[1]->child[0]->level() << '\n';

	return 0;
}
