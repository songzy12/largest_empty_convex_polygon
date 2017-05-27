
#ifndef  LECP_POINT_H
#define  LECP_POINT_H
/*
This file is only used by zyx.
*/
#include<queue>
#include<QColor>
using namespace std;

/*
point which is inserted by the user definiation
*/

class LECP_Point{

public:
	double x, y;
	long long index;
	long long sortedIndex;//from left to right according to x coordinate
	QColor color; //default color is red
public:
	LECP_Point();
	LECP_Point(double _x, double _y);

	void setX(double x){ this->x = x; }
	void setY(double y){ this->y = y; }

	bool operator == (LECP_Point a){
		if (a.x == x && a.y == y)
			return true;
		else return false;
	}

};

#endif