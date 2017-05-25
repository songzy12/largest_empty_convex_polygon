#include "MyQLine.h"
MyQline::MyQline(){
	color_ = Qt::black;
	use_dot_style_ = false;
	have_arrow_ = false;
}
MyQline::MyQline(QLine line){
	this->setLine(line.x1(),line.y1(),line.x2(),line.y2());

	color_ = Qt::black;
	use_dot_style_ = false;
	have_arrow_ = false;
}

QColor MyQline::getColor(){
	return color_;
}
void MyQline::setColor(QColor color){
	color_ = color;
}

void  MyQline::setDotStyle(bool use){
	use_dot_style_ = use;
}
bool  MyQline::getDotStyle(){
	return use_dot_style_;
}

void MyQline::setArrowStyle(bool use){
	have_arrow_ = use;
}
bool MyQline::getArrowStyle(){
	return have_arrow_;
}
float MyQline::length(){
	float length = sqrt(this->dx()*this->dx() + this->dy()*this->dy());
	return length;
}