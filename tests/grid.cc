#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

#include <brutus/brutus.h>

TEST_CASE("Grid constructor/deconstructor") {
	Brutus::Grid grid(2, 2, 2); // Constructor
	Brutus::Grid grid2; // Default constructor
	grid2 = Brutus::Grid(1,1,3); // Copy assignment
}

TEST_CASE("Access chunk") {
	Brutus::Grid grid(2, 2, 2);

	Brutus::Chunk& chunk = grid(0,0,0);
	chunk(1,1,1).weight = 2;
	CHECK(chunk(1,1,1).weight == 2);
	CHECK(chunk(1,1,2).weight == 0);
}
