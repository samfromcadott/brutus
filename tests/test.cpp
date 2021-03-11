#include <cstddef>
#include <iostream>
#include <fstream>
#include <cmath>
#include "../src/grid.hpp"
#include "../src/mesh.hpp"

using namespace Brutus;

int main() {
	Grid g(10, 10, 10);
	for (int x = 0; x < g.sizeX; x++)
	for (int y = 0; y < g.sizeY; y++)
	for (int z = 0; z < g.sizeZ; z++)
		g.setVoxel( x, y, z, sqrt(pow(x-5, 2) + pow(y-5, 2) + pow(z-5, 2)) - 3 );
	// g.setVoxel(0, 0, 0, -1);
	// g.setVoxel(0, 0, 1, 1);
	// g.setVoxel(0, 1, 0, 1);
	// g.setVoxel(0, 1, 1, 1);
	// g.setVoxel(1, 0, 0, 1);
	// g.setVoxel(1, 0, 1, 1);
	// g.setVoxel(1, 1, 0, 1);
	// g.setVoxel(1, 1, 1, 1);

	Mesh m = g.generateMesh();

	std::ofstream file("grid.obj");
	if (file.is_open()) {
		for (int i = 0; i < m.vertex.size(); i++) {
			file << "v " << m.vertex[i].x << " " << m.vertex[i].y << " " << m.vertex[i].z << '\n';

		}

		for (int i = 0; i < m.face.size(); i++) {
			file << "f " << m.face[i].v0+1 << " " << m.face[i].v1+1 << " " << m.face[i].v2+1 << '\n';

		}

		file.close();

	}

	return 0;
}
