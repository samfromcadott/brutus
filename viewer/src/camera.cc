#include <iostream>
#include <raylib.h>
#include <raymath.h>

#include "camera.hh"

float sensitivity = 5.0;
float rotate_h = 0.0;
float rotate_v = 0.0;
float zoom = 16.0;
float zoom_speed = 30.0;
float zoom_min = 16.0;
float zoom_max = 64.0;

void update_camera(Camera& camera) {
	zoom -= GetMouseWheelMove() * GetFrameTime() * zoom_speed; // Zoom the camera
	zoom = Clamp(zoom, zoom_min, zoom_max);

	if ( IsMouseButtonDown(0) ) {
		Vector2 delta = GetMouseDelta();

		// Calculate the horizontal and vertical rotation
		rotate_h = rotate_h - delta.x * GetFrameTime();
		rotate_v = rotate_v + delta.y * GetFrameTime();
		rotate_v = Clamp(rotate_v, -1.5, 1.5);
	}

	//Update view
	Vector3 vector_h = {cos( rotate_h ), sin( rotate_h ), 0.0f};
	Vector3 vector_v = {cos( rotate_v ), 0.0f, sin( rotate_v )};
	Vector3 camera_location = {vector_h.x*vector_v.x, vector_h.y*vector_v.x, vector_v.z};

	camera.position = Vector3Add( Vector3Scale(camera_location, zoom), camera.target);
}
