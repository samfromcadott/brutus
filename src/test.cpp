#include <cstddef>
#include <iostream>
#include "voxel.hpp"
#include "vertex.hpp"
#include "octree.hpp"

int main() {
	Octree graph;
	graph({}).value = 2.0;
	graph.subdivide({});
	graph({1}).value = -5.0;

	graph.subdivide({0});
	graph({0, 2}).value = 6.0;

	std::cout << graph({}).value << '\n';
	std::cout << graph({1}).value << '\n';
	std::cout << graph({0, 2}).value << '\n';

	return 0;
}
