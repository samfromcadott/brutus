cmake_minimum_required(VERSION 3.4)
set(CMAKE_CXX_STANDARD 17)

project(brutus)

include_directories(include)

option(BRUTUS_BUILD_TESTS "Build the Brutus unit tests" ON)
option(BRUTUS_BUILD_EXAMPLES "Build the Brutus examples" ON)

if (BRUTUS_BUILD_TESTS)
	add_subdirectory(tests)
endif()

if (BRUTUS_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()
