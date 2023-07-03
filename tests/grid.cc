#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <fstream>

#include <brutus/brutus.h>

TEST_CASE("Grid constructor/deconstructor") {
	Brutus::Grid grid(2, 2, 2); // Constructor
	Brutus::Grid grid2; // Default constructor
}

TEST_CASE("Copy assignment") {
	Brutus::Grid grid;
	grid = Brutus::Grid(1,1,3);
}

TEST_CASE("Set voxel weight") {
	Brutus::Grid grid(2, 2, 2);

	grid(1,1,1).weight = 2;
	CHECK(grid(1,1,1).weight == 2);
}

void generate_sphere(Brutus::Grid& grid, float radius, float cx, float cy, float cz) {
	for (size_t x = 0; x < Brutus::Chunk::size * 2; x++)
	for (size_t y = 0; y < Brutus::Chunk::size * 2; y++)
	for (size_t z = 0; z < Brutus::Chunk::size * 2; z++) {
		float weight = (sqrt( pow(cx-x, 2) + pow(cy-y, 2) + pow(cz-z, 2) ) - radius) * 64;

		// Clamp values
		if (weight > 127) weight = 127;
		if (weight < -128) weight = -128;

		grid(x,y,z).weight = Brutus::VoxelWeight(weight);
	}
}

void write_model(Brutus::Mesh& mesh, std::string filename) {
	std::ofstream model_file;
	model_file.open(filename);

	model_file << "# Test of the Brutus voxel library\n";
	for (size_t i = 0; i < mesh.vertex_count * 3; i+=3) {
		model_file << "v "
		<< mesh.vertices[i] << " "
		<< mesh.vertices[i+1] << " "
		<< mesh.vertices[i+2] << '\n';
	}

	for (size_t i = 0; i < mesh.vertex_count * 3; i+=3) {
		model_file << "vn "
		<< mesh.normals[i] << " "
		<< mesh.normals[i+1] << " "
		<< mesh.normals[i+2] << '\n';
	}

	// for (size_t i = 0; i < mesh.tex_coord_count * 2; i+=2) {
	// 	model_file << "vt "
	// 	<< mesh.tex_coords[i] << " "
	// 	<< mesh.tex_coords[i+1] << "\n";
	// }

	for (size_t i = 0; i < mesh.vertex_count; i+=3) {
		model_file << "f "
		<< i+3 << "//" << i+3 << " "
		<< i+2 << "//" << i+2 << " "
		<< i+1 << "//" << i+1 << " "
		<< '\n';
	}
}

TEST_CASE("Generate mesh") {
	Brutus::Grid grid(2, 2, 2);

	// Create a sphere
	generate_sphere(grid, 6.0, 8, 8, 8);

	// Generating the mesh
	Brutus::Mesh mesh = grid.generate_mesh(0, 0, 0);
	CHECK(mesh.face_count == 163);

	// Writing to a file
	std::cout << "Generating obj file for mesh" << '\n';
	std::cout << "Face count: " << mesh.face_count << '\n';
	write_model(mesh, "test.obj");

	Brutus::Mesh mesh2 = grid.generate_mesh(1, 0, 0);
	write_model(mesh2, "test2.obj");

	Brutus::Mesh mesh3 = grid.generate_mesh(1, 1, 0);
	write_model(mesh3, "test3.obj");

	Brutus::Mesh mesh4 = grid.generate_mesh(0, 1, 1);
	write_model(mesh4, "test4.obj");

	Brutus::Mesh mesh5 = grid.generate_mesh(0, 1, 0);
	write_model(mesh5, "test5.obj");

	Brutus::Mesh mesh6 = grid.generate_mesh(0, 0, 1);
	write_model(mesh6, "test6.obj");

	Brutus::Mesh mesh7 = grid.generate_mesh(1, 1, 1);
	write_model(mesh7, "test7.obj");

	Brutus::Mesh mesh8 = grid.generate_mesh(1, 0, 1);
	write_model(mesh8, "test8.obj");
}

TEST_CASE("Total size") {
	Brutus::Grid grid(1, 2, 3);

	auto [x, y, z] = grid.total_size();

	CHECK(x == 8);
	CHECK(y == 16);
	CHECK(z == 24);
}

TEST_CASE("Chunk size") {
	Brutus::Grid grid(1, 2, 3);

	auto [x, y, z] = grid.chunk_size();

	CHECK(x == 1);
	CHECK(y == 2);
	CHECK(z == 3);
}
