The Marching Cubes Algorithm
==============

Marching cubes is an algorithm for generating a mesh from a signed distance field (SDF). The SDF is a uniform grid of signed values representing the distance to the nearest surface.

Voxels
--------------

Voxels are a structure of two 8-bit integers. `weight` is a signed integer that represents the voxel's distance to the surface. Negative values are below the surface. `data` is an unsigned integer that the user can use to store additional data, such as terrain type. It has no effect on mesh generation

Chunks
--------------

`Chunk`s are containers that store `Voxel`s. The world will generally be made of a number of `Chunk`s. The array is a cube with an edge length of `BRUTUS_CHUNK_SIZE`, which has a default value of 8. They're functionally a 3D array of `Voxel`s. `Mesh`es are generated on a per-`Chunk` basis since whole-world generation can be costly if terrain changes are frequent.

Grid
--------------

`Grid` is the class that contains `Chunk`s. This is the class that users should instantiate directly. `Grid` also a 3D array but unlike `Chunk`s they can be of any size.

Mesh Generation
--------------

Mesh generation involves finding the edges of the SDF where the values switch from negative to positive and using linear interpolation to place a vertex where the implicit value is 0.

Neighborhood Cases
--------------

A neighborhood is a set of 8 voxels adjacent to each other. The `Case` of the neighborhood is a bitfield that encodes what voxels are negative. If all voxels in a neighborhood have the same sign then no mesh is generated for it. The origin of a neighborhood is the voxel with the lowest location on each axis.

During mesh generation `Grid` loops over all voxels, determines the case of it, then generates the faces for that neighborhood. Since generating the faces for each case is complex and time consuming, Brutus, like most marching cubes implementations, uses precomputed lookup tables.

### Lookup Tables

Brutus uses three lookup tables for mesh generation.

* `case_face_count` contains the number of faces in each `Case`
* `case_faces` contains the faces for each `Case` defined by what grid edge the vertex lies on
* `edge_offsets` contains what voxels in a neighborhood (relative to origin) share an edge

Vertex Placement
--------------

Once the faces of a neighborhood have been found, each vertex location is calculated. `edge_offsets` is used to get the voxels that share an edge. Since voxels with a vertex between them always have opposite signs, linear interpolation is used to approximate where the SDF is zero. This is used as the location of the vertex.

Normal Generation
--------------

Normals are calculated if the value of `calculate_normals` is `true`. Normals generation is done by finding the gradient of the function at the voxel the vertex originates from. The gradient is a vector of the difference in weight for the adjacent voxels on each axis.

Sources
--------------

* [Polygonising a scalar field](http://paulbourke.net/geometry/polygonise/) by Paul Bourke
* [Generating Complex Procedural Terrains Using the GPU](https://developer.nvidia.com/gpugems/gpugems3/part-i-geometry/chapter-1-generating-complex-procedural-terrains-using-gpu) by Ryan Geiss in GPU Gems 3
