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
				for (size_t x = 0; x < grid.chunk_size().x - 1; x++)
				for (size_t y = 0; y < grid.chunk_size().y - 1; y++)
				for (size_t z = 0; z < grid.chunk_size().z - 1; z++) {
					Brutus::Mesh mesh = grid.generate_mesh(x, y, z);
					render_mesh( mesh);
				}

				// Draw the bounds of the grid
				const Color clear_grey = {224, 224, 224, 128};
				Vector3 bounds = {(float)grid.total_size().x-1, (float)grid.total_size().y-1, (float)grid.total_size().z-1};
				DrawCubeWiresV( Vector3Scale(bounds, 0.5), bounds, clear_grey );
			EndMode3D();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
