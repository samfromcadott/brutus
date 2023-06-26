struct Mesh {
	float* vertices = nullptr;
	float* normals = nullptr;
	float* tex_coords = nullptr;

	unsigned short* indices = nullptr;

	size_t vertex_count = 0, normal_count = 0, face_count = 0;

	~Mesh() {
		if (vertices != nullptr) delete[] vertices;
		if (normals != nullptr) delete[] normals;
		if (tex_coords != nullptr) delete[] tex_coords;
		if (indices != nullptr) delete[] indices;
	}

	void add_vertex(const vec3f& vertex) {
		vertices[vertex_count*3+0] = vertex.x;
		vertices[vertex_count*3+1] = vertex.y;
		vertices[vertex_count*3+2] = vertex.z;
		vertex_count += 1;
	}

	void add_normal(const vec3f& normal) {
		normals[normal_count*3+0] = normal.x;
		normals[normal_count*3+1] = normal.y;
		normals[normal_count*3+2] = normal.z;
		normal_count += 1;
	}
};
