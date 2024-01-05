Brutus - Marching Cubes Library
==============

Brutus is a header-only library for generating meshes from volumetric data using marching cubes.

Features
--------------

* Surface normal generation
* Compile-time option to change `Chunk` size (`BRUTUS_CHUNK_SIZE`)
* Store additional data in voxels (such as terrain type)
* C++ 17
* No dependencies beyond the standard library
* Header-only
* Public domain license

### Planned Features

* Texture coordinate generation
* 3D editor example program
* Single file version

Example
--------------

```C++
#include <iostream>
#include <fstream>
#include <algorithm>
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
		int weight = (sqrt( pow(cx-x, 2) + pow(cy-y, 2) + pow(cz-z, 2) ) - radius) * 64;
		weight = std::clamp(weight, -128, 127); // Clamp values

		grid(x,y,z).weight = static_cast<Brutus::VoxelWeight>(weight);
	}

	Brutus::Mesh mesh = grid.generate_mesh(0, 0, 0); // Generate a mesh

	// Write to an .obj file
	std::ofstream model_file;
	model_file.open("sphere.obj");

	model_file << "# Test of the Brutus voxel library\n";

	// Vertices
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
		<< i+1 << "//" << i+1 << " " // Switch to CCW face winding
		<< i+2 << "//" << i+2 << " "
		<< i+3 << "//" << i+3 << '\n';
	}

	return 0;
}
```
