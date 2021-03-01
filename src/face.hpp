#ifndef FACE_HPP
#define FACE_HPP

namespace Brutus {

	class Face {
	public:
		int v0, v1, v2; // Geometric vertecies
		int n0, n1, n2; // Normals

		Face(int v0, int n0, int v1, int n1, int v2, int n2) {
			this->v0 = v0;
			this->v1 = v1;
			this->v2 = v2;

			this->n0 = n0;
			this->n1 = n1;
			this->n2 = n2;

		}

	};

}

#endif
