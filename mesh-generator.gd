extends Spatial

export(Material) var mat
export var voxels = [Vector3(1, 2, 1), Vector3(1, 1, 2)]
export(Vector3) var maxSize = Vector3(10, 10, 10)
export(float) var sideLength = 1.0

var vertices = []
var faces = []

func _ready():
	generateMesh()

func generateMesh():
	for x in range(maxSize.x):
		for y in range(maxSize.y):
			for z in range(maxSize.z):
				#Generate vertices
				if signChange( Vector3(x, y, z) ):
					var vert = Vector3(x + sideLength/2, y + sideLength/2, z + sideLength/2)
					print( 'v ' + str(vert.x) + ' ' + str(vert.y) + ' ' + str(vert.z))
					vertices.append(vert)

	#Generate faces
	for voxel in voxels:
		var newFaces = makeFaces( voxel )
		for face in newFaces:
			print('f ' + str(face[0] + 1) + ' ' + str(face[1] + 1) + ' ' + str(face[2] + 1) + ' ' + str(face[3] + 1))
			faces.append(face)


	print('#', vertices.size(), " vertices created.")
	print('#', faces.size(), " faces created.")


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


func makeFaces(voxel):
	var filledFaces = [] #Array of faces active on the voxel
	var faces = [
		[Vector3(2, 2, 2), Vector3(2, -2, 2), Vector3(-2, -2, 2), Vector3(-2, 2, 2)],
		[Vector3(2, 2, 2), Vector3(2, -2, 2), Vector3(2, 2, -2), Vector3(2, -2, -2)],
		[Vector3(2, 2, 2), Vector3(2, 2, -2), Vector3(-2, 2, -2), Vector3(-2, 2, 2)],
		[Vector3(2, 2, -2), Vector3(-2, 2, -2), Vector3(-2, -2, -2), Vector3(2, -2, -2)],
		[Vector3(-2, -2, 2), Vector3(-2, 2, 2), Vector3(-2, 2, -2), Vector3(-2, -2, -2)],
		[Vector3(2, -2, 2), Vector3(-2, -2, 2), Vector3(-2, -2, -2), Vector3(2, -2, -2)]
	]

	for face in faces:
		var currentFace = [] #Array of vertices in current face

		#Check if all vertices of the face are present
		for v in face:
			var vertex = voxel + (Vector3(sideLength, sideLength, sideLength) / v)
			if vertex in vertices:
				currentFace.append( vertices.bsearch(vertex) )

		if currentFace.size() == 4:
			filledFaces.append(currentFace)

	return filledFaces
