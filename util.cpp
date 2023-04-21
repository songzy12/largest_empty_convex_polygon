#include "util.h"
#include "paint.h"
#include "time.h"
#include <iostream>

using namespace std;

//按照横坐标从左向右排列
bool comparePoint(LECP_Point* a, LECP_Point* b){
	if (a->x != b->x)
		return a->x < b->x;
	return a->y < b->y;
}

bool toLeft(Vertex* i, Vertex* j, Vertex* k)
{
	return toLeft(i->point(), j->point(), k->point());
}

bool toLeft(pair<double, double> i, pair<double, double> j, pair<double, double> k)
{
	bool isleft = (get<0>(i)*get<1>(j) -get<1>(i)*get<0>(j)
		+get<0>(j)*get<1>(k) -get<1>(j)*get<0>(k)
		+get<0>(k)*get<1>(i) -get<1>(k)*get<0>(i)) >= 0;
	return isleft; 
}

bool isConvexTurn(HalfEdge *i, HalfEdge *o)
{
	return toLeft(i->origin(), i->target(), o->target());
}

list<Vertex*> changeLECO_PointToVertex(vector<LECP_Point*> points){
	list<Vertex*> re;

	for (long long i = 0; i < points.size(); i++){
		LECP_Point *point = points[i];
		Vertex *v = new Vertex(point->x, point->y, i);
		re.push_back(v);
	}

	return re;
}

vector<LECP_Point*> sortPointsOnX(vector<LECP_Point*> points){
	sort(points.begin(), points.end(), comparePoint);
	return points;
}


vector<LECP_Point*>  generateRandomPoints(long long points_number){
	vector<LECP_Point*> points;

	int offset = 40;

	// 向内回收5个像素点的位置，避免点落在边界或者超出边界的case
	int mx = -WIN_WIDTH / 2 + offset;
	int nx = WIN_WIDTH / 2 - offset;
	int my = -WIN_HEIGHT / 2 + offset;
	int ny = WIN_HEIGHT / 2 - offset;

	srand(time(NULL));

	for (long long i = 0; i < points_number; i++) {
		LECP_Point *point = new LECP_Point(rand() % (nx - mx + 1) + mx, rand() % (ny - my + 1) + my, i);
		if (std::find(points.begin(), points.end(), point) == points.end()){
			cout << "point " << points.size() << ":" << point->x << " " << point->y << endl;
			points.push_back(point);
		}
		else {
			delete point;
			i--;
		}
	}
	return points;
}
