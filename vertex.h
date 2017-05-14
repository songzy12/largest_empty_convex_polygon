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

	HalfEdge* half_edge() { return half_edge_; }//该顶点对应的半边
	void set_half_edge(HalfEdge *half_edge) { half_edge_ = half_edge; }
	pair<double, double> point() { return point_; }//顶点坐标
	void set_point(pair<double, double> point) { point_ = point; }

private:
	HalfEdge *half_edge_;//每个Vertex对应多个half_edge,选择一个作为origin
	pair<double, double> point_;
};

#endif