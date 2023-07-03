Brutus - Marching Cubes Library
==============

Brutus is a header-only library for generating meshes from volumetric data using marching cubes.

Example
--------------

```C++
#include <iostream>
#include <fstream>
#include <brutus.h>

int main() {
	Brutus::Grid grid(1, 1, 1);

	// Sphere properties
	const float radius = 3.0;
	const float cx = 3.5, cy = 3.5, cz = 3.5;

	// Generate a sphere using an SDF
	for (size_t x = 0; x < grid.total_size().x; x++)
	for (size_t y = 0; y < grid.total_size().y; y++)
	for (size_t z = 0; z < grid.total_size().z; z++) {
		float weight = (sqrt( pow(cx-x, 2) + pow(cy-y, 2) + pow(cz-z, 2) ) - radius) * 64;

		// Clamp values
		if (weight > 127) weight = 127;
		if (weight < -128) weight = -128;

		grid(x,y,z).weight = Brutus::VoxelWeight(weight);
	}

	Brutus::Mesh mesh = grid.generate_mesh(0, 0, 0); // Generate a mesh

	// Write to an .obj file
	std::ofstream model_file;
	model_file.open("sphere.obj");

	model_file << "# Test of the Brutus voxel library\n";

	// Vertecies
	for (size_t i = 0; i < mesh.vertex_count * 3; i+=3) {
		model_file << "v "
		<< mesh.vertices[i] << " "
		<< mesh.vertices[i+1] << " "
		<< mesh.vertices[i+2] << '\n';
	}

	// Normals
	for (size_t i = 0; i < mesh.vertex_count * 3; i+=3) {
		model_file << "vn "
		<< mesh.normals[i] << " "
		<< mesh.normals[i+1] << " "
		<< mesh.normals[i+2] << '\n';
	}

	// Faces
	for (size_t i = 0; i < mesh.vertex_count; i+=3) {
		model_file << "f "
		<< i+3 << "//" << i+3 << " " // Switch to CCW face winding
		<< i+2 << "//" << i+2 << " "
		<< i+1 << "//" << i+1 << " "
		<< '\n';
	}

	return 0;
}
```
