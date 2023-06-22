#ifndef BRUTUS_CHUNK_SIZE
#define BRUTUS_CHUNK_SIZE 8
#endif

class Chunk {
private:
	friend class Grid;

	Voxel data[BRUTUS_CHUNK_SIZE * BRUTUS_CHUNK_SIZE * BRUTUS_CHUNK_SIZE]; // Array of Voxel

	size_t index(const size_t x, const size_t y, const size_t z) const { // Returns the index of a coordinate
		return (x * size * size) + (y * size) + z;
	}

public:
	static const size_t size = BRUTUS_CHUNK_SIZE; // Chunks are cubes so this is the same in all dimmensions

	Voxel& operator()(const size_t x, const size_t y, const size_t z) { // Setter
		return data[ index(x,y,z) ];
	}

	Voxel operator()(const size_t x, const size_t y, const size_t z) const { // Getter
		return data[ index(x,y,z) ];
	}
};
