#include <algorithm>
#include <brutus/brutus.h>
#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>

#include "noise.hh"
#include "write_model.hh"
#include "convert_mesh.hh"
#include "height.hh"
#include "mesh.hh"
#include "fly_camera.hh"

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

	// Save the meshes
	std::vector< Brutus::Mesh > meshes;

	for (size_t x = 0; x < grid.chunk_size().x - 1; x++)
	for (size_t y = 0; y < grid.chunk_size().y - 1; y++)
	for (size_t z = 0; z < grid.chunk_size().z - 1; z++) {
		meshes.push_back(grid.generate_mesh(x, y, z));
	}

	std::cout << "Generated terrain" << '\n';

	const int screenWidth = 1280;
	const int screenHeight = 720;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Brutus Viewer");

	FlyCamera camera;

	SetTargetFPS(60);

	while ( !WindowShouldClose() ) {
		camera.update();

		BeginDrawing();

			ClearBackground({32, 32, 32, 255});

			BeginMode3D(camera.camera);
				for (auto& m : meshes) {
					render_mesh(m);
				}
			EndMode3D();

			DrawFPS(20, 20);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
