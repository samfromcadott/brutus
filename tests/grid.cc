#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <fstream>

#include <brutus/brutus.h>

TEST_CASE("Grid constructor/deconstructor") {
	Brutus::Grid grid(2, 2, 2); // Constructor
	Brutus::Grid grid2; // Default constructor
}

TEST_CASE("Copy assignment") {
	Brutus::Grid grid;
	grid = Brutus::Grid(1,1,3);
}

TEST_CASE("Set voxel weight") {
	Brutus::Grid grid(2, 2, 2);

	grid(1,1,1).weight = 2;
	CHECK(grid(1,1,1).weight == 2);
}

TEST_CASE("Total size") {
	Brutus::Grid grid(1, 2, 3);

	auto [x, y, z] = grid.total_size();

	CHECK(x == 8);
	CHECK(y == 16);
	CHECK(z == 24);
}

TEST_CASE("Chunk size") {
	Brutus::Grid grid(1, 2, 3);

	auto [x, y, z] = grid.chunk_size();

	CHECK(x == 1);
	CHECK(y == 2);
	CHECK(z == 3);
}
