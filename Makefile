CXX = g++

build:
	$(CXX) -c src/grid.cpp -o bin/grid.o

clean:
	del *.exe
