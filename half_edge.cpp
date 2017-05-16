#include "half_edge.h"

HalfEdge::HalfEdge() {
	L_ = 0;
}

HalfEdge::HalfEdge(Vertex *origin, Vertex *target) {
	origin_ = origin;
	target_ = target;
	L_ = 0;
}

HalfEdge::~HalfEdge() {

}