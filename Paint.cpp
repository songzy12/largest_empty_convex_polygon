#include "Paint.h"
#include <QtGui/QPen>
#include <QtGui/QMouseEvent>
#include <iostream>
#include <vertex.h>
#include <QtGui\qpainter.h>
#include <iomanip>
#include <fstream>
#include <QMessageBox>
#include <string>
#include <vector>
using namespace std;

PaintWidget::PaintWidget() {

}

PaintWidget::PaintWidget(int width, int height, LECP_Doc *lecp_doc){
	lecp_doc_ = lecp_doc;
	resize(width, height);
}

PaintWidget::~PaintWidget() {

}

//绘制points中所有点
void PaintWidget::paintEvent(QPaintEvent *event){
	QPainter painter(this);
	painter.setBrush(Qt::red);
	vector<Vertex*>::iterator it = lecp_doc_->vertices_.begin();
	while (it != lecp_doc_->vertices_.end()){
		paintPoint(*it);
		it++;
	}
}

void PaintWidget::mousePressEvent(QMouseEvent *event){
	QPoint p = event->pos();
	lecp_doc_->addPoint(p.x(), p.y());
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

	outFile << lecp_doc_->vertices_.size() << endl;

	for (long long i = 0; i < lecp_doc_->vertices_.size(); i++){
		Vertex* point = lecp_doc_->vertices_[i];
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

	for (int i = 0; i < size; i++) {
		in.getline(buffer, 10);
		char *cx = strtok(buffer, " ");
		x = atof(cx);

		char *cy = strtok(NULL, " ");

		y = atof(cy);

		lecp_doc_->addPoint(x, y);
	}

	update();
}

void PaintWidget::paintPoint(Vertex* point_){
	QPainter painter(this);
	painter.setBrush(Qt::red);
	painter.drawEllipse(point_->point().first, point_->point().second, 6, 6);
	update();
}