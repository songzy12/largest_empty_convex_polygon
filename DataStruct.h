/*
Added by zhangyaxian
This file is used to define the data struct used in the project.
*/

#ifndef DATASTRUCT_H
#define DATASTRUCT_H

/*
point definiation
*/

class LECP_Point{

public :
	double x;
	double y;
public:
	LECP_Point(){}
	LECP_Point(double _x, double _y);

	bool operator == (const LECP_Point a){
		if (a.x == this->x && a.y == this->y)
			return true;
		else return false;
	}
};

#endif