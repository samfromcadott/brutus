#ifndef OCTREE_HPP
#define OCTREE_HPP

#include <unordered_map>
#include <vector>
#include <array>
#include "voxel.hpp"
#include "vertex.hpp"

typedef unsigned int NodeID;
typedef std::vector<int> NodeAddress;

class Octree {
private:
	std::unordered_map< NodeID, Voxel > voxels;

public:
	NodeID getNodeID(NodeAddress voxel);

	Voxel& operator()(NodeAddress voxel);

	void subdivide(NodeAddress voxel);
	void collapse(NodeAddress voxel);
	NodeID parent(NodeAddress voxel); // Returns the parent of voxel
	std::array<NodeID, 8> children(NodeAddress voxel); // Returns the children of voxel

	Octree ();
	virtual ~Octree ();

};

#endif
