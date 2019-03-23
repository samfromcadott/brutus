extends Spatial

export(Material) var mat
export var voxels = [Vector3(1, 1, 1), Vector3(1, 1, 2)]
export(Vector3) var maxSize = Vector3(10, 10, 10)
export(float) var sideLength = 1.0

var vertices = PoolVector3Array()

func _ready():
	generateMesh()

func generateMesh():
	for x in range(maxSize.x):
		for y in range(maxSize.y):
			for z in range(maxSize.z):
				if signChange( Vector3(x, y, z) ):
					var vert = Vector3(x + sideLength/2, y + sideLength/2, z + sideLength/2)
					print( 'Placed vertex at (' + str(vert.x) + ', ' + str(vert.y) + ', ' + str(vert.z) + ')' )
					vertices.append(vert)

	print(vertices.size(), " vertices created.")


func signChange(voxel):
	#Returns true if voxels around voxel are not all the same
	var truthTable = [
		voxel in voxels,
		voxel + Vector3(0,0,1) in voxels,
		voxel + Vector3(0,1,0) in voxels,
		voxel + Vector3(1,0,0) in voxels,
		voxel + Vector3(1,0,1) in voxels,
		voxel + Vector3(1,1,0) in voxels,
		voxel + Vector3(0,1,1) in voxels,
		voxel + Vector3(1,1,1) in voxels
	]
	return truthTable != [true ,true ,true ,true ,true ,true ,true ,true] and truthTable != [false ,false ,false ,false ,false ,false ,false ,false]
	# return voxel in voxels or voxel + Vector3(0,0,1) in voxels or voxel + Vector3(0,1,0) in voxels or voxel + Vector3(1,0,0) in voxels or voxel + Vector3(1,0,1) in voxels or voxel + Vector3(1,1,0) in voxel + Vector3(0,1,1) in voxels or voxel + Vector3(1,1,1) in voxels
