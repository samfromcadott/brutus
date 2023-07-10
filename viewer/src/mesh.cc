#include <raylib.h>
#include <rlgl.h>
#include <brutus/brutus.h>

// void generate_mesh(Mesh& mesh, const Brutus::Grid& grid) {
// 	grid.generate_mesh()
// }

void render_mesh(Brutus::Mesh mesh) {
	rlPushMatrix();
	rlBegin(RL_TRIANGLES);

	// Loop over each face
	for (size_t i = 0; i < mesh.vertex_count * 3; i+=3) {
		rlVertex3f(
			mesh.vertices[i+0],
			mesh.vertices[i+1],
			mesh.vertices[i+2]
		);
		rlColor3f(
			(mesh.normals[i+0] + 1.0) / 2.0,
			(mesh.normals[i+1] + 1.0) / 2.0,
			(mesh.normals[i+2] + 1.0) / 2.0
		);
	}

	rlEnd();
	rlPopMatrix();
}
