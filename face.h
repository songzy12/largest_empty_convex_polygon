#ifndef Face_H
#define Face_H

class HalfEdge;

//无洞
class Face
{
public:
	Face();
	~Face();

	HalfEdge* half_edge() { return half_edge_; }//面的半边，最左侧顶点对应的half_edge
	void set_half_edge(HalfEdge *half_edge) { half_edge_ = half_edge; }

private:
	HalfEdge *half_edge_;
};

#endif