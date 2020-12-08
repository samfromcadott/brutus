#include "face.hpp"

using namespace Brutus;

Face::Face(int v0, int n0, int v1, int n1, int v2, int n2) {
	this->v0 = v0;
	this->v1 = v1;
	this->v2 = v2;

	this->n0 = n0;
	this->n1 = n1;
	this->n2 = n2;

}

Face::~Face() {

}
