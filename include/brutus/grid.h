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
	vec3f point_between_voxels(const vec3i chunk, const vec3i a, const vec3i b); // Finds the 0 point between two opposite sign voxels

public:
	Grid();
	Grid(size_t size_x, size_t size_y, size_t size_z);
	~Grid();

	Grid& operator=(Grid other);
	Chunk& operator()(const size_t x, const size_t y, const size_t z); // Setter
	Chunk operator()(const size_t x, const size_t y, const size_t z) const; // Getter

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

	VoxelWeight v0 = (*this)(chunk.x, chunk.y, chunk.z)(voxel.x+0, voxel.y+0, voxel.z+0).weight;
	VoxelWeight v1 = (*this)(chunk.x, chunk.y, chunk.z)(voxel.x+0, voxel.y+0, voxel.z+1).weight;
	VoxelWeight v2 = (*this)(chunk.x, chunk.y, chunk.z)(voxel.x+1, voxel.y+0, voxel.z+1).weight;
	VoxelWeight v3 = (*this)(chunk.x, chunk.y, chunk.z)(voxel.x+1, voxel.y+0, voxel.z+0).weight;
	VoxelWeight v4 = (*this)(chunk.x, chunk.y, chunk.z)(voxel.x+0, voxel.y+1, voxel.z+0).weight;
	VoxelWeight v5 = (*this)(chunk.x, chunk.y, chunk.z)(voxel.x+0, voxel.y+1, voxel.z+1).weight;
	VoxelWeight v6 = (*this)(chunk.x, chunk.y, chunk.z)(voxel.x+1, voxel.y+1, voxel.z+1).weight;
	VoxelWeight v7 = (*this)(chunk.x, chunk.y, chunk.z)(voxel.x+1, voxel.y+1, voxel.z).weight;

	// Set bits for each voxel with a weight below 0
	if ( v0 < 0 ) c ^= 1 << 0;
	if ( v1 < 0 ) c ^= 1 << 1;
	if ( v2 < 0 ) c ^= 1 << 2;
	if ( v3 < 0 ) c ^= 1 << 3;
	if ( v4 < 0 ) c ^= 1 << 4;
	if ( v5 < 0 ) c ^= 1 << 5;
	if ( v6 < 0 ) c ^= 1 << 6;
	if ( v7 < 0 ) c ^= 1 << 7;

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
		mesh.vertices[mesh.vertex_count*3+0] = v0.x;
		mesh.vertices[mesh.vertex_count*3+1] = v0.y;
		mesh.vertices[mesh.vertex_count*3+2] = v0.z;
		mesh.vertex_count += 1;

		mesh.vertices[mesh.vertex_count*3+0] = v1.x;
		mesh.vertices[mesh.vertex_count*3+1] = v1.y;
		mesh.vertices[mesh.vertex_count*3+2] = v1.z;
		mesh.vertex_count += 1;

		mesh.vertices[mesh.vertex_count*3+0] = v2.x;
		mesh.vertices[mesh.vertex_count*3+1] = v2.y;
		mesh.vertices[mesh.vertex_count*3+2] = v2.z;
		mesh.vertex_count += 1;
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

inline vec3f Grid::point_between_voxels(const vec3i chunk, const vec3i a, const vec3i b) {
	// Get the weight of both voxels
	VoxelWeight weight_a = (*this)(chunk.x, chunk.y, chunk.z)(a.x, a.y, a.z).weight;
	VoxelWeight weight_b = (*this)(chunk.x, chunk.y, chunk.z)(b.x, b.y, b.z).weight;

	// Interpolate between them to find where the surface is
	// const int x0 = 0;
	const int x1 = 255;
	// int x = ( -weight_a * (x1 - x0) ) / (weight_b - weight_a) + x0;
	int x = ( -weight_a * x1 ) / (weight_b - weight_a);

	// Calculate vertex location
	vec3f origin_a = voxel_origin(chunk, a);
	vec3f origin_b = voxel_origin(chunk, b);

	vec3f d = origin_b - origin_a; // Vector from a to b
	vec3f vertex = origin_a + ( d * ( float(x) / float(x1) ) );

	return vertex;
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


inline Mesh Grid::generate_mesh(const size_t x, const size_t y, const size_t z) {
	Mesh mesh;
	vec3i chunk = {(int)x, (int)y, (int)z}; // Index of the chunk being meshed

	mesh.vertices = new float[11*8*8*8]();

	// Loop over each neighborhood
	for (size_t i = 0; i < Chunk::size - 1; i++)
	for (size_t j = 0; j < Chunk::size - 1; j++)
	for (size_t k = 0; k < Chunk::size - 1; k++) {
		vec3i voxel = {(int)i, (int)j, (int)k};
		neighborhood_mesh(mesh, chunk, voxel);
	}

	return mesh;
}
