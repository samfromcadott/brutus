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

NodeID Octree::getNodeID(NodeAddress voxel) {
	// TODO: Check that node is in octree
	NodeID id = 1; // The root node has an ID of 1

	for(auto&& v : voxel) {
		id = (id << 3) + v; // IDs are composed of concatinations of each individual ID

	}

	return id;

}

Voxel& Octree::operator()(NodeAddress voxel) {
	return voxels.at( getNodeID(voxel) );

}

void Octree::subdivide(NodeAddress voxel) {
	NodeID v = getNodeID(voxel);

	for (int i = 0; i < 8; i++) { // Add all 8 children
		NodeID id = (v << 3) + i;
		voxels.emplace( id, Voxel(id) );

	}

}

void Octree::collapse(NodeAddress voxel) {


}
