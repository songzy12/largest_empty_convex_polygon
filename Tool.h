/*
Added by zhangyaxian
This file stores all of the public params and public configures.
*/

#ifndef TOOL_H
#define TOOL_H

#include<DataStruct.h>
#include<vector>
#include<set>
#include<list>
#include<vertex.h>
#include<DataStruct.h>
using namespace std;

#define WIN_WIDTH  1200
#define WIN_HEIGHT 800
#define MAX_X 20000000000
#define MAX_Y 10000000000

class LECP_Doc{
public :
	vector<LECP_Point> points;//all of the points user input

	long long  windowWidth;
	long long  windowHeight;

	int QWindowWidth;
	int QWindowHeight;

	LECP_Point s;//求极角的标杆点
public:
	LECP_Doc(){
		//windowWidth = WIN_WIDTH;
		//windowHeight = WIN_HEIGHT;

		windowWidth = MAX_X;
		windowHeight = MAX_Y;

		QWindowWidth = WIN_WIDTH;
		QWindowHeight = WIN_HEIGHT;
	}

	void removeRepeatPoints();//remove one of the same point to ensure every point in points is unique.

	bool comparePolar(const LECP_Point p, const LECP_Point q);
};

extern bool comparePoint(LECP_Point a, LECP_Point b);
extern list<Vertex*> changeLECO_PointToVertex(list<LECP_Point> points);
extern list<Vertex*> changeLECO_PointToVertex(vector<LECP_Point> points);

//return whether the point is added to the array successfully.If point in points,return false;otherwise return true.
extern bool addPoint(LECP_Point point,vector<LECP_Point> points);

//判断half_edge与直线y=ax-b是否有交点，if intersect,return the Vertex,else return null
extern Vertex* intersaction(HalfEdge *half_edge, double a, double b);

#endif