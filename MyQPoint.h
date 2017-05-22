#ifndef MYQPOINT_H
#define MYQPOINT_H

#include<QPoint>
#include<QColor>

class MyQPoint:public QPoint{
public:
	MyQPoint();
	MyQPoint(QPoint point);
	MyQPoint(QColor color, long long index);
	~MyQPoint(){};
	void setIndex(long long index);
	void setColor(QColor color);
	long long getIndex();
	QColor getColor();
public:
	long long index_;
	QColor color_;

};

#endif // !MYQPOINT_H
