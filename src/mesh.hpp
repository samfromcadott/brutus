#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include "vertex.hpp"
#include "face.hpp"

namespace Brutus {

	struct Mesh {
		std::vector<Vertex> vertex;
		std::vector<Vertex> normal;
		std::vector<Face> face;

	};

}

#endif
