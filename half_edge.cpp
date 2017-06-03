#include "half_edge.h"

HalfEdge::HalfEdge() {
	L_ = 0;
	prev_chain_ = nullptr;
	lecp_point = nullptr;
}

HalfEdge::HalfEdge(Vertex *origin, Vertex *target) {
	origin_ = origin;
	target_ = target;
	L_ = 0;
	prev_chain_ = nullptr;
	lecp_point = nullptr;
}

HalfEdge::~HalfEdge() {

}