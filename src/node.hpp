#ifndef NODE_HPP
#define NODE_HPP
#define SUBDIVS 8

typedef unsigned int NodeID;

class Node {
public:
	NodeID id;

	Node (NodeID id);
	virtual ~Node ();

	NodeID parent();

};

template <class T>
class Voxel : public Node {
public:
	float value;
	T data;

};

template <class V>
class Vertex {
public:
	V engineVertex; // A refernece to the engine's vertex class

	void setLoc(float x, float y, float z);
	void setNormal(float x, float y, float z);

};

// class Node {
// private:
// 	class Branch {
// 	public:
// 		Node* leaf[SUBDIVS];
//
// 		~Branch();
// 	};
//
// 	Branch* branch;
// 	float width; //Spatial width of the node
// 	float center[3]; //Location of the node
//
// public:
// 	Node* parent;
// 	double value; //Used to determine vertex location
// 	void* data; //Optional aditional data
//
// 	Node (Node* parent, int value, float width, float* center);
// 	virtual ~Node ();
//
// 	Node* &operator()(int c...); //Used to access child nodes
// 	void subdivide(); //Subdivides the node into 8 child nodes
// 	void collapse(); //Removes all child nodes
// 	Node* root(); //Gets the root of the node structure
// 	int level(); //Returns the nodes level in the node structure
//
// };

#endif
