class Grid {
private:
	size_t size_x, size_y, size_z;
	Chunk* data; // Array of Chunk

	size_t index(const size_t x, const size_t y, const size_t z) const; // Returns the index of a coordinate

public:
	Grid();
	Grid(size_t size_x, size_t size_y, size_t size_z);
	~Grid();

	Chunk& operator()(const size_t x, const size_t y, const size_t z); // Setter
	Chunk operator()(const size_t x, const size_t y, const size_t z) const; // Getter

	Mesh generate_mesh(const size_t x, const size_t y, const size_t z); // Generates a mesh for the given chunk
};

inline size_t Grid::index(const size_t x, const size_t y, const size_t z) const {
	return (x * size_y * size_z) + (y * size_z) + z;
}

inline Grid::Grid() {

}

inline Grid::Grid(size_t size_x, size_t size_y, size_t size_z) {
	this->size_x = size_x;
	this->size_y = size_y;
	this->size_z = size_z;

	data = new Chunk[size_x * size_y * size_z];
}

inline Grid::~Grid() {
	delete[] data;
}


inline Chunk& Grid::operator()(const size_t x, const size_t y, const size_t z) {
	return data[ index(x,y,z) ];
}

inline Chunk Grid::operator()(const size_t x, const size_t y, const size_t z) const {
	return data[ index(x,y,z) ];
}


inline Mesh Grid::generate_mesh(const size_t x, const size_t y, const size_t z) {
	Mesh mesh;
	return mesh;
}