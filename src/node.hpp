#ifndef NODE_HPP
#define NODE_HPP

class Node {
private:
	Node* parent;
	Node* child;
	int value; //Used to determine vertex location
	void* data; //Optional aditional data
	unsigned char level; //Level of the node in the tree
	int center[3]; //Location of the node

public:
	Node ();
	virtual ~Node ();

	void subdivide(); //Subdivides the node into 8 child nodes

	void collapse(); //Removes all child nodes

	Node* root(); //Gets the root of the node structure

	unsigned int width(); //Returns the spatial width of the node

};

#endif
