#ifndef VOXEL_HPP
#define VOXEL_HPP

typedef unsigned int NodeID;

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

};

#endif
