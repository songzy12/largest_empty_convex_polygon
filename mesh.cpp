#include "mesh.h"
#include <cstdio>
#include<list>
using namespace std;

Mesh::Mesh() {
	faces_ = list<Face*>();
	half_edges_ = list<HalfEdge*>();
	vertices_ = list<Vertex*>();

	lecp_doc = new LECP_Doc();//存储全局变量和配置的document

	init();//DCEL初始化
}

Mesh::~Mesh() {
	clear();
}
void Mesh ::clear(){
	for (Face *f : faces_)
		delete f;
	faces_.clear();
	for (HalfEdge *e : half_edges_)
		delete e;
	half_edges_.clear();
	for (Vertex *v : vertices_)
		delete v;
	vertices_.clear();
}

/*simple version: add new vertex at the end of the vertex list*/
void Mesh::AddVertex(Vertex *v) {
	vertices_.push_back(v);
}

void Mesh::ConnectVertices(Vertex *v1, Vertex *v2) {

}

//屏幕上增加一个点，对应的对偶图中增加一条线
void Mesh::AddLine(double a, double b){
	//找到新插入的直线和bounding box的哪个线段相交
	HalfEdge *firstIntersect = getIntersectHalfEdge(a, b);

	//找到交点，并且更新boudingBox
	Vertex *v = intersectWithBoundingBox(firstIntersect, a, b);
	
	HalfEdge* newHalf = new HalfEdge();
	newHalf->set_face( firstIntersect->face());
	newHalf->set_next (firstIntersect->next()); 
	newHalf->set_origin( v);
	newHalf->set_prev(firstIntersect);
	
	v->set_half_edge(newHalf);

	vertices_.push_back(v);
	half_edges_.push_back(newHalf);
	boundingBox.push_back(newHalf);
	// end intersection with bouding box

	/*
	//沿着新产生的half_edge找到当前face中与直线y=ax-b有交点的half_edge
	HalfEdge* nextHalfEdge = newHalf->next();
	while (!intersaction(nextHalfEdge, a, b)){

	}
*/
}

//最外围的墙，no twins,翻不出去
void Mesh::init(){
	// init face
	Face *face = new Face();

	//init four vertex, which are the four window points. 

	Vertex *v1 = new Vertex();
	pair<double, double> p1;
	p1.first = 0;
	p1.second = 0;
	v1->set_point(p1);

	Vertex *v2 = new Vertex();
	pair<double, double> p2;
	p2.first = 0;
	p2.second = lecp_doc->windowHeight;
	v2->set_point(p2);

	Vertex *v3 = new Vertex();
	pair<double, double> p3;
	p3.first = lecp_doc->windowWidth;
	p3.second = lecp_doc->windowHeight;
	v3->set_point(p3);

	Vertex *v4 = new Vertex();
	pair<double, double> p4;
	p4.first = lecp_doc->windowWidth;
	p4.second = 0;
	v4->set_point(p4);

	// four half_edge
	HalfEdge *h1 = new HalfEdge();
	h1->set_origin(v1);
	h1->set_face(face);

	HalfEdge *h2 = new HalfEdge();
	h2->set_origin(v2);
	h2->set_face(face);

	HalfEdge *h3 = new HalfEdge();
	h3->set_origin(v3);
	h3->set_face(face);

	HalfEdge *h4 = new HalfEdge();
	h4->set_origin(v4);
	h4->set_face(face);

	// set the half_edges of each vertex
	v1->set_half_edge(h1);
	v2->set_half_edge(h2);
	v3->set_half_edge(h3);
	v4->set_half_edge(h4);

	//relation between the four half edges
	h1->set_next(h2);
	h1->set_prev(h4);

	h2->set_next(h3);
	h2->set_prev(h1);

	h3->set_next(h4);
	h3->set_prev(h2);

	h4->set_next(h1);
	h4->set_prev(h3);

	//set the left most point as the half edge of the face
	face->set_half_edge(h1);

	//add parameters to mesh
	faces_.push_back(face);
	
	vertices_.push_back(v1);
	vertices_.push_back(v2);
	vertices_.push_back(v3);
	vertices_.push_back(v4);

	half_edges_.push_back(h1);
	half_edges_.push_back(h2);
	half_edges_.push_back(h3);
	half_edges_.push_back(h4);

	boundingBox.push_back(h1);
	boundingBox.push_back(h2);
	boundingBox.push_back(h3);
	boundingBox.push_back(h4);
}

HalfEdge*  Mesh::getIntersectHalfEdge(double a, double b){
	list<HalfEdge*>::iterator it = half_edges_.begin();

	while (it != half_edges_.end()){
		HalfEdge* tmp = *it++;

		//判断半边与直线是否有交点
		Vertex* intersect = intersectWithBoundingBox(tmp,a,b);
		if (intersect!=NULL){
			return tmp;
		}
	}

	return NULL;
}

//判断直线y=ax-b与半边tmp是否有交点,如果有，则返回交点，否则为NULL
Vertex*  Mesh::intersectWithBoundingBox(HalfEdge* tmp, double a, double b){
	//判断当前half_edge所在的boudingBox的边
	double x1 = tmp->origin()->point().first;
	double y1 = tmp->origin()->point().second;

	double x2 = tmp->next()->origin()->point().first;
	double y2 = tmp->next()->origin()->point().second;

	Vertex* re = new Vertex();


	//4种情况
	if (x1 == x2 && x1 == 0){//左侧边界 线段x=0
		if ((-b >= y1 && -b <= y2) || (-b <= y1 && -b >= y2))
		{
			pair<double, double> p;
			p.first = 0;
			p.second = -b;
			re->set_point(p);
			return re;
		}
			
	}
	else if (x1 == x2 && x1 == lecp_doc->windowWidth){ // x=maxWidth
		double y = a*x1 - b;
		if ((y >= y1 && y <= y2) || (y <= y1 && y >= y2))
		{
			pair<double, double> p;
			p.first = x1;
			p.second = -b;
			re->set_point(p);
			return re;
		}
			
	}
	else if (y1 == y2 && y1 == 0){// y = 0
		if (a != 0){
			double x = b / a;
			if ((x >= x1 && x <= x2) || (x <= x1 && x >= x2))
			{
				pair<double, double> p;
				p.first = x;
				p.second = 0;
				re->set_point(p);
				return re;
			}
		}
	}
	else if (y1 == y2 && y1 == lecp_doc->windowHeight) // y=maxHeight
	{
		if (a != 0){
			double x = (b+y1) / a;
			if ((x >= x1 && x <= x2) || (x <= x1 && x >= x2))
			{
				pair<double, double> p;
				p.first = x;
				p.second = y1;
				re->set_point(p);
				return re;
			}
		}
	}

	return NULL;
}