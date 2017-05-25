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

	//the first is the intersection point, and the second is the corresponding point user input.
	vector<pair<LECP_Point*,LECP_Point*>> AddLine(LECP_Point *point);// return the intersections

	void init();//初始化，bounding box, one face,4 half_edge,4 vertex
	void clear();
	HalfEdge*  getIntersectHalfEdge(double a,double b);
	Vertex* intersectWithBoundingBox(HalfEdge* tmp,double a,double b);

	//得到新插入的直线和当前面的交点.
	//从newHalfEdge的next开始判断是否有交点
	//返回的newIntersection中保存交点Vertex
	//返回的intersectHalfEdge保存当前face的哪条half_edge和直线y=ax-b相交
	HalfEdge* getIntersection(double a, double b, HalfEdge newHalf, Vertex &newIntersection);
	bool onBoundingBox(Vertex* newIntersection);

	HalfEdge* getIntersectBundingBox(double a, double b, Vertex &vertex);

	//poH和neH是上一步产生的新边对应的两个half_edge,在下一步需要更新某些字段
	//newPoH和new neH是该步新产生的边对应的两个half_edge
	void dealWithNormalIntersection(Vertex* newIntersection, HalfEdge* intersectHalfEdgeLeft, HalfEdge* intersectHalfEdgeRight, HalfEdge* newPoH, HalfEdge* newNeH);//处理中间的交点

	void  postCalcPolarAngle();

	void postAjustIntersections(list<LECP_Point*>  &return_intersections);// 2017-05-24添加
	void postAjustIntersections(vector<pair<LECP_Point*, LECP_Point*>>  &return_intersections);// 2017-05-24添加

	// Added by zyx,2017-05-25
	// return the new halfEdge
	HalfEdge* splitEdge(HalfEdge* half_edge,Vertex* vertex);
	void connectTwoNewVertices(HalfEdge* h1,HalfEdge* h2,LECP_Point *point);

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

