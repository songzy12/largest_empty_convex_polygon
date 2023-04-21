#ifndef HALFEDGE_H
#define HALFEDGE_H
#include "vertex.h"
#include "point.h"

class HalfEdge
{
public:
	HalfEdge();
	HalfEdge(Vertex *origin, Vertex *target); 
	~HalfEdge();
	
	Vertex* origin() { return origin_; }
	void set_origin(Vertex *origin) { origin_ = origin; }

	HalfEdge* twin() { return twin_; }
	void set_twin(HalfEdge *twin) { twin_ = twin; }
	HalfEdge* next() { return next_; }
	void set_next(HalfEdge *next) { next_ = next; }
	HalfEdge* prev() { return prev_; }
	void set_prev(HalfEdge *prev) { prev_ = prev; }

	// origin and target are both used for convex chain
	Vertex* target() { return target_; }
	void set_target(Vertex *target) { target_ = target; }
	int L() { return L_; }
	void set_L(int L) { L_ = L; }
private:
	Vertex *origin_;//2017-05-13 修改by zyx,原 target_
	HalfEdge *twin_;//得到另外一个面
	HalfEdge *next_;
	HalfEdge *prev_;

	// used for convex chain
	Vertex *target_; // the Vertex that is pointed to
	int L_; // only used for convex chain
public:
	HalfEdge *prev_chain_;

	LECP_Point *lecp_point;//which LECP_Point(line) the half_edge belongs to
};

#endif