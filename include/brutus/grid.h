/// This class is used to generate meshes from voxel data.
/// It is effectivly a 3D array of `Chunk`.
class Grid {
private:
	typedef uint8_t Case; ///< Bitfield that stores which voxels in a neighborhood are below threshold
	typedef int8_t Edge; ///< Index of edge in voxel neighborhood
	struct EdgeFace { ///< Defines faces by the edges of the cube the vertices touch
		Edge v0, v1, v2;

		EdgeFace invert() const {
			return EdgeFace {v2, v1, v0};
		}
	};

	// Include the lookup tables used for mesh generation
	#include "lut.h"

	size_t size_x, size_y, size_z;
	Chunk* data = nullptr; // Array of Chunk

	size_t index(const size_t x, const size_t y, const size_t z) const; ///< Returns the index of a coordinate
	vec3f voxel_origin(const vec3i voxel); ///< Returns the world location of a voxel
	Case neighborhood_case(const vec3i voxel); ///< Determines the case of a neighborhood
	void neighborhood_mesh(Mesh& mesh, const vec3i voxel); ///< Adds triangles to mesh for neighborhood of voxel
	vec3f vertex_from_edge(const vec3i voxel, const Edge edge); ///< Gets vertex position for edge in neighborhood of voxel
	vec3f normal_from_edge(const vec3i voxel, const Edge edge); ///< Calculates normals for a vertex
	vec2f uv_from_vertex(const vec3f vertex, const vec3f normal); ///< Calculates texture coordinates from existing vertex
	vec3f point_between_voxels(const vec3i a, const vec3i b); ///< Finds the 0 point between two opposite sign voxels

public:
	bool calculate_normals = true; ///< Determines if normals are calculated when `generate_mesh()` is called.
	bool calculate_uv = true; ///< Determines if texture coordinates are calculated when `generate_mesh()` is called.
	bool winding_ccw = true; ///< Determines if faces have a counter clockwise winding order.

	Grid(){}
	Grid(size_t size_x, size_t size_y, size_t size_z);
	~Grid();

	Grid& operator=(Grid& other);
	///
	/// Voxels can be accessed by putting their coordinates in parentheses.
	Voxel& operator()(const size_t x, const size_t y, const size_t z); // Setter
	Voxel operator()(const size_t x, const size_t y, const size_t z) const; // Getter
	Voxel& operator()(const vec3i voxel); // Setter
	Voxel operator()(const vec3i voxel) const; // Getter

	Mesh generate_mesh(const size_t x, const size_t y, const size_t z); ///< Generates a mesh for the given chunk
	Size3D total_size() const; ///< Returns the total size of the grid in voxels
	Size3D chunk_size() const; ///< Returns the size of the grid in chunks
};

inline size_t Grid::index(const size_t x, const size_t y, const size_t z) const {
	return (x * size_y * size_z) + (y * size_z) + z;
}

inline vec3f Grid::voxel_origin(const vec3i voxel) {
	return {
		float(voxel.x),
		float(voxel.y),
		float(voxel.z)
	};
}

inline Grid::Case Grid::neighborhood_case(const vec3i voxel) {
	// Get all the voxel locations
	vec3i voxels[8] = {
		voxel,
		voxel + vec3i{0, 0, 1},
		voxel + vec3i{1, 0, 1},
		voxel + vec3i{1, 0, 0},
		voxel + vec3i{0, 1, 0},
		voxel + vec3i{0, 1, 1},
		voxel + vec3i{1, 1, 1},
		voxel + vec3i{1, 1, 0},
	};

	// Get weights
	VoxelWeight w[8];
	for (size_t i = 0; i < 8; i++)
		w[i] = (*this)(voxels[i]).weight;

	// Set bits for each voxel with a negative weight
	Case c = 0;
	for (size_t i = 0; i < 8; i++)
		if ( w[i] < 0 ) c ^= 1 << i;

	return c;
}

inline void Grid::neighborhood_mesh(Mesh& mesh, const vec3i voxel) {
	// Determine the case of the neighborhood
	Case c = neighborhood_case(voxel);
	if (c == 0 || c == 255) return; // These cases don't have vertices

	// Determine the number of faces and vertices
	const size_t face_count = case_face_count[c];

	mesh.face_count += face_count;

	// Loop over faces
	for (size_t i = 0; i < face_count; i++) {
		EdgeFace face = case_faces[c][i];
		if (winding_ccw) face = face.invert();
		Edge edges[3] = {face.v0, face.v1, face.v2};

		for (size_t v = 0; v < 3; v++) {
			vec3f vertex, normal;

			vertex = vertex_from_edge(voxel, edges[v]);
			mesh.add_vertex(vertex);

			if (calculate_normals) {
				normal = normal_from_edge(voxel, edges[v]);
				mesh.add_normal(normal);
			}

			mesh.vertex_count += 1;
		}
	}
}

inline vec3f Grid::vertex_from_edge(const vec3i voxel, const Edge edge) {
	return point_between_voxels( voxel + edge_offsets[edge][0], voxel + edge_offsets[edge][1] );
}

inline vec3f Grid::normal_from_edge(const vec3i voxel, const Edge edge) {
	// Get the origins of both voxels
	vec3i coord_a = voxel + edge_offsets[edge][0];
	vec3i coord_b = voxel + edge_offsets[edge][1];

	// Read the weight of both voxels
	VoxelWeight weight_a = (*this)(coord_a).weight;
	VoxelWeight weight_b = (*this)(coord_b).weight;

	// Determine which voxel is the filled one
	vec3i coord;
	(weight_b < weight_a) ? coord = coord_b : coord = coord_a;

	// Get the coordinates for calculating the gradient
	size_t x0 = (coord.x == 0) ? 0 : coord.x - 1;
	size_t y0 = (coord.y == 0) ? 0 : coord.y - 1;
	size_t z0 = (coord.z == 0) ? 0 : coord.z - 1;
	size_t x1 = (coord.x >= (int)total_size().x) ? total_size().x - 1 : coord.x + 1;
	size_t y1 = (coord.y >= (int)total_size().y) ? total_size().y - 1 : coord.y + 1;
	size_t z1 = (coord.z >= (int)total_size().z) ? total_size().z - 1 : coord.z + 1;

	// Get the delta on each axis
	float dx = static_cast<float>( (*this)(x1, coord.y, coord.z).weight - (*this)(x0, coord.y, coord.z).weight );
	float dy = static_cast<float>( (*this)(coord.x, y1, coord.z).weight - (*this)(coord.x, y0, coord.z).weight );
	float dz = static_cast<float>( (*this)(coord.x, coord.y, z1).weight - (*this)(coord.x, coord.y, z0).weight );

	// Compute the gradient
	vec3f gradient = {dx, dy, dz};
	vec3f normal = gradient.normalized();

	return normal;
}

inline vec2f Grid::uv_from_vertex(const vec3f vertex, const vec3f normal) {
	vec2f tex_coord;

	vec3f U = normal.cross( {0, 0, 1} ); // Axis for x component of tex_coord
	if ( U.dot(U) < 0.001 ) U = {1, 0, 0};
	else U = U.normalized();

	vec3f V = normal.cross(U).normalized(); // Axis for y component of tex_coord

	tex_coord = vec2f{ vertex.dot(U), vertex.dot(V) };

	return tex_coord;
}

inline vec3f Grid::point_between_voxels(const vec3i a, const vec3i b) {
	// Get the weight of both voxels
	VoxelWeight weight_a = (*this)(a).weight;
	VoxelWeight weight_b = (*this)(b).weight;

	// Interpolate between them to find where the surface is
	const int x1 = weight_max - weight_min;
	int x = ( -weight_a * x1 ) / (weight_b - weight_a);

	// Calculate vertex location
	vec3f origin_a = voxel_origin(a);
	vec3f origin_b = voxel_origin(b);

	vec3f d = origin_b - origin_a; // Vector from a to b
	vec3f vertex = origin_a + ( d * ( float(x) / float(x1) ) );

	return vertex;
}

inline Grid::Grid(size_t size_x, size_t size_y, size_t size_z) {
	this->size_x = size_x;
	this->size_y = size_y;
	this->size_z = size_z;

	data = new Chunk[size_x * size_y * size_z];
}

inline Grid::~Grid() {
	if (data != nullptr) delete[] data;
}

inline Grid& Grid::operator=(Grid& other) {
	if (data != nullptr) delete[] data;

	this->data = other.data;
	this->size_x = other.size_x;
	this->size_y = other.size_y;
	this->size_z = other.size_z;

	other.data = nullptr;

	return *this;
}

inline Voxel& Grid::operator()(const size_t x, const size_t y, const size_t z) {
	return data[
		index(x / Chunk::size, y / Chunk::size, z / Chunk::size) // Get the chunk
	](
		x % Chunk::size, y % Chunk::size, z % Chunk::size // Get the voxel in the chunk
	);
}

inline Voxel Grid::operator()(const size_t x, const size_t y, const size_t z) const {
	return data[
		index(x / Chunk::size, y / Chunk::size, z / Chunk::size) // Get the chunk
	](
		x % Chunk::size, y % Chunk::size, z % Chunk::size // Get the voxel in the chunk
	);
}

inline Voxel& Grid::operator()(const vec3i voxel) {
	return (*this)(voxel.x, voxel.y, voxel.z);
}

inline Voxel Grid::operator()(const vec3i voxel) const {
	return (*this)(voxel.x, voxel.y, voxel.z);
}

inline Mesh Grid::generate_mesh(const size_t x, const size_t y, const size_t z) {
	Mesh mesh;

	mesh.vertices = new float[11 * Chunk::size * Chunk::size * Chunk::size]();
	if (calculate_normals) mesh.normals = new float[11 * Chunk::size * Chunk::size * Chunk::size]();
	// mesh.tex_coords = new float[11 * Chunk::size * Chunk::size * Chunk::size]();

	// Get the start coordinates
	int start_x = static_cast<int>( x * Chunk::size );
	int end_x = static_cast<int>( (x+1) * Chunk::size );
	int start_y = static_cast<int>( y * Chunk::size );
	int end_y = static_cast<int>( (y+1) * Chunk::size );
	int start_z = static_cast<int>( z * Chunk::size );
	int end_z = static_cast<int>( (z+1) * Chunk::size );

	// For each dimmension go an extra step if there is an adjacent chunk
	int border_x = x == size_x - 1;
	int border_y = y == size_y - 1;
	int border_z = z == size_z - 1;

	// Loop over each neighborhood
	for (int i = start_x; i < end_x - border_x; i++)
	for (int j = start_y; j < end_y - border_y; j++)
	for (int k = start_z; k < end_z - border_z; k++) {
		vec3i voxel = {i, j, k};
		neighborhood_mesh(mesh, voxel);
	}

	return mesh;
}

inline Size3D Grid::total_size() const {
	return {Chunk::size * size_x, Chunk::size * size_y, Chunk::size * size_z};
}

inline Size3D Grid::chunk_size() const {
	return {size_x, size_y, size_z};
}
