#include <raylib.h>
#include <brutus/brutus.h>

#include "mesh.hh"

int main(void) {
	const int screenWidth = 800;
	const int screenHeight = 450;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Brutus Viewer");

	Camera3D camera = { 0 };
	camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
	camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
	camera.up = (Vector3){ 0.0f, 0.0f, 1.0f };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

	SetTargetFPS(60);

	// Create the shere
	Brutus::Grid grid(1, 1, 1);

	// Sphere properties
	const float radius = 2.0;
	const float cx = 3.5, cy = 3.5, cz = 3.5;

	// Generate a sphere using an SDF
	for (size_t x = 0; x < grid.total_size().x; x++)
	for (size_t y = 0; y < grid.total_size().y; y++)
	for (size_t z = 0; z < grid.total_size().z; z++) {
		float weight = (sqrt( pow(cx-x, 2) + pow(cy-y, 2) + pow(cz-z, 2) ) - radius) * 64;

		// Clamp values
		if (weight > 127) weight = 127;
		if (weight < -128) weight = -128;

		grid(x,y,z).weight = Brutus::VoxelWeight(weight);
	}

	Brutus::Mesh mesh = grid.generate_mesh(0, 0, 0); // Generate a mesh


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