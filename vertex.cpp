#include "vertex.h"

Vertex::Vertex() {

}

Vertex::Vertex(double x, double y) {
	point_ = { x, y };
}

Vertex::Vertex(double x, double y, int index) {
	point_ = { x, y };
	index_ = index;
}

Vertex::Vertex(pair<int, int> p, int index) {
	point_ = p;
	index_ = index;
}

Vertex::~Vertex() {

}