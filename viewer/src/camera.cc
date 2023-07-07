#include <iostream>
#include <raylib.h>
#include <raymath.h>

#include "camera.hh"

float sensitivity = 0.5;

void update_camera(Camera& camera) {
	if ( !IsMouseButtonDown(0) ) return;

	Vector2 delta = GetMouseDelta();
	Vector3 d = Vector3Subtract(camera.target, camera.position);

	d = Vector3RotateByAxisAngle(d, {0,0,1}, -delta.x * GetFrameTime() * sensitivity);
	d = Vector3RotateByAxisAngle(d, {0,1,0}, delta.y * GetFrameTime() * sensitivity);

	camera.position = Vector3Subtract(camera.target, d);
}
