#include <cmath>
#include "voxel.hpp"

// template <class T>
// Voxel<T>::Voxel (NodeID id) {
// 	this->id = id;
//
// }
//
// template <class T>
// Voxel<T>::~Voxel () {
//
//
// }

float Voxel::weight() {
	// Returns the weight of the voxel's center based on the value of the voxel

	// values outside [-1, 1] are 1.0
	float x = (value > 1.0 || value < -1.0) ? 1.0 : std::abs(value);
	return ( (x-1)*(x-1) ) + 1;

}
