struct Mesh {
	float* vertices = nullptr;
	float* normals = nullptr;
	float* tex_coords = nullptr;

	unsigned short* indices = nullptr;

	size_t vertex_count = 0, face_count = 0;

	~Mesh() {
		if (vertices != nullptr) delete[] vertices;
		if (normals != nullptr) delete[] normals;
		if (tex_coords != nullptr) delete[] tex_coords;
		if (indices != nullptr) delete[] indices;
	}
};
