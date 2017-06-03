#include "point.h"

LECP_Point::LECP_Point(){
	color = Qt::red;
}

LECP_Point::LECP_Point(double _x, double _y, int _index){
	x = _x;
	y = _y;
	index = _index;
	color = Qt::red;
}