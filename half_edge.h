#ifndef HALFEDGE_H
#define HALFEDGE_H
#include "vertex.h"
#include "face.h"

class HalfEdge
{
public:
	HalfEdge();
	~HalfEdge();
	
	Vertex* target() { return target_; }
	void set_target(Vertex *target) { target_ = target; }
	Face* face() { return face_; }
	void set_face(Face *face) { face_ = face; }
	HalfEdge* twin() { return twin_; }
	void set_twin(HalfEdge *twin) { twin_ = twin; }
	HalfEdge* next() { return next_; }
	void set_next(HalfEdge *next) { next_ = next; }
	HalfEdge* prev() { return prev_; }
	void set_prev(HalfEdge *prev) { prev_ = prev; }

private:
	Vertex *target_;
	Face *face_;
	HalfEdge *twin_;
	HalfEdge *next_;
	HalfEdge *prev_;
};

#endif