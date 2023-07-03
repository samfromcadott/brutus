#ifndef BRUTUS_HEADER
#define BRUTUS_HEADER

#include <cstddef>
#include <cstdint>
#include <cmath>

namespace Brutus {

class Grid;
class Chunk;
struct Voxel;
struct Mesh;

struct Size3D {
	size_t x, y, z;
};

#include "vectors.h"
#include "mesh.h"
#include "voxel.h"
#include "chunk.h"
#include "grid.h"

}

#endif
