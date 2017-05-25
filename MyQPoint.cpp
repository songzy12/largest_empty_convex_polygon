#include"MyQPoint.h"

MyQPoint::MyQPoint(){
	color_ = Qt::red;
	index_ = 0;
	showQ_ = true;
}

MyQPoint::MyQPoint(QPoint point){
	this->setX(point.x());
	this->setY(point.y());
	this->color_ = Qt::red;
	this->index_ = 0;
	showQ_ = true;
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
void MyQPoint::setQ(deque<Vertex*> Q)
{
	Q_.clear();

	Vertex * temp_v;
	deque<Vertex*>::iterator it_v = Q.begin();
	while (it_v != Q.end())
	{
		temp_v = *it_v;
		Q_.push_back(temp_v->index());
		it_v++;
	}
}

bool MyQPoint::showQ()
{
	return showQ_;
}
void MyQPoint::setShowQ(bool showQ)
{
	showQ_ = showQ;
}