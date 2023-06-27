struct vec3f {
	float x, y, z;

	vec3f operator+(const vec3f& other) {
		return {
			x + other.x,
			y + other.y,
			z + other.z
		};
	}

	vec3f operator-(const vec3f& other) {
		return {
			x - other.x,
			y - other.y,
			z - other.z
		};
	}

	vec3f operator*(const float& other) {
		return {
			x * other,
			y * other,
			z * other
		};
	}

	vec3f normalized() {
		vec3f v = *this;

		float length = sqrt( pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2) );
		if (length == 0.0) length = 1.0;

		v = v * (1.0 / length);

		return v;
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

	vec3i operator-(const vec3i& other) {
		return {
			x - other.x,
			y - other.y,
			z - other.z
		};
	}
};
