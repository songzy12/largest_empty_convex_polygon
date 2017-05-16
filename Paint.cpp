#include "Paint.h"
#include<QtGui/QPen>
#include<QtGui/QMouseEvent>
#include<DataStruct.h>
#include<Tool.h>
#include<iostream>
#include<vertex.h>
#include<QtGui\qpainter.h>


PaintWidget::PaintWidget(int width, int height){
	resize(width, height);
	paintFlag = false;
}

//绘制points中所有点
void PaintWidget::paintEvent(QPaintEvent *event){

	if (paintFlag){
		QPainter painter(this);
		painter.setBrush(Qt::red);
		vector<LECP_Point>::iterator tmpiterator = points.begin();
		while (tmpiterator != points.end()){//一样的
			LECP_Point tmp = *tmpiterator++;
			painter.drawEllipse(tmp.x, tmp.y, 6, 6);
		}

		paintFlag = false;
	}

}


void PaintWidget::paintPoint(double x, double y){
	/*
	LECP_Point *point = new LECP_Point();
	point->x = x;
	point->y = y;

	points.push_back(point);

	update();
*/
	//mesh->AddLine(x, y);

}

extern bool addPoint(LECP_Point point, vector<LECP_Point> points);
void PaintWidget::mousePressEvent(QMouseEvent *event){
	QPoint p = event->pos();
	LECP_Point point;
	point.x = p.x();
	point.y = p.y();

	if (addPoint(point, points)){
		paintFlag = true;
		points.push_back(point);
		update();
	}
}

void PaintWidget::paintPoint(LECP_Point point_){
	//point->x = point_.x;
	//point->y = point_.y;
	update();
}