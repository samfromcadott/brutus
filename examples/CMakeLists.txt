include_directories(shared)

add_subdirectory(raylib)

add_executable(terrain
	terrain/terrain.cc
	terrain/height.cc
	terrain/fly_camera.cc

	shared/noise.cc
	shared/mesh.cc
)

add_executable(viewer
	viewer/viewer.cc
	viewer/camera.cc
	viewer/editing.cc
	viewer/mesh.cc
	viewer/sdf.cc
)

target_link_libraries(terrain raylib)
target_link_libraries(viewer raylib)
