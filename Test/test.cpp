#include <cstdio>
#include <qdebug.h>
#include "vertex.h"
#include "mesh.h"
#include "util.h"

void point_test() {
	Vertex *v = new Vertex();
	v->set_point({ 1, 2 });
	printf("%lf\n", v->point().first);
	return;
}

//only test left or right ; not test point on the line
void toleft_test(){
	Vertex *v1 = new Vertex(); v1->set_point({ 1, 1 });
	Vertex *v2 = new Vertex(); v2->set_point({ 2, 3 });
	Vertex *v3 = new Vertex(); v3->set_point({ 1, 3 });
	Vertex *v4 = new Vertex(); v4->set_point({ 2, 2 });

	bool res1 = toLeft(v1, v2, v3);
	bool res2 = toLeft(v1, v2, v4);

	if (res1 == 1 && res2 == 0)
		qDebug() << "toLeft pass the test";
	else
	{
		qDebug() << "toLeft don't pass the test";
	}
}

void visibility_test()
{
	Mesh* starPoly = new Mesh();
	starPoly->clear();
	//vector<Vertex *> points(6,new Vertex());
	//vector<pair<double, double>> points_data = { { 0, 4 }, { 1, 1 }, { 3, 2 }, { 5, 3 }, { 4, 5 }, { 2, 6 } };
	//for (int i = 0; i < 6; i++)
	//{
	//	points.at(i)->set_point(points_data.at(i));
	//	starPoly->AddVertex(points.at(i));
	//}

	/*Vertex *p = new Vertex(); p->set_point({ 0, 3 }); p->set_index(0);
	Vertex *p1 = new Vertex(); p1->set_point({ 1, 1 }); p1->set_index(1);
	Vertex *p2 = new Vertex(); p2->set_point({ 2, 2 }); p2->set_index(2);
	Vertex *p3 = new Vertex(); p3->set_point({ 7, 0 }); p3->set_index(3);
	Vertex *p4 = new Vertex(); p4->set_point({ 6, 4 }); p4->set_index(4);
	Vertex *p5 = new Vertex(); p5->set_point({ 8, 6 }); p5->set_index(5);
	starPoly->AddVertex(p);
	starPoly->AddVertex(p1);
	starPoly->AddVertex(p2);
	starPoly->AddVertex(p3);
	starPoly->AddVertex(p4);
	starPoly->AddVertex(p5);*/

	Vertex *p = new Vertex(); p->set_point({ 0, 3 }); p->set_index(0);
	Vertex *p1 = new Vertex(); p1->set_point({ 1, 1 }); p1->set_index(1);
	Vertex *p2 = new Vertex(); p2->set_point({ 2, 2 }); p2->set_index(2);
	Vertex *p3 = new Vertex(); p3->set_point({ 7, 0 }); p3->set_index(3);
	Vertex *p4 = new Vertex(); p4->set_point({ 6, 4 }); p4->set_index(4);
	Vertex *p5 = new Vertex(); p5->set_point({ 8, 6 }); p5->set_index(5);
	starPoly->AddVertex(p);
	starPoly->AddVertex(p1);
	starPoly->AddVertex(p2);
	starPoly->AddVertex(p3);
	starPoly->AddVertex(p4);
	starPoly->AddVertex(p5);

	list<Vertex> list_temp;
	list_temp.push_back(*p);
	list_temp.push_back(*p1);
	list_temp.push_back(*p2);
	list_temp.push_back(*p3);
	list_temp.push_back(*p4);
	list_temp.push_back(*p5);
	starPoly->sortedVector.push_back(list_temp);

	visibility(starPoly);
	list<pair<Vertex *, Vertex *>>::iterator itor_edge = starPoly->all_edges()->at(0).begin();
	while (itor_edge != starPoly->all_edges()->at(0).end())
	{
		qDebug() << itor_edge->first->index() << "->" << itor_edge->second->index();
		itor_edge++;
	}

}

void convex_chain_test() 
{
    vector<Vertex *> vs;
    
    Vertex *p0 = new Vertex(); p0->set_point({ 0, 0 }); 
	Vertex *p1 = new Vertex(); p1->set_point({ 1, 0 }); 
	Vertex *p2 = new Vertex(); p2->set_point({ 1, 1 }); 
	Vertex *p3 = new Vertex(); p3->set_point({ 2, 3 }); 
	Vertex *p4 = new Vertex(); p4->set_point({ 0, 4 }); 
    vs.push_back(p0);
    vs.push_back(p1);
    vs.push_back(p2);
    vs.push_back(p3);
    vs.push_back(p4);

	HalfEdge *e12 = new HalfEdge(p1, p2);
    p1->outgoing_edges_.push_back(e12);
    p2->incoming_edges_.push_back(e12);

	HalfEdge *e23 = new HalfEdge(p2, p3);
    p2->outgoing_edges_.push_back(e23);
    p3->incoming_edges_.push_back(e23);
    
	HalfEdge *e24 = new HalfEdge(p2, p4);
    p2->outgoing_edges_.push_back(e24);
    p4->incoming_edges_.push_back(e24);
    
	HalfEdge *e34 = new HalfEdge(p3, p4);
    p3->outgoing_edges_.push_back(e34);
    p4->incoming_edges_.push_back(e34);
    
    ConvexChainLength(vs);
}

int main() {
    point_test();
	toleft_test();
	visibility_test();
	convex_chain_test();
    return 0;
}
