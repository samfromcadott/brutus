// #include "convert_mesh.hh"
//
// Mesh convert_mesh(Brutus::Mesh& brutus_mesh) {
// 	Mesh mesh; // The raylib mesh
//
// 	mesh.vertices = new float[brutus_mesh.vertex_count*3];
// 	mesh.normals = new float[brutus_mesh.vertex_count*3];
// 	// mesh.texcoords = new float[brutus_mesh.vertex_count*2];
// 	mesh.vertexCount = brutus_mesh.vertex_count;
// 	mesh.triangleCount = mesh.vertexCount / 3;
//
// 	for (size_t i = 0; i < mesh.vertexCount * 3; i+=3) {
// 		mesh.vertices[i] = brutus_mesh.vertices[i];
// 		mesh.vertices[i+1] = brutus_mesh.vertices[i+1];
// 		mesh.vertices[i+2] = brutus_mesh.vertices[i+2];
//
// 		mesh.normals[i] = brutus_mesh.normals[i];
// 		mesh.normals[i+1] = brutus_mesh.normals[i+1];
// 		mesh.normals[i+2] = brutus_mesh.normals[i+2];
//
// 		// mesh.texcoords[i] = 0.0;
// 		// mesh.texcoords[i+1] = 0.0;
// 	}
//
// 	return mesh;
// }
