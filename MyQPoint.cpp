#include"MyQPoint.h"

MyQPoint::MyQPoint(){
	color_ = Qt::red;
	index_ = 0;
}

MyQPoint::MyQPoint(QPoint point){
	this->setX(point.x());
	this->setY(point.y());
	this->color_ = Qt::red;
	this->index_ = 0;
}


MyQPoint::MyQPoint(QColor color, long long index){
	color_ = color;
	index_ = index;
}

void MyQPoint::setColor(QColor color){
	color_ = color;
}

void MyQPoint::setIndex(long long index){
	index_ = index;
}

long long MyQPoint::getIndex(){
	return index_;
}

QColor MyQPoint::getColor(){
	return color_;
}
vector<int> MyQPoint::getQ()
{
	return Q_;
}
void MyQPoint::setQ(vector<int> Q)
{
	Q_.clear();
	Q_ = Q;
}