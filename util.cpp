#include "util.h"
#include "qDebug" //only for output check, can be removed later,

bool toLeft(Vertex* i, Vertex* j, Vertex* k)
{
	return toLeft(i->point(), j->point(), k->point());
}

bool toLeft(pair<double, double> i, pair<double, double> j, pair<double, double> k)
{
	bool isleft = (get<0>(i)*get<1>(j) -get<1>(i)*get<0>(j)
		+get<0>(j)*get<1>(k) -get<1>(j)*get<0>(k)
		+get<0>(k)*get<1>(i) -get<1>(k)*get<0>(i)) > 0;
	return isleft;
}

Mesh* visibility(Mesh* starPoly)
{
	list<Vertex*> vertices = starPoly->vertices();
	int N = (starPoly->vertices()).size();
	
	//clear the queue of every point
	list<Vertex*>::iterator itor_vertex = vertices.begin();
	while (itor_vertex != vertices.end())
	{
		Vertex* v1 = *itor_vertex;
		(*itor_vertex)->queue2store()->clear();
		itor_vertex++;
	}

	//do process for n-2 points
	itor_vertex = vertices.begin();
	list<Vertex*>::iterator itor_vertex_temp = itor_vertex++;
	for (int i = 1; i<=N - 2; i++)
	{
		itor_vertex_temp = itor_vertex++;
		Vertex* v1 = *itor_vertex_temp;
		itor_vertex_temp++;
		Vertex* v2 = *itor_vertex_temp;
		VG_process(v1, v2);
	}
	vertices.clear();
	return starPoly;
}

void VG_process(Vertex* i, Vertex* j)
{
	qDebug() <<"vertex i:"<< i->point().first << "," << i->point().second;
	qDebug() << "vertex j:" << j->point().first << "," << j->point().second;
	return;
}