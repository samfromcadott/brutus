class Grid {
private:
	typedef uint8_t Case; // Bitfield that stores which voxels in a neighborhood are below threshold
	typedef int8_t Edge; // Index of edge in voxel neighborhood
	struct EdgeFace { // Defines faces by the edges of the cube the vertices touch
		Edge v0, v1, v2;
	};

	// Include the lookup tables used for mesh generation
	#include "lut.h"

	size_t size_x, size_y, size_z;
	Chunk* data = nullptr; // Array of Chunk

	size_t index(const size_t x, const size_t y, const size_t z) const; // Returns the index of a coordinate
	vec3f voxel_origin(const vec3i chunk, const vec3i voxel); // Returns the world location of a voxel
	Case neighborhood_case(vec3i chunk, vec3i voxel); // Determines the case of a neighborhood
	void neighborhood_mesh(Mesh& mesh, vec3i chunk, vec3i voxel); // Adds triangles to mesh for neighborhood of voxel
	vec3f vertex_from_edge(vec3i chunk, vec3i voxel, const Edge edge); // Gets vertex position for edge in neighborhood of voxel
	vec3f point_between_voxels(const vec3i chunk, vec3i a, vec3i b); // Finds the 0 point between two opposite sign voxels
	void correct_boundry_voxel(vec3i& chunk, vec3i& voxel); // Gets voxel from next chunk

public:
	Grid(){}
	Grid(size_t size_x, size_t size_y, size_t size_z);
	~Grid();

	Grid& operator=(Grid other);
	Chunk& operator()(const size_t x, const size_t y, const size_t z); // Setter
	Chunk operator()(const size_t x, const size_t y, const size_t z) const; // Getter
	Chunk& operator()(const vec3i chunk); // Setter
	Chunk operator()(const vec3i chunk) const; // Getter

	Mesh generate_mesh(const size_t x, const size_t y, const size_t z); // Generates a mesh for the given chunk
};

inline size_t Grid::index(const size_t x, const size_t y, const size_t z) const {
	return (x * size_y * size_z) + (y * size_z) + z;
}

inline vec3f Grid::voxel_origin(const vec3i chunk, const vec3i voxel) {
	return {
		float(chunk.x * Chunk::size + voxel.x),
		float(chunk.y * Chunk::size + voxel.y),
		float(chunk.z * Chunk::size + voxel.z)
	};
}

inline Grid::Case Grid::neighborhood_case(vec3i chunk, vec3i voxel) {
	Case c = 0;

	// Get all the voxel locations
	vec3i voxels[8] = {
		voxel,
		voxel + (vec3i){0, 0, 1},
		voxel + (vec3i){1, 0, 1},
		voxel + (vec3i){1, 0, 0},
		voxel + (vec3i){0, 1, 0},
		voxel + (vec3i){0, 1, 1},
		voxel + (vec3i){1, 1, 1},
		voxel + (vec3i){1, 1, 0},
	};

	// Chunks may need to be corrected
	vec3i chunks[8];
	for (size_t i = 0; i < 8; i++) chunks[i] = chunk;

	// Correct voxels (voxels[0] never needs to be corrected)
	for (size_t i = 1; i < 8; i++)
		correct_boundry_voxel( chunks[i], voxels[i] );

	// Get weights
	VoxelWeight w[8];
	for (size_t i = 0; i < 8; i++)
		w[i] = (*this)(chunks[i])(voxels[i]).weight;

	// Set bits for each voxel with a negative weight
	for (size_t i = 0; i < 8; i++)
		if ( w[i] < 0 ) c ^= 1 << i;

	return c;
}

inline void Grid::neighborhood_mesh(Mesh& mesh, vec3i chunk, vec3i voxel) {
	// Determine the case of the neighborhood
	Case c = neighborhood_case(chunk, voxel);
	if (c == 0 || c == 255) return; // These cases don't have vertices

	// Determine the number of faces and vertices
	const size_t face_count = case_face_count[c];

	mesh.face_count += face_count;

	// Loop over faces
	for (size_t i = 0; i < face_count; i++) {
		EdgeFace face = case_faces[c][i];

		// Find the location of each vertex
		vec3f v0 = vertex_from_edge(chunk, voxel, face.v0);
		vec3f v1 = vertex_from_edge(chunk, voxel, face.v1);
		vec3f v2 = vertex_from_edge(chunk, voxel, face.v2);

		// Add the face to the mesh
		mesh.add_vertex(v0);
		mesh.add_vertex(v1);
		mesh.add_vertex(v2);
	}

}

