#include <cstdio>
#include <qdebug.h>
#include "vertex.h"
#include "mesh.h"
#include "util.h"

void point_test() {
	Vertex *v = new Vertex({ 1, 2 });
	printf("%lf\n", v->point().first);
	return;
}

//only test left or right ; not test point on the line
void toleft_test(){
	Vertex *v1 = new Vertex({ 402, 548 }); 
	Vertex *v2 = new Vertex({ 822, 511 }); 
	Vertex *v3 = new Vertex({ 638, 246 }); 
	Vertex *v4 = new Vertex({ 2, 2 }); 

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
	vector<Vertex *> vertices;
	vertices.push_back(new Vertex({ 0, 3 }, 0));
	vertices.push_back(new Vertex({ 1, 1 }, 1));
	vertices.push_back(new Vertex({ 2, 2 }, 2));
	vertices.push_back(new Vertex({ 7, 0 }, 3));
	vertices.push_back(new Vertex({ 6, 4 }, 4));
	vertices.push_back(new Vertex({ 8, 6 }, 5));
	Polygon * polygon = new Polygon(vertices);

	vector<Vertex*> visibility_graph = polygon->getVisibilityGraph(); 
	
	vector<Vertex*>::iterator it = visibility_graph.begin();
	for (; it != visibility_graph.end(); ++it) {
		qDebug() << "Vertex with index " << (*it)->index() << ":";
		vector<HalfEdge*> incoming_edges = (*it)->incoming_edges_;
		vector<HalfEdge*>::iterator it_e = incoming_edges.begin();
		for (; it_e != incoming_edges.end(); ++it_e) {
			qDebug() << (*it_e)->origin()->index() << "->" << (*it_e)->target()->index();
		}
	}
}

void convex_chain_test() 
{
    vector<Vertex *> vs;
    
	Vertex *p0 = new Vertex({ 0, 0 }, 0);
	Vertex *p1 = new Vertex({ 1, 0 }, 1);
	Vertex *p2 = new Vertex({ 1, 1 }, 2);
	Vertex *p3 = new Vertex({ 2, 3 }, 3);
	Vertex *p4 = new Vertex({ 0, 4 }, 4);
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
    
	Polygon *polygon = new Polygon(vs);
	vector<Vertex*> convex_chain = polygon->getConvexChain();

	for (size_t i = 0; i < convex_chain.size(); ++i) {
		qDebug() << convex_chain[i]->index();
	}
}

int main() {
	convex_chain_test();
}