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

class LECP_Doc{
public :
	vector<LECP_Point> points;//all of the points user input
public:
	LECP_Doc(){}

	bool addPoint(LECP_Point point);//return whether the point is added to the array successfully.
	void removeRepeatPoints();//remove one of the same point to ensure every point in points is unique.
};

#endif