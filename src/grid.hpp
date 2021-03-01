#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include "voxel.hpp"
#include "vertex.hpp"
#include "mesh.hpp"

namespace Brutus {

	class Grid {
	private:
		// std::vector< std::vector< std::vector<Voxel> > > grid;
		std::vector<Voxel> voxels;

		Vertex getVertexDelta(int voxX, int voxY, int voxZ);
		bool voxelInGrid(int x, int y, int z);
		void lerp(int x0, int y0, int z0, int x1, int y1, int z1, float& n, int& d);

	public:
		unsigned int sizeX, sizeY, sizeZ;

		void resize();
		Voxel getVoxel(int x, int y, int z);
		void setVoxel(int x, int y, int z, int value);
		Mesh generateMesh();

		Grid(unsigned int sizeX, unsigned int sizeY, unsigned int sizeZ);
		virtual ~Grid ();

	};

}

#endif
