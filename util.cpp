#include "util.h"
#include "LECP_Point.h"
#include"Paint.h"

//按照横坐标从左向右排列
bool comparePoint(LECP_Point a, LECP_Point b){
	if (a.x < b.x)
		return true;
	else if (a.x >b.x)
		return false;
	else{
		return a.y < b.y;
	}
}

bool toLeft(Vertex* i, Vertex* j, Vertex* k)
{
	return toLeft(i->point(), j->point(), k->point());
}

bool toLeft(pair<double, double> i, pair<double, double> j, pair<double, double> k)
{
	bool isleft = (get<0>(i)*get<1>(j) -get<1>(i)*get<0>(j)
		+get<0>(j)*get<1>(k) -get<1>(j)*get<0>(k)
		+get<0>(k)*get<1>(i) -get<1>(k)*get<0>(i)) > 0;
	return !isleft; // TODO: < >
}

bool isConvexTurn(HalfEdge *i, HalfEdge *o)
{
	return toLeft(i->origin(), i->target(), o->target());
}

list<Vertex*> changeLECO_PointToVertex(vector<LECP_Point> points){
	list<Vertex*> re;

	for (long long i = 0; i < points.size(); i++){
		LECP_Point point = points[i];
		Vertex *v = new Vertex();
		pair<double, double> p;
		p.first = point.x;
		p.second = point.y;
		v->set_point(p);
		v->set_index(i);
		re.push_back(v);
	}

	return re;
}

vector<LECP_Point> sortInputPointsFromLeftToRight(PaintWidget *paint){
	vector<LECP_Point> points= paint->points;
	
	sort(points.begin(), points.end(), comparePoint);

	return points;
}
