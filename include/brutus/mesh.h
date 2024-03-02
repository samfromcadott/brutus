/// This class stores vertex data.
/// It is returned by `Grid::generate_mesh()`
struct Mesh {
	float* vertices = nullptr;
	float* normals = nullptr;
	float* tex_coords = nullptr;

	size_t vertex_count = 0, face_count = 0;

	Mesh() = default;

	Mesh(Mesh&& other) {
		this->vertices = other.vertices;
		this->normals = other.normals;
		this->tex_coords = other.tex_coords;

		this->vertex_count = other.vertex_count;
		this->face_count = other.face_count;

		other.vertices = nullptr;
		other.normals = nullptr;
		other.tex_coords = nullptr;
		other.vertex_count = 0;
		other.face_count = 0;
	}

	~Mesh() {
		if (vertices != nullptr) delete[] vertices;
		if (normals != nullptr) delete[] normals;
		if (tex_coords != nullptr) delete[] tex_coords;
	}

	void add_vertex(const vec3f& vertex) {
		vertices[vertex_count*3+0] = vertex.x;
		vertices[vertex_count*3+1] = vertex.y;
		vertices[vertex_count*3+2] = vertex.z;
	}

	void add_normal(const vec3f& normal) {
		normals[vertex_count*3+0] = normal.x;
		normals[vertex_count*3+1] = normal.y;
		normals[vertex_count*3+2] = normal.z;
	}

	void add_uv(const vec2f& uv) {
		// tex_coords[tex_coord_count*2+0] = uv.x;
		// tex_coords[tex_coord_count*2+1] = uv.y;
		// tex_coord_count += 1;
	}
};
