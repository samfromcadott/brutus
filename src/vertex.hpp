#ifndef VERTEX_HPP
#define VERTEX_HPP

template <class V>
class Vertex {
private:
	V engineVertex; // A refernece to the engine's vertex class

public:
	void setLoc(float x, float y, float z);
	void setNormal(float x, float y, float z);

};

#endif
