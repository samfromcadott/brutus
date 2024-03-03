#include "noise.hh"
#include "height.hh"

using namespace OpenSimplexNoise;

std::vector<float> heightmap(size_t size_x, size_t size_y, size_t size_z) {
	Noise noise(1138);
	std::vector<float> map;
	map.resize(size_x * size_y);

	for (size_t x = 0; x < size_x; x++)
	for (size_t y = 0; y < size_y; y++) {
		float sx = static_cast<float>(x) / static_cast<float>(size_x) * 4.0;
		float sy = static_cast<float>(y) / static_cast<float>(size_y) * 4.0;

		float height = noise.eval(sx, sy) * size_z;
		height = std::abs(height);

		map[x * size_x + y] = height;
	}

	return map;
}
