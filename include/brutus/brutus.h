#ifndef BRUTUS_HEADER
#define BRUTUS_HEADER

#include <cstddef>
#include <cstdint>

namespace Brutus {

class Grid;
class Chunk;
struct Voxel;

struct Mesh {
	float* vertices;
	float* normals;
	float* tex_coords;

	unsigned short *indices;

	size_t vertex_count, face_count;
};

#include "voxel.h"
#include "chunk.h"
#include "grid.h"

}

#endif
