#include "mesh.h"
#include <cstdio>

Mesh::Mesh() {
	faces_ = list<Face*>();
	half_edges_ = list<HalfEdge*>();
	vertices_ = list<Vertex*>();
}

Mesh::~Mesh() {
	for (Face *f : faces_)
		delete f;
	faces_.clear();
	for (HalfEdge *e : half_edges_)
		delete e;
	half_edges_.clear();
	for (Vertex *v : vertices_)
		delete v;
	vertices_.clear();
}

/*simple version: add new vertex at the end of the vertex list*/
void Mesh::AddVertex(Vertex *v) {
	vertices_.push_back(v);
}

void Mesh::ConnectVertices(Vertex *v1, Vertex *v2) {

}