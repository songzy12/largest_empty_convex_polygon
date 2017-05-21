/*
Added by zhangyaxian
This file is used to define the data struct used in the project.
*/

#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include<queue>

using namespace std;

/*
point definiation
*/

class LECP_Point{

public :
	double x,y;
	long long index;
	//queue<LECP_Point*> angleSortedQueue;//以该点为基准，其他所有点的极角排序优先队列
public:
	LECP_Point(){}
	LECP_Point(double _x, double _y);

	//double x();
	//double y();

	void setX(double x){ this->x = x; }
	void setY(double y){ this->y = y; }
	//void setXY(double x, double y){ this->x= x; this->y= y; }

	bool operator == (LECP_Point a){
		if (a.x == x && a.y == y)
			return true;
		else return false;
	}

};

#endif