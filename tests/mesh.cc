#include <doctest.h>
#include <string>
#include <fstream>
#include <iostream>

#include <brutus/brutus.h>

void generate_sphere(Brutus::Grid& grid, float radius, float cx, float cy, float cz) {
	for (size_t x = 0; x < grid.total_size().x; x++)
	for (size_t y = 0; y < grid.total_size().y; y++)
	for (size_t z = 0; z < grid.total_size().z; z++) {
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
		<< i+1 << "//" << i+1 << " "
		<< i+2 << "//" << i+2 << " "
		<< i+3 << "//" << i+3 << " "
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
