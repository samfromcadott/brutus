struct vec3f {
	float x, y, z;

	vec3f operator+(const vec3f& other) {
		return {
			x + other.x,
			y + other.y,
			z + other.z
		};
	}
};

struct vec3i {
	int x, y, z;

	vec3i operator+(const vec3i& other) {
		return {
			x + other.x,
			y + other.y,
			z + other.z
		};
	}
};
