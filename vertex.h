#ifndef VERTEX_H
#define VERTEX_H

#include <utility>

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

private:
	HalfEdge *half_edge_;
	pair<double, double> point_;
};

#endif