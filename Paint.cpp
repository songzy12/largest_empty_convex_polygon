#include "Paint.h"
#include<QtGui/QPen>
#include<QtGui/QMouseEvent>
#include<DataStruct.h>
#include<Tool.h>
#include<iostream>
#include<vertex.h>
#include<QtGui\qpainter.h>
#include <iomanip>
#include <fstream>
#include<QMessageBox>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

PaintWidget::PaintWidget(int width, int height){
	resize(width, height);
	paintFlag = false;

	mesh = new Mesh();
}

//绘制points中所有点
void PaintWidget::paintEvent(QPaintEvent *event){

	//if (paintFlag){
		QPainter painter(this);
		painter.setBrush(Qt::red);
		vector<LECP_Point>::iterator tmpiterator = points.begin();
		while (tmpiterator != points.end()){//一样的
			LECP_Point tmp = *tmpiterator++;
			painter.drawEllipse(tmp.x, tmp.y, 6, 6);
		}

		paintFlag = false;
	//}

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

		//change DCEL
		mesh->AddLine(point.x, point.y);

		update();
	}
}

void PaintWidget::paintPoint(LECP_Point point_){
	//point->x = point_.x;
	//point->y = point_.y;
	update();
}

bool PaintWidget::savePoints(char *filename){
	ofstream outFile(filename);
	if (!outFile){
		QMessageBox box;
		QString msg = "Fail to save file" + QString::fromUtf8(filename);
		box.about(this, "Failed!",msg );
		box.show();
		return false;
	}

	outFile << points.size() << endl;

	for (long long i = 0; i < points.size(); i++){
		LECP_Point point = points[i];
		outFile << point.x << " " << point.y << endl;
	}

	outFile.close();
	update();
	return true;
}

void PaintWidget::openFile(char *fileName){
	ifstream in(fileName);

	if (!in){
		QMessageBox box;
		QString msg = "Fail to open file" + QString::fromUtf8(fileName);
		box.about(this, "Failed!", msg);
		box.show();
		return ;
	}

	char buffer[256];
	double x, y;

	in.getline(buffer, 10);
	int size = atoi(buffer);

	for (int i = 0; i < size; i++){
		in.getline(buffer, 10);
		char *cx = strtok(buffer, " ");
		x = atof(cx);

		char *cy = strtok(NULL, " ");

		y = atof(cy);

		LECP_Point point;
		point.setX(x);
		point.setY(y);
		points.push_back(point);
	}

	paintFlag = true;
	update();

}