typedef int8_t VoxelWeight;
typedef uint8_t VoxelData;

struct Voxel {
	VoxelWeight weight = 0; ///< Used for mesh generation. Negative values are inside the mesh.
	VoxelData data = 0; ///< Additional data for the voxel, such as terrain type.
};

const VoxelWeight weight_min = -128;
const VoxelWeight weight_max = 127;
