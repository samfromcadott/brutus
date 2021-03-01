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

void Brutus::Grid::setVoxel(int x, int y, int z, int value) {
	Voxel v;
	v.value = value;
	voxels[x*sizeY*sizeZ + y*sizeZ + z] = v;

}

Brutus::Mesh Brutus::Grid::generateMesh() {
	// Create an empty mesh object
	Mesh m;

	for (int x = 0; x < sizeX; x++)
	for (int y = 0; y < sizeY; y++)
	for (int z = 0; z < sizeZ; z++)
	if (getVoxel(x, y, z).value <= 0) {
		// Compute the delta of each vertex
		Vertex v000 = getVertexDelta(x-1, y-1, z-1);
		Vertex v001 = getVertexDelta(x-1, y-1, z  );
		Vertex v010 = getVertexDelta(x-1, y  , z-1);
		Vertex v011 = getVertexDelta(x-1, y  , z  );
		Vertex v100 = getVertexDelta(x  , y-1, z-1);
		Vertex v101 = getVertexDelta(x  , y-1, z  );
		Vertex v110 = getVertexDelta(x  , y  , z-1);
		Vertex v111 = getVertexDelta(x  , y  , z  );

		// If an adjacent voxel value is >0 there should be faces

		// Append new face data to the mesh
		m.vertex.push_back(v000);
		m.vertex.push_back(v001);
		m.vertex.push_back(v010);
		m.vertex.push_back(v011);
		m.vertex.push_back(v100);
		m.vertex.push_back(v101);
		m.vertex.push_back(v110);
		m.vertex.push_back(v111);

	}

	// Return mesh
	return m;

}


Brutus::Vertex Brutus::Grid::getVertexDelta(int voxX, int voxY, int voxZ) {
	// vox* represent voxel location
	int count = 0; // Number of verticies to average
	float sumX, sumY, sumZ; // Sums for each axis

	// For each pair check if they are both in the grid and have opposite signs
	// Lerp between them
	// Increment count
	// X-AXIS
	lerp(voxX,voxY,voxZ, voxX+1,voxY,voxZ, sumX, count);
	lerp(voxX,voxY+1,voxZ, voxX+1,voxY+1,voxZ, sumX, count);
	lerp(voxX,voxY,voxZ+1, voxX+1,voxY,voxZ+1, sumX, count);
	lerp(voxX,voxY+1,voxZ+1, voxX+1,voxY+1,voxZ+1, sumX, count);

	// Y-AXIS
	lerp(voxX,voxY,voxZ, voxX,voxY+1,voxZ, sumY, count);
	lerp(voxX+1,voxY,voxZ, voxX+1,voxY+1,voxZ, sumY, count);
	lerp(voxX,voxY,voxZ+1, voxX,voxY+1,voxZ+1, sumY, count);
	lerp(voxX+1,voxY,voxZ+1, voxX+1,voxY+1,voxZ+1, sumY, count);

	// Z-AXIS
	lerp(voxX,voxY,voxZ, voxX,voxY,voxZ+1, sumZ, count);
	lerp(voxX+1,voxY,voxZ, voxX+1,voxY,voxZ+1, sumZ, count);
	lerp(voxX,voxY+1,voxZ, voxX,voxY+1,voxZ+1, sumZ, count);
	lerp(voxX+1,voxY+1,voxZ, voxX+1,voxY+1,voxZ+1, sumZ, count);

	// Average all verticies
	float avgX, avgY, avgZ;
	if (count > 0) {
		avgX = sumX/count;
		avgY = sumY/count;
		avgZ = sumZ/count;

	}

	return Vertex(avgX*voxX+0.5, avgY*voxY+0.5, avgZ*voxZ+0.5);

}

void Brutus::Grid::lerp(int x0, int y0, int z0, int x1, int y1, int z1, float& n, int& d) {
	// Check if v0 and v1 are in the grid
	if ( voxelInGrid(x0,y0,z0) && voxelInGrid(x1,y1,z1) ) {
		float v0 = getVoxel(x0,y0,z0).value;
		float v1 = getVoxel(x1,y1,z1).value;

		// Check if v0 and v1 have opposite signs
		if ( (v0<=0) != (v1<=0) ) {
			n += -v0/( v1 - v0 ); // Linearly iterpolate the values
			d++; // Increment the count

		}

	}

}

bool Brutus::Grid::voxelInGrid(int x, int y, int z) {
	bool xIn = x >= 0 && x < sizeX;
	bool yIn = y >= 0 && y < sizeY;
	bool zIn = z >= 0 && z < sizeZ;
	return xIn && yIn && zIn;

}
