/*
All painting operations  are executed by this file.
*/

#ifndef PAINT_H
#define PAINT_H

#include "vertex.h"
#include "half_edge.h"
#include <QtWidgets/QMainWindow>
#include <QtWidgets\qwidget.h>
#include <QtGui/qpainter.h>

class PaintWidget:public QWidget
{
public:
	PaintWidget();
	~PaintWidget();
	PaintWidget(int width, int height);
protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
public:
	bool savePoints(char *filename);
	void loadPoints(char *fileName);
	void paintPoint(Vertex* point);
	void paintEdge(HalfEdge* edge);

	bool addPoint(double x, double y);
	void removeRepeatPoints(); //remove one of the same point to ensure every point in points is unique.

	vector<Vertex*> vertices_; //all of the points user input
};

#endif