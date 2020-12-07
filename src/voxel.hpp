#ifndef VOXEL_HPP
#define VOXEL_HPP

#include <vector>

typedef unsigned int NodeID;
typedef std::vector<int> NodeAddress;

// template <typename T>
class Voxel {
public:
	NodeID id;
	float value;
	void* data;

	Voxel (NodeID id) {
		this->id = id;

	}
	virtual ~Voxel () {}

	NodeID parent();
	float weight();

};

#endif
