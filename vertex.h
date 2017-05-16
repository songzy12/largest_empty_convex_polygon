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

	HalfEdge* half_edge() { return half_edge_; }//该顶点对应的半边
	void set_half_edge(HalfEdge *half_edge) { half_edge_ = half_edge; }
	pair<double, double> point() { return point_; }//顶点坐标
	void set_point(pair<double, double> point) { point_ = point; }

	deque<Vertex*>* queue2store() { return &queue2store_; }
	void set_queue2store(deque<Vertex*>* queue2store) { queue2store_ = *queue2store; }

	int index() { return index_; }
	void set_index(int index) { index_ = index; }

private:
	HalfEdge *half_edge_;//每个Vertex对应多个half_edge,选择一个作为origin
	pair<double, double> point_;

	/*to store the starting points of the incoming edges of this vertex */
	deque<Vertex*> queue2store_;

	/*only for test&debug ,can be used in animation*/
	int index_;
};

#endif
