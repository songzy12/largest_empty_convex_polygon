#ifndef VERTEX_H
#define VERTEX_H

#include <utility>
#include <deque>
using namespace std;

class HalfEdge;

class Vertex
{
public:
	Vertex();
	~Vertex();

	HalfEdge* half_edge() { return half_edge_; }
	void set_half_edge(HalfEdge *half_edge) { half_edge_ = half_edge; }

	pair<double, double> point() { return point_; }
	void set_point(pair<double, double> point) { point_ = point; }

	deque<Vertex*>* queue2store() { return &queue2store_; }
	void set_queue2store(deque<Vertex*>* queue2store) { queue2store_ = *queue2store; }

private:
	HalfEdge *half_edge_;
	pair<double, double> point_;
	/*to store the starting points of the incoming edges of this vertex */
	deque<Vertex*> queue2store_;
};

#endif