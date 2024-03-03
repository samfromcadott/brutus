struct vec3f {
	float x, y, z;

	vec3f operator+(const vec3f& other) const {
		return {
			x + other.x,
			y + other.y,
			z + other.z
		};
	}

	vec3f operator-(const vec3f& other) const {
		return {
			x - other.x,
			y - other.y,
			z - other.z
		};
	}

	vec3f operator*(const float& other) const {
		return {
			x * other,
			y * other,
			z * other
		};
	}

	vec3f cross(const vec3f& other) const {
		return {
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		};
	}

	float dot(const vec3f& other) const {
		return x * other.x + y * other.y + z * other.z;
	}

	vec3f normalized() const {
		vec3f v = *this;

		float length = sqrt( pow(v.x, 2.0f) + pow(v.y, 2.0f) + pow(v.z, 2.0f) );
		if (length == 0.0) length = 1.0;

		v = v * (1.0f / length);

		return v;
	}
};

struct vec2f {
	float x, y;

	vec2f operator+(const vec2f& other) const {
		return {
			x + other.x,
			y + other.y
		};
	}

	vec2f operator-(const vec2f& other) const {
		return {
			x - other.x,
			y - other.y
		};
	}

	vec2f operator*(const float& other) const {
		return {
			x * other,
			y * other
		};
	}

	vec2f normalized() const {
		vec2f v = *this;

		float length = sqrt( pow(v.x, 2.0f) + pow(v.y, 2.0f) );
		if (length == 0.0) length = 1.0;

		v = v * (1.0f / length);

		return v;
	}
};

struct vec3i {
	int x, y, z;

	vec3i operator+(const vec3i& other) const {
		return {
			x + other.x,
			y + other.y,
			z + other.z
		};
	}

	vec3i operator-(const vec3i& other) const {
		return {
			x - other.x,
			y - other.y,
			z - other.z
		};
	}
};
