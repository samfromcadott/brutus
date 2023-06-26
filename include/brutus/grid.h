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
	vec3f voxel_origin(const vec3i voxel); // Returns the world location of a voxel
	Case neighborhood_case(vec3i voxel); // Determines the case of a neighborhood
	void neighborhood_mesh(Mesh& mesh, vec3i voxel); // Adds triangles to mesh for neighborhood of voxel
	vec3f vertex_from_edge(vec3i voxel, const Edge edge); // Gets vertex position for edge in neighborhood of voxel
	vec3f normal_from_edge(vec3i voxel, const Edge edge); // Calculates normals for a vertex
	vec3f point_between_voxels(const vec3i a, const vec3i b); // Finds the 0 point between two opposite sign voxels
	void correct_boundry_voxel(vec3i& voxel); // Gets voxel from next chunk

public:
	bool calculate_normals = true;
	bool calculate_uv = true;

	Grid(){}
	Grid(size_t size_x, size_t size_y, size_t size_z);
	~Grid();

	Grid& operator=(Grid other);
	Voxel& operator()(const size_t x, const size_t y, const size_t z); // Setter
	Voxel operator()(const size_t x, const size_t y, const size_t z) const; // Getter
	Voxel& operator()(const vec3i voxel); // Setter
	Voxel operator()(const vec3i voxel) const; // Getter

	Mesh generate_mesh(const size_t x, const size_t y, const size_t z); // Generates a mesh for the given chunk
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

inline Grid::Case Grid::neighborhood_case(vec3i voxel) {
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

	// Get weights
	VoxelWeight w[8];
	for (size_t i = 0; i < 8; i++)
		w[i] = (*this)(voxels[i]).weight;

	// Set bits for each voxel with a negative weight
	for (size_t i = 0; i < 8; i++)
		if ( w[i] < 0 ) c ^= 1 << i;

	return c;
}

inline void Grid::neighborhood_mesh(Mesh& mesh, vec3i voxel) {
	// Determine the case of the neighborhood
	// Case c = neighborhood_case(chunk, voxel);
	Case c = neighborhood_case(voxel);
	if (c == 0 || c == 255) return; // These cases don't have vertices

	// Determine the number of faces and vertices
	const size_t face_count = case_face_count[c];

	mesh.face_count += face_count;

	// Loop over faces
	for (size_t i = 0; i < face_count; i++) {
		EdgeFace face = case_faces[c][i];

		// Find the location of each vertex
		vec3f v0 = vertex_from_edge(voxel, face.v0);
		vec3f v1 = vertex_from_edge(voxel, face.v1);
		vec3f v2 = vertex_from_edge(voxel, face.v2);

		// Add the face to the mesh
		mesh.add_vertex(v0);
		mesh.add_vertex(v1);
		mesh.add_vertex(v2);

		// Calculate normals
		// if (calculate_normals) {
		// 	// Find the location of each vertex
		// 	vec3f n0 = normal_from_edge(chunk, voxel, face.v0);
		// 	vec3f n1 = normal_from_edge(chunk, voxel, face.v1);
		// 	vec3f n2 = normal_from_edge(chunk, voxel, face.v2);
		//
		// 	// Add the face to the mesh
		// 	mesh.add_normal(n0);
		// 	mesh.add_normal(n1);
		// 	mesh.add_normal(n2);
		// }
	}

}

inline vec3f Grid::vertex_from_edge(vec3i voxel, const Edge edge) {
	return point_between_voxels( voxel + edge_offsets[edge][0], voxel + edge_offsets[edge][1] );
}

inline vec3f Grid::normal_from_edge(vec3i voxel, const Edge edge) {
	// // Get the origins of both voxels
	// vec3i coord_a = voxel + edge_offsets[edge][0];
	// vec3i coord_b = voxel + edge_offsets[edge][1];
	//
	// vec3f a = voxel_origin(chunk, ca);
	// vec3f b = voxel_origin(chunk, cb);
	//
	// // Get the direction vector from voxel a to voxel b
	// // vec3f d = a - b; // d will always be normalized
	// // vec3f normal = d;
	//
	// // Read the weight of both voxels
	// vec3i chunk_a = chunk;
	// vec3i chunk_b = chunk;
	// correct_boundry_voxel(chunk_a, coord_a);
	// correct_boundry_voxel(chunk_b, coord_b);
	//
	// VoxelWeight weight_a = (*this)(chunk_a)(ca).weight;
	// VoxelWeight weight_b = (*this)(chunk_b)(cb).weight;
	//
	// // if (weight_b < weight_a) normal = normal * -1;
	// // Determine which voxel is the filled one
	// vec3i coord;
	// (weight_b < weight_a) ? coord = coord_b : coord = coord_a;
	//
	// // Get the coordinates for calculating the gradient
	// int x0 = coord.x - 1, x1 = coord.x + 1;
	// int y0 = coord.y - 1, y1 = coord.y + 1;
	// int z0 = coord.z - 1, z1 = coord.z + 1;

	vec3f normal;
	return normal;
}

inline vec3f Grid::point_between_voxels(vec3i a, vec3i b) {
	// Get the weight of both voxels
	VoxelWeight weight_a = (*this)(a).weight;
	VoxelWeight weight_b = (*this)(b).weight;

	// Interpolate between them to find where the surface is
	const int x1 = 255;
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

inline Grid& Grid::operator=(Grid other) {
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

	mesh.vertices = new float[11*8*8*8]();
	mesh.normals = new float[11*8*8*8]();

	// Get the start coordinates
	int start_x = x * Chunk::size, end_x = (x+1) * Brutus::Chunk::size;
	int start_y = y * Chunk::size, end_y = (y+1) * Brutus::Chunk::size;
	int start_z = z * Chunk::size, end_z = (z+1) * Brutus::Chunk::size;

	// For each dimmension go an extra step if there is an adjacent chunk
	int border_x = x == size_x - 1;
	int border_y = y == size_y - 1;
	int border_z = z == size_z - 1;

	// Loop over each neighborhood
	for (int i = start_x; i < end_x - border_x; i++)
	for (int j = start_y; j < end_y - border_y; j++)
	for (int k = start_z; k < end_z - border_z; k++) {
		vec3i voxel = {(int)i, (int)j, (int)k};
		neighborhood_mesh(mesh, voxel);
	}

	return mesh;
}
