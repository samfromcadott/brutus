#include "write_model.hh"

void write_model(Brutus::Mesh& mesh, std::string filename) {
	if (mesh.vertex_count < 3) return;

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
