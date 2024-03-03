#pragma once

void get_edit(const Camera& camera, Brutus::Grid& grid); // Checks if the user wants to edit voxels
Vector3 intersection(const Camera& camera, const Brutus::Grid& grid); // Checks if the mouse is pointing at a surface
bool point_in_bounds(const Brutus::Grid& grid, const Vector3 point); // Check if point is in bounds of grid
