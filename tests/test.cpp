#include <cstddef>
#include <iostream>
#include <fstream>
#include "../src/grid.hpp"
#include "../src/mesh.hpp"

using namespace Brutus;

int main() {
	Grid g(2, 2, 2);
	g.setVoxel(0, 0, 0, -1);
	g.setVoxel(0, 0, 1, 1);
	g.setVoxel(0, 1, 0, 1);
	g.setVoxel(0, 1, 1, 1);
	g.setVoxel(1, 0, 0, 1);
	g.setVoxel(1, 0, 1, 1);
	g.setVoxel(1, 1, 0, 1);
	g.setVoxel(1, 1, 1, 1);

	Mesh m = g.generateMesh();

	std::ofstream file("grid.obj");
	if (file.is_open()) {
		for (int i = 0; i < m.vertex.size(); i++) {
			file << "v " << m.vertex[i].x << " " << m.vertex[i].y << " " << m.vertex[i].z << '\n';

		}

		file.close();

	}

	return 0;
}
