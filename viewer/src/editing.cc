#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <brutus/brutus.h>

#include "editing.hh"

void get_edit(const Camera& camera, Brutus::Grid& grid) {
	Vector3 brush_location = intersection(camera, grid);

	if (brush_location.x == -1) return; // Check if no intersection returned
	if (!IsMouseButtonDown(0)) return;

	grid( int(brush_location.x), int(brush_location.y), int(brush_location.z) ).weight = -128;
}

Vector3 intersection(const Camera& camera, const Brutus::Grid& grid) {
	const int max_steps = 128;
	Ray ray = GetMouseRay(GetMousePosition(), camera);
	Vector3 location = {-1, -1, -1};

	// March along ray
	for (int i = 0; i < max_steps; i++) {
		Vector3 last_location = location;
		location = Vector3Add( ray.position, Vector3Scale(ray.direction, i) ); // Get the next location

		if ( !point_in_bounds(grid, location) ) {
			location = last_location;
			continue;
		}

		// Get closest voxel
		Brutus::VoxelWeight weight = grid( floor(location.x), floor(location.y), floor(location.z) ).weight;
		if (weight < 0) break; // Point is under surface, there is an intersection
	}

	return location;
}

bool point_in_bounds(const Brutus::Grid& grid, const Vector3 point) {
	if (point.x < 0 || point.y < 0 || point.z < 0) return false;
	if (point.x > grid.total_size().x || point.y > grid.total_size().y || point.z > grid.total_size().z) return false;
	return true;
}
