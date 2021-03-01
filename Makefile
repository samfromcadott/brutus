CXX = g++

build:
	$(CXX) src/grid.cpp tests/test.cpp -o bin/objtest

clean:
	del *.exe
