#include <raylib.h>
#include <raymath.h>
#include <brutus/brutus.h>

#include "sdf.hh"

void SDF::sphere(Brutus::Grid& grid, Vector3 center, float radius) {
	size_t min_x = Clamp(center.x - radius - 1, 0, grid.total_size().x-1);
	size_t min_y = Clamp(center.y - radius - 1, 0, grid.total_size().y-1);
	size_t min_z = Clamp(center.z - radius - 1, 0, grid.total_size().z-1);

	size_t max_x = Clamp(center.x + radius + 1, 0, grid.total_size().x-1);
	size_t max_y = Clamp(center.y + radius + 1, 0, grid.total_size().y-1);
	size_t max_z = Clamp(center.z + radius + 1, 0, grid.total_size().z-1);

	for (size_t x = min_x; x < max_x; x++)
	for (size_t y = min_y; y < max_y; y++)
	for (size_t z = min_z; z < max_z; z++) {
		float weight = sqrt( pow(center.x-x, 2) + pow(center.y-y, 2) + pow(center.z-z, 2) ) - radius;
		weight *= 64;

		// Clamp values
		if (weight > 127) weight = 127;
		if (weight < -128) weight = -128;

		grid(x,y,z).weight = Brutus::VoxelWeight(weight);
	}
}
