#include "grid.hpp"
#include "voxel.hpp"

Brutus::Grid::Grid(unsigned int sizeX, unsigned int sizeY, unsigned int sizeZ) {
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->sizeZ = sizeZ;

	voxels.resize(sizeX*sizeY*sizeZ);

}

Brutus::Grid::~Grid() {

}

Brutus::Voxel Brutus::Grid::getVoxel(int x, int y, int z) {
	return voxels[x*sizeY*sizeZ + y*sizeZ + z];

}
