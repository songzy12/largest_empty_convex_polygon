/*
Added by zhangyaxian
This file stores all of the public params and public configures.
*/

#ifndef TOOL_H
#define TOOL_H

#include<DataStruct.h>
#include<vector>
#include<set>
using namespace std;

#define WIN_WIDTH  1200
#define WIN_HEIGHT 800

class LECP_Doc{
public :
	vector<LECP_Point> points;//all of the points user input

	int windowWidth;
	int windowHeight;
public:
	LECP_Doc(){
		windowWidth = WIN_WIDTH;
		windowHeight = WIN_HEIGHT;
	}

	bool addPoint(LECP_Point point);//return whether the point is added to the array successfully.
	void removeRepeatPoints();//remove one of the same point to ensure every point in points is unique.
};

extern bool comparePoint(LECP_Point a, LECP_Point b);

#endif