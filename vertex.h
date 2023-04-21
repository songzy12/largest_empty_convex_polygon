#ifndef VERTEX_H
#define VERTEX_H

#include <utility>
#include <deque>
#include <vector>
using namespace std;

class HalfEdge;
class Vertex
{
public:
	Vertex();
	Vertex(double x, double y);
	Vertex(pair<int, int> p, int index);
	Vertex(double x, double y, int index);
	~Vertex();

	HalfEdge *half_edge() { return half_edge_; } // 该顶点对应的半边
	void set_half_edge(HalfEdge *half_edge) { half_edge_ = half_edge; }

	pair<double, double> point() { return point_; } // 顶点坐标
	void set_point(pair<double, double> point) { point_ = point; }

	int index() { return index_; }
	void set_index(int index) { index_ = index; }

	// used for visible graph and convex chain
	deque<Vertex*> Q_;

	vector<HalfEdge*> incoming_edges_; 
	vector<HalfEdge*> outgoing_edges_;

	HalfEdge* prev_;

	// used in unique()
	bool operator == (Vertex v) {
		if (v.point().first == point_.first && v.point().first == point_.second)
			return true;
		else 
			return false;
	}
private:
	HalfEdge *half_edge_; // 每个Vertex对应多个half_edge,选择一个作为origin

	/*only for test&debug ,can be used in animation*/
	int index_;
	pair<double, double> point_;
};

#endif
