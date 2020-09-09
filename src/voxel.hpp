#ifndef VOXEL_HPP
#define VOXEL_HPP

typedef unsigned int NodeID;

template <class T>
class Voxel {
public:
	NodeID id;
	float value;
	T data;

	Node (NodeID id);
	virtual ~Node ();

	NodeID parent();

};

#endif