inline vec3f Grid::vertex_from_edge(vec3i chunk, vec3i voxel, const Edge edge) {
	vec3f vertex;

	// Find to surface point of the edge
	switch (edge) {
		case 0:
			vertex = point_between_voxels(chunk, voxel, voxel + (vec3i){0,0,1});
			break;
		case 1:
			vertex = point_between_voxels(chunk, voxel + (vec3i){0,0,1}, voxel + (vec3i){1,0,1});
			break;
		case 2:
			vertex = point_between_voxels(chunk, voxel + (vec3i){1,0,0}, voxel + (vec3i){1,0,1});
			break;
		case 3:
			vertex = point_between_voxels(chunk, voxel, voxel + (vec3i){1,0,0});
			break;
		case 4:
			vertex = point_between_voxels(chunk, voxel + (vec3i){0,1,0}, voxel + (vec3i){0,1,1});
			break;
		case 5:
			vertex = point_between_voxels(chunk, voxel + (vec3i){0,1,1}, voxel + (vec3i){1,1,1});
			break;
		case 6:
			vertex = point_between_voxels(chunk, voxel + (vec3i){1,1,0}, voxel + (vec3i){1,1,1});
			break;
		case 7:
			vertex = point_between_voxels(chunk, voxel + (vec3i){0,1,0}, voxel + (vec3i){1,1,0});
			break;
		case 8:
			vertex = point_between_voxels(chunk, voxel, voxel + (vec3i){0,1,0});
			break;
		case 9:
			vertex = point_between_voxels(chunk, voxel + (vec3i){0,0,1}, voxel + (vec3i){0,1,1});
			break;
		case 10:
			vertex = point_between_voxels(chunk, voxel + (vec3i){1,0,1}, voxel + (vec3i){1,1,1});
			break;
		case 11:
			vertex = point_between_voxels(chunk, voxel + (vec3i){1,0,0}, voxel + (vec3i){1,1,0});
			break;
	}

	return vertex;
}

inline vec3f Grid::point_between_voxels(const vec3i chunk, vec3i a, vec3i b) {
	// Correct for boundries
	vec3i chunk_a = chunk;
	vec3i chunk_b = chunk;
	correct_boundry_voxel(chunk_a, a);
	correct_boundry_voxel(chunk_b, b);

	// Get the weight of both voxels
	VoxelWeight weight_a = (*this)(chunk_a)(a).weight;
	VoxelWeight weight_b = (*this)(chunk_b)(b).weight;

	// Interpolate between them to find where the surface is
	const int x1 = 255;
	int x = ( -weight_a * x1 ) / (weight_b - weight_a);

	// Calculate vertex location
	vec3f origin_a = voxel_origin(chunk_a, a);
	vec3f origin_b = voxel_origin(chunk_b, b);

	vec3f d = origin_b - origin_a; // Vector from a to b
	vec3f vertex = origin_a + ( d * ( float(x) / float(x1) ) );

	return vertex;
}

inline void Grid::correct_boundry_voxel(vec3i& chunk, vec3i& voxel) {
	if (voxel.x == Chunk::size) {
		chunk.x += 1;
		voxel.x = 0;
	}

	if (voxel.y == Chunk::size) {
		chunk.y += 1;
		voxel.y = 0;
	}

	if (voxel.z == Chunk::size) {
		chunk.z += 1;
		voxel.z = 0;
	}
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

inline Grid& Grid::operator=(Grid other) {
	if (data != nullptr) delete[] data;

	this->data = other.data;
	this->size_x = other.size_x;
	this->size_y = other.size_y;
	this->size_z = other.size_z;

	other.data = nullptr;

	return *this;
}

inline Chunk& Grid::operator()(const size_t x, const size_t y, const size_t z) {
	return data[ index(x,y,z) ];
}

inline Chunk Grid::operator()(const size_t x, const size_t y, const size_t z) const {
	return data[ index(x,y,z) ];
}

inline Chunk& Grid::operator()(const vec3i chunk) {
	return (*this)(chunk.x, chunk.y, chunk.z);
}

inline Chunk Grid::operator()(const vec3i chunk) const {
	return (*this)(chunk.x, chunk.y, chunk.z);
}

inline Mesh Grid::generate_mesh(const size_t x, const size_t y, const size_t z) {
	Mesh mesh;
	vec3i chunk = {(int)x, (int)y, (int)z}; // Index of the chunk being meshed

	mesh.vertices = new float[11*8*8*8]();

	// For each dimmension go an extra step if there is an adjacent chunk
	int border_x = x == size_x - 1;
	int border_y = y == size_y - 1;
	int border_z = z == size_z - 1;

	// Loop over each neighborhood
	for (size_t i = 0; i < Chunk::size - border_x; i++)
	for (size_t j = 0; j < Chunk::size - border_y; j++)
	for (size_t k = 0; k < Chunk::size - border_z; k++) {
		vec3i voxel = {(int)i, (int)j, (int)k};
		neighborhood_mesh(mesh, chunk, voxel);
	}

	return mesh;
}
