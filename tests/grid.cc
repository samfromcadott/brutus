#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <fstream>

#include <brutus/brutus.h>

TEST_CASE("Grid constructor/deconstructor") {
	Brutus::Grid grid(2, 2, 2); // Constructor
	Brutus::Grid grid2; // Default constructor
	grid2 = Brutus::Grid(1,1,3); // Copy assignment
}

TEST_CASE("Access chunk") {
	Brutus::Grid grid(2, 2, 2);

	Brutus::Chunk& chunk = grid(0,0,0);
	chunk(1,1,1).weight = 2;
	CHECK(chunk(1,1,1).weight == 2);
	CHECK(chunk(1,1,2).weight == 0);
}

TEST_CASE("Generate mesh") {
	Brutus::Grid grid(1, 1, 1);

	// Create a sphere
	float radius = 2.0f;

	for (size_t x = 0; x < Brutus::Chunk::size; x++)
	for (size_t y = 0; y < Brutus::Chunk::size; y++)
	for (size_t z = 0; z < Brutus::Chunk::size; z++) {
		float weight = (sqrt( pow(3.5-x, 2) + pow(3.5-y, 2) + pow(3.5-z, 2) ) - radius) * (127/radius);

		// Clamp values
		if (weight > 127) weight = 127;
		if (weight < -128) weight = -128;

		grid(0,0,0)(x,y,z).weight = Brutus::VoxelWeight(weight);
	}

	// Generating the mesh
	Brutus::Mesh mesh = grid.generate_mesh(0, 0, 0);
	CHECK(mesh.face_count == 140);

	// Writing to a file
	std::cout << "Generating obj file for mesh" << '\n';
	std::cout << "Face count: " << mesh.face_count << '\n';

	std::ofstream model_file;
	model_file.open("test.obj");

	model_file << "# Test of the Brutus voxel library\n";
	for (size_t i = 0; i < mesh.vertex_count * 3; i+=3) {
		model_file << "v "
		<< mesh.vertices[i] << " "
		<< mesh.vertices[i+1] << " "
		<< mesh.vertices[i+2] << '\n';
	}

	for (size_t i = 0; i < mesh.vertex_count; i+=3) {
		model_file << "f "
		<< i+1 << " "
		<< i+2 << " "
		<< i+3 << '\n';
	}
}
