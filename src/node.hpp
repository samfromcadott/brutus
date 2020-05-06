#ifndef NODE_HPP
#define NODE_HPP
#define SUBDIVS 8

class Node {
private:
	class Branch {
	public:
		Node* leaf[SUBDIVS];

		~Branch();
	};

	Branch* branch;
	float width; //Spatial width of the node
	float center[3]; //Location of the node

public:
	Node* parent;
	short value; //Used to determine vertex location
	void* data; //Optional aditional data

	Node (Node* parent, int value, float width, float* center);
	virtual ~Node ();

	Node* &operator[](int i); //Used to access child nodes
	void subdivide(); //Subdivides the node into 8 child nodes
	void collapse(); //Removes all child nodes
	Node* root(); //Gets the root of the node structure
	int level(); //Returns the nodes level in the node structure

};

#endif
