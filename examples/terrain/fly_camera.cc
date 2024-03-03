#include <raylib.h>
#include <raymath.h>
#include "fly_camera.hh"

FlyCamera::FlyCamera() {
	camera = {0};
	camera.position = Vector3 { -8.0f, 8.0f, 8.0f };
	camera.target = Vector3 { 8.0f, 9.0f, 8.0f };
	camera.up = Vector3 { 0.0f, 0.0f, 1.0f };
	camera.fovy = 90.0f;
	camera.projection = CAMERA_PERSPECTIVE;
}

void FlyCamera::update() {
	const float sensitivity = 0.5;
	const float speed = 16.0;

	// Mouse look
	if ( IsMouseButtonDown(0) ) {
		Vector2 delta = GetMouseDelta();

		// Calculate the horizontal and vertical rotation
		yaw -= delta.x * GetFrameTime() * sensitivity;
		pitch -= delta.y * GetFrameTime() * sensitivity;
		pitch = Clamp(pitch, -1.5f, 1.5f);
	}

	// Movement
	Vector2 input_dir = Vector2Zero();

	if ( IsKeyDown(KEY_W) ) input_dir.y += 1;
	if ( IsKeyDown(KEY_S) ) input_dir.y -= 1;
	if ( IsKeyDown(KEY_D) ) input_dir.x += 1;
	if ( IsKeyDown(KEY_A) ) input_dir.x -= 1;

	input_dir = Vector2Normalize(input_dir);

	Vector3 forward = Vector3Subtract(camera.target, camera.position);
	Vector3 right = Vector3CrossProduct(forward, camera.up);

	forward = Vector3Scale(forward, input_dir.y);
	right = Vector3Scale(right, input_dir.x);

	Vector3 velocity = Vector3Add(forward, right);
	velocity = Vector3Normalize(velocity);
	velocity = Vector3Scale( velocity, speed * GetFrameTime() );

	camera.position = Vector3Add(camera.position, velocity);

	//Update view
	Vector3 vector_h = {cos(yaw), sin(yaw), 0.0f};
	Vector3 vector_v = {cos(pitch), 0.0f, sin(pitch)};
	Vector3 camera_target = {vector_h.x*vector_v.x, vector_h.y*vector_v.x, vector_v.z};

	camera.target = Vector3Add( camera_target, camera.position);
}
