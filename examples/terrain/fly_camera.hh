#pragma once

class FlyCamera {
public:
	float pitch = 0;
	float yaw = 0;
	Camera3D camera;

	FlyCamera();
	void update();
};
