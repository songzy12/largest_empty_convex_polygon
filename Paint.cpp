#include "Paint.h"
#include "util.h"
#include <QtGui/QPen>
#include <QtGui/QMouseEvent>
#include <QtGui\qpainter.h>
#include <QMessageBox>
#include "qdebug.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <vertex.h>
using namespace std;

PaintWidget::PaintWidget() {

}
//, Mesh *mesh_
PaintWidget::PaintWidget(int width, int height) {
	resize(width, height);
	//mesh = mesh_;
}

PaintWidget::~PaintWidget() {

}

//绘制points中所有点
void PaintWidget::paintEvent(QPaintEvent *event){
	QPainter painter(this);
	painter.setBrush(Qt::red);
	
	for (long long i = 0; i < qPoints.size();i++){
		QPoint tmpP = qPoints[i];
		paintPoint(tmpP,i);
	}
}

void PaintWidget::mousePressEvent(QMouseEvent *event){
	QPoint p = event->pos();

	double half_x = WIN_WIDTH/ 2.0;
	double half_y = WIN_HEIGHT/ 2.0;

	LECP_Point point;
	point.x = p.x() - half_x;
	point.y = -p.y() + half_y;

	if (addPoint(point)){
		
		point.index = points.size();
		points.push_back(point);

		qPoints.push_back(p);

		update();
	}
}

bool PaintWidget::addPoint(LECP_Point point) {
	vector<LECP_Point>::iterator it;
	it = std::find(points.begin(), points.end(), point);

	if (it == points.end())
	{
		std::cout << points.size() << " point：" << point.x << "," << point.y << endl;

		return true;
	}

	return false;
}

void PaintWidget::removeRepeatPoints() {
	//sort(vertices_.begin(), vertices_.end(), comparePoint);
	//t6vertices_.erase(unique(vertices_.begin(), vertices_.end()), vertices_.end());
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

void PaintWidget::loadPoints(char *fileName){
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
	// TODO: whether to clear vertices_ first?
	for (int i = 0; i < size; i++) {
		in.getline(buffer, 10);
		char *cx = strtok(buffer, " ");
		x = atof(cx);

		char *cy = strtok(NULL, " ");

		y = atof(cy);

		LECP_Point point;
		point.setX(x);
		point.setY(y);
		point.index = points.size();
		points.push_back(point);
	}

	changeLECP_PointToQPoint();//坐标变换

	update();
}

void PaintWidget::paintPoint(QPoint point,long long index){
	QPainter painter(this);
	painter.setBrush(Qt::red);
	painter.drawEllipse(point.x(), point.y(), 6, 6);
	painter.drawText(point.x(), point.y(), QString::number(index));
	update();
}

void PaintWidget::paintEdge(HalfEdge* edge_) {
	QPainter painter(this);
	painter.setBrush(Qt::blue);
	painter.drawLine(edge_->origin()->point().first, edge_->origin()->point().second, 
					 edge_->target()->point().first, edge_->target()->point().second);
	update();
}

void PaintWidget::changeLECP_PointToQPoint(){
	double half_x = WIN_WIDTH / 2.0;
	double half_y = WIN_HEIGHT/ 2.0;

	for (long long i = 0; i < points.size(); i++)
	{
		LECP_Point p = points[i];
		QPoint qp;
		qp.setX(half_x + p.x);
		qp.setY(half_y - p.y);
		qPoints.push_back(qp);
	}

	update();
}