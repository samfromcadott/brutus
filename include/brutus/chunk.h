#ifndef BRUTUS_CHUNK_SIZE
#define BRUTUS_CHUNK_SIZE 8
#endif

/// This is used to store voxels. It does not need to be instanced directly.
/// `Grid` acts as a container for `Chunk`.
class Chunk {
private:
	friend class Grid;

	Voxel data[BRUTUS_CHUNK_SIZE * BRUTUS_CHUNK_SIZE * BRUTUS_CHUNK_SIZE]; // Array of Voxel

	size_t index(const size_t x, const size_t y, const size_t z) const { // Returns the index of a coordinate
		return (x * size * size) + (y * size) + z;
	}

public:
	static const size_t size = BRUTUS_CHUNK_SIZE; ///< Chunks are cubes so this is the same in all dimmensions. Default value is 8.

	Voxel& operator()(const size_t x, const size_t y, const size_t z) { // Setter
		return data[ index(x,y,z) ];
	}

	Voxel operator()(const size_t x, const size_t y, const size_t z) const { // Getter
		return data[ index(x,y,z) ];
	}

	Voxel& operator()(const vec3i voxel) { // Setter
		return (*this)(voxel.x, voxel.y, voxel.z);
	}

	Voxel operator()(const vec3i voxel) const { // Getter
		return (*this)(voxel.x, voxel.y, voxel.z);
	}
};
