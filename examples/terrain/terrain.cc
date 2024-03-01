#include <algorithm>
#include <brutus/brutus.h>

#include "noise.hh"
#include "write_model.hh"
#include "convert_mesh.hh"
#include "height.hh"
#include "mesh.hh"

using namespace OpenSimplexNoise;

int main() {
	std::cout << "Brutus terrain test" << '\n';
	Brutus::Grid grid(16, 16, 4); // A large grid

	auto map = heightmap(grid.total_size().x, grid.total_size().y, grid.total_size().z);

	// Generate terrain using the noise
	for (size_t x = 0; x < grid.total_size().x; x++)
	for (size_t y = 0; y < grid.total_size().y; y++) {
		// Find the height at this (x, y) location
		float height = map[x * grid.total_size().x + y];

		for (size_t z = 0; z < grid.total_size().z; z++) {
			// Find the difference between z and the height
			int diff = (z - height) * 64;

			// Set the weight
			Brutus::VoxelWeight weight = std::clamp(diff, -128, 127);
			grid(x, y, z).weight = weight;
		}
	}

	std::cout << "Generated terrain" << '\n';

	Brutus::Mesh mesh = grid.generate_mesh(0, 0, 0);
	std::cout << "Generated mesh" << '\n';

	std::cout << "Vertex count: " << mesh.vertex_count << '\n';

	// write_model(mesh, "terrain.obj");
	// std::cout << "Wrote model file" << '\n';

	const int screenWidth = 800;
	const int screenHeight = 450;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Brutus Viewer");

	Camera3D camera = { 0 };
	camera.position = (Vector3){ -8.0f, -8.0f, 8.0f };
	camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
	camera.up = (Vector3){ 0.0f, 0.0f, 1.0f };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	SetTargetFPS(60);

	while ( !WindowShouldClose() ) {

		BeginDrawing();

			ClearBackground({32, 32, 32, 255});

			BeginMode3D(camera);
				render_mesh(mesh);
			EndMode3D();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
