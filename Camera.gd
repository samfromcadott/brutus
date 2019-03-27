extends Spatial

export var rotationSpeed = 0.3
export var zoomSpeed = 0.01
export var maxZoom = 0.2

var rot = Vector2(0, 0)
var zoom = 0

func _ready():
	# Called every time the node is added to the scene.
	# Initialization here
	pass

func _unhandled_input(event):
	if event is InputEventMouseMotion and Input.is_action_pressed('camera_rotate'):
		rot.y += event.relative.x * rotationSpeed
		rot.x += event.relative.y * rotationSpeed

		# rot.y = clamp(rot.y, -90, 90)
		rot.x = clamp(rot.x, -90, 90)

		var trans = Transform()

		trans = trans.rotated(Vector3(1,0,0), -rot.x * PI / 180.0)
		trans = trans.rotated(Vector3(0,1,0), -rot.y * PI / 180.0)

		get_node("Base").transform.basis = trans.basis

	if event is InputEventMouseButton and event.button_index == BUTTON_WHEEL_UP:
		if zoom < maxZoom:
			zoom += zoomSpeed
			get_node("Base/Camera").translation.z += -zoom

	if event is InputEventMouseButton and event.button_index == BUTTON_WHEEL_DOWN:
		if zoom > 0:
			zoom -= zoomSpeed
			get_node("Base/Camera").translation.z += zoom
