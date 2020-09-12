#include <unordered_map>
#include <vector>
#include <iostream>
#include "voxel.hpp"
#include "vertex.hpp"
#include "octree.hpp"

Octree::Octree () {
	voxels.emplace( 1, Voxel(1) );

}

Octree::~Octree () {}

NodeID Octree::getNodeID(std::vector<int> voxel) {
	NodeID id = 1;

	for(auto&& v : voxel) {
		id = (id << 3) + v;

	}

	return id;

}

Voxel& Octree::operator()(std::vector<int> voxel) {
	return voxels.at( getNodeID(voxel) );

}

// Voxel Octree::operator()(std::vector<int> voxel) const {
// 	return voxels.at( getNodeID(voxel) );
//
// }

void Octree::subdivide(std::vector<int> voxel) {
	NodeID v = getNodeID(voxel);

	for (int i = 0; i < 8; i++) {
		NodeID id = (v << 3) + i;
		voxels.emplace( id, Voxel(id) );

	}

}

void Octree::collapse(std::vector<int> voxel) {


}
