#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include "voxel.hpp"
#include "vertex.hpp"

namespace Brutus {

	class Grid {
	private:
		// std::vector< std::vector< std::vector<Voxel> > > grid;
		std::vector<Voxel> voxels;

	public:
		unsigned int sizeX, sizeY, sizeZ;

		void resize();
		Voxel getVoxel(int x, int y, int z);

		Grid(unsigned int sizeX, unsigned int sizeY, unsigned int sizeZ);
		virtual ~Grid ();

	};

}

#endif
