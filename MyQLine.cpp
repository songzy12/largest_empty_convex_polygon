#include "MyQLine.h"
MyQline::MyQline(){}
MyQline::MyQline(QLine line){
	this->setLine(line.x1(),line.y1(),line.x2(),line.y2());

	color_ = Qt::blue;
}

QColor MyQline::getColor(){
	return color_;
}
void MyQline::setColor(QColor color){
	color_ = color;
}

void  MyQline::setDotStyle(bool use)
{
	use_dot_style_ = use;
}
bool  MyQline::getDotStyle()
{
	return use_dot_style_;
}