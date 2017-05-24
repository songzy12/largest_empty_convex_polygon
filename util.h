#include "vertex.h"
#include "half_edge.h"
#include"LECP_Point.h"
#include<list>
#include "lecp_doc.h"

#define WIN_WIDTH  1200
#define WIN_HEIGHT 800
#define MAX_X 20000000000
#define MAX_Y 10000000000

//按照横坐标从左向右排列
bool comparePoint(LECP_Point a, LECP_Point b);

/*toLeft test
direct line i->j, test point k*/
bool toLeft(Vertex* i, Vertex* j, Vertex* k);
bool toLeft(pair<double, double> i, pair<double, double> j, pair<double, double> k);
bool isConvexTurn(HalfEdge *i, HalfEdge *o);
list<Vertex*> changeLECO_PointToVertex(vector<LECP_Point> points);

vector<LECP_Point> sortInputPointsFromLeftToRight(LECP_Doc *doc);

vector<LECP_Point>  generateRandomPoints(long long points_number);