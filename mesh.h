#ifndef MESH_H
#define MESH_H
#include "face.h"
#include "vertex.h"
#include "half_edge.h"
#include <list>

using namespace std;

class Mesh
{
public:
	Mesh();
	~Mesh();

	list<Face*> faces() { return faces_; }
	list<Vertex*> vertices() { return vertices_; }
	list<HalfEdge*> edges() { return half_edges_; }

	void AddVertex(Vertex *v);
	void ConnectVertices(Vertex *v1, Vertex *v2);
private:
	list<Face*> faces_;
	list<Vertex*> vertices_;
	list<HalfEdge*> half_edges_;
};

#endif