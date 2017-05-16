#ifndef HALFEDGE_H
#define HALFEDGE_H
#include "vertex.h"
#include "face.h"

class HalfEdge
{
public:
	HalfEdge();
	~HalfEdge();
	
	Vertex* origin() { return origin_; }
	void set_origin(Vertex *origin) { origin_ = origin; }
	Face* face() { return face_; }
	void set_face(Face *face) { face_ = face; }
	HalfEdge* twin() { return twin_; }
	void set_twin(HalfEdge *twin) { twin_ = twin; }
	HalfEdge* next() { return next_; }
	void set_next(HalfEdge *next) { next_ = next; }
	HalfEdge* prev() { return prev_; }
	void set_prev(HalfEdge *prev) { prev_ = prev; }

private:
	Vertex *origin_;//2017-05-13 修改by zyx,原 target_
	Face *face_;
	HalfEdge *twin_;//得到另外一个面
	HalfEdge *next_;
	HalfEdge *prev_;
};

#endif