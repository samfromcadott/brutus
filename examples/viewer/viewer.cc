#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <brutus/brutus.h>

#include "mesh.hh"
#include "camera.hh"
#include "editing.hh"
#include "sdf.hh"

int main(void) {
	const int screenWidth = 800;
	const int screenHeight = 450;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Brutus Viewer");

	Camera3D camera = { 0 };
	camera.position = Vector3 { 0.0f, 0.0f, 8.0f };
	camera.target = Vector3 { 8.0f, 8.0f, 8.0f };
	camera.up = Vector3 { 0.0f, 0.0f, 1.0f };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	SetTargetFPS(60);
	rlDisableBackfaceCulling();

	Brutus::Grid grid(2, 2, 2);
	SDF::sphere(grid, {8,8,8}, 6.0, -1); // Generate a sphere using an SDF

	while ( !WindowShouldClose() ) {
		get_edit(camera, grid);
		update_camera(camera);

		BeginDrawing();

			ClearBackground({32, 32, 32, 255});

			BeginMode3D(camera);
				render_mesh(grid.generate_mesh(0, 0, 0));
				render_mesh(grid.generate_mesh(0, 0, 1));
				render_mesh(grid.generate_mesh(0, 1, 0));
				render_mesh(grid.generate_mesh(0, 1, 1));
				render_mesh(grid.generate_mesh(1, 0, 0));
				render_mesh(grid.generate_mesh(1, 0, 1));
				render_mesh(grid.generate_mesh(1, 1, 0));
				render_mesh(grid.generate_mesh(1, 1, 1));

				// Draw the bounds of the grid
				const Color clear_grey = {224, 224, 224, 128};
				Vector3 bounds = {(float)grid.total_size().x-1, (float)grid.total_size().y-1, (float)grid.total_size().z-1};
				DrawCubeWiresV( Vector3Scale(bounds, 0.5), bounds, clear_grey );

				// Draw the brush location
				Vector3 brush_location = intersection(camera, grid);
				DrawSphere(brush_location, 1.0, clear_grey);
			EndMode3D();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
