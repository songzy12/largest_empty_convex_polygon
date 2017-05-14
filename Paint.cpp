#include "Paint.h"
#include<QtGui/QPen>
#include<QtGui/QMouseEvent>
#include<DataStruct.h>
#include<Tool.h>
#include<iostream>
#include<vertex.h>
#include<QtGui\qpainter.h>

void PaintWidget::paintEvent(QPaintEvent *event){
	QPainter painter(this);
	painter.setBrush(Qt::red);

	if (paintFlag){
	
		//painter.setPen(QPen(Qt::red, 5));
		

		list<LECP_Point*>::iterator tmpiterator = points.begin();
		while (tmpiterator != points.end()){//Ò»ÑùµÄ
			LECP_Point *tmp = *tmpiterator++;
			painter.drawEllipse(tmp->x, tmp->y, 6, 6);
		}

		paintFlag = false;
	}
	
}

PaintWidget::PaintWidget(int width, int height){
	resize(width, height);
	paintFlag = false;
	//point = new LECP_Point();

	//mesh = new Mesh();
}

void PaintWidget::paintPoint(double x, double y){
	LECP_Point *point = new LECP_Point();
	point->x = x;
	point->y = y;

	points.push_back(point);

	update();

	//mesh->AddLine(x, y);

}

void PaintWidget::paintPoint(LECP_Point point_){
	//point->x = point_.x;
	//point->y = point_.y;
	update();
}