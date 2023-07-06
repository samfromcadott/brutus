#include <raylib.h>

int main(void) {
	const int screenWidth = 800;
	const int screenHeight = 450;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Brutus Viewer");

	Camera3D camera = { 0 };
	camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };
	camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

	SetTargetFPS(60);

	while ( !WindowShouldClose() ) {
		BeginDrawing();

			ClearBackground({32, 32, 32, 255});

			BeginMode3D(camera);

				DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, BLUE);
				DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, DARKBLUE);

			EndMode3D();

			DrawFPS(10, 10);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
