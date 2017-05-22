#include "MyQLine.h"

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