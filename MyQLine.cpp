#include "MyQLine.h"
MyQline::MyQline(){
	color_ = Qt::black;
	use_dot_style_ = false;
	have_arrow_ = false;
	show_l_ = false;
	L_ = 1;
}
MyQline::MyQline(QLine line){
	this->setLine(line.x1(),line.y1(),line.x2(),line.y2());

	color_ = Qt::black;
	use_dot_style_ = false;
	have_arrow_ = false;
	show_l_ = false;
	L_ = 1;
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
int MyQline::L()
{
	return L_;
}
void MyQline::setL(int l)
{
	L_ = l;
}
bool MyQline::showL()
{
	return show_l_;
}
void MyQline::setShowL(bool showL)
{
	show_l_ = showL;
}