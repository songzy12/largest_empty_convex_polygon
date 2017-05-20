#ifndef MESH_H
#define MESH_H
#include "vertex.h"
#include "half_edge.h"
#include "lecp_doc.h"
#include <list>

using namespace std;

class Mesh
{
public:
	Mesh();
	~Mesh();

	list<Vertex*> vertices() { return vertices_; }
	list<HalfEdge*> edges() { return half_edges_; }

	/*store all directed edges from low_index to high_index in vg*/
	vector<list<pair<Vertex*, Vertex*>>>* all_edges(){ return &all_edges_; }

	void AddVertex(Vertex *v);
	void ConnectVertices(Vertex *v1, Vertex *v2);
	void AddLine(LECP_Point *point);
	void init();//初始化，bounding box, one face,4 half_edge,4 vertex
	void clear();
	HalfEdge*  getIntersectHalfEdge(double a,double b);
	Vertex* intersectWithBoundingBox(HalfEdge* tmp,double a,double b);

	//得到新插入的直线和当前面的交点.
	//从newHalfEdge的next开始判断是否有交点
	//返回的newIntersection中保存交点Vertex
	//返回的intersectHalfEdge保存当前face的哪条half_edge和直线y=ax-b相交
	HalfEdge* getIntersection(double a, double b, HalfEdge newHalf, Vertex &newIntersection, HalfEdge &intersectHalfEdgeRight);
	bool onBoundingBox(Vertex* newIntersection);

	HalfEdge* getIntersectBundingBox(double a, double b, Vertex &vertex);

	//poH和neH是上一步产生的新边对应的两个half_edge,在下一步需要更新某些字段
	//newPoH和new neH是该步新产生的边对应的两个half_edge
	void dealWithNormalIntersection(Vertex* newIntersection, HalfEdge* intersectHalfEdgeLeft, HalfEdge* intersectHalfEdgeRight, HalfEdge* newPoH, HalfEdge* newNeH);//处理中间的交点

	void  postCalcPolarAngle();

private:
	list<Vertex*> vertices_;
	list<HalfEdge*> half_edges_;

	/*store all directed edges from low_index to high_index in vg*/
	vector<list<pair<Vertex*, Vertex*>>> all_edges_;

	list<HalfEdge*> boundingBox;//保存边界的HalfEdge,用以确定新插入的直线首先穿过哪个face

public:
	vector<list<Vertex*>> sortedVector;
	vector<list<LECP_Point*>> sortedPoint;
	vector<LECP_Point*> points;
};

#endif

