#ifndef OCTREE_HPP
#define OCTREE_HPP

#include <unordered_map>
#include <vector>
#include "voxel.hpp"
#include "vertex.hpp"

class Octree {
private:
	std::unordered_map< NodeID, Voxel > voxels;

public:
	NodeID getNodeID(std::vector<int> voxel);

	Voxel& operator()(std::vector<int> voxel);
	Voxel operator()(std::vector<int> voxel) const;

	void subdivide(std::vector<int> voxel);
	void collapse(std::vector<int> voxel);

	Octree ();
	virtual ~Octree ();

};

#endif
