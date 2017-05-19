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

PaintWidget::PaintWidget(int width, int height) {
	resize(width, height);
}

PaintWidget::~PaintWidget() {

}

//绘制points中所有点
void PaintWidget::paintEvent(QPaintEvent *event){
	QPainter painter(this);
	painter.setBrush(Qt::red);
	vector<Vertex*>::iterator it = vertices_.begin();
	while (it != vertices_.end()){
		paintPoint(*it);
		it++;
	}
}

void PaintWidget::mousePressEvent(QMouseEvent *event){
	QPoint p = event->pos();
	addPoint(p.x(), p.y());
	update();
}

// origin in lecp_doc

bool PaintWidget::addPoint(double x, double y) {
	Vertex *point = new Vertex(x, y, vertices_.size());

	vector<Vertex*>::iterator it = std::find(vertices_.begin(), vertices_.end(), point);

	if (it == vertices_.end())	{
		qDebug() << "vertex" << vertices_.size() << ":" << point->point().first << "," << point->point().second;
		vertices_.push_back(point);
		//paintPoint(point);
		return true;
	}
	else {
		delete point;
	}
	return false;
}

void PaintWidget::removeRepeatPoints() {
	sort(vertices_.begin(), vertices_.end(), comparePoint);
	vertices_.erase(unique(vertices_.begin(), vertices_.end()), vertices_.end());
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

	outFile << vertices_.size() << endl;

	for (long long i = 0; i < vertices_.size(); i++){
		Vertex* point = vertices_[i];
		outFile << point->point().first << " " << point->point().second << endl;
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

		addPoint(x, y);
	}

	update();
}

void PaintWidget::paintPoint(Vertex* point_){
	QPainter painter(this);
	painter.setBrush(Qt::red);
	painter.drawEllipse(point_->point().first, point_->point().second, 6, 6);
	painter.drawText(point_->point().first, point_->point().second, QString::number(point_->index()));
	update();
}

void PaintWidget::paintEdge(HalfEdge* edge_) {
	QPainter painter(this);
	painter.setBrush(Qt::blue);
	painter.drawLine(edge_->origin()->point().first, edge_->origin()->point().second, 
					 edge_->target()->point().first, edge_->target()->point().second);
	update();
}