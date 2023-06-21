#ifndef BRUTUS_HEADER
#define BRUTUS_HEADER

#include <cstddef>
#include <cstdint>

namespace Brutus {

class Grid;
class Chunk;
struct Voxel;

struct Mesh {
	float* vertices = nullptr;
	float* normals = nullptr;
	float* tex_coords = nullptr;

	unsigned short *indices = nullptr;

	size_t vertex_count = 0, face_count = 0;
};

#include "voxel.h"
#include "chunk.h"
#include "grid.h"

}

#endif
