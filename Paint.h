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
#include <LECP_Point.h>
#include <mesh.h>

class PaintWidget:public QWidget
{
private:
	vector<QPoint> qPoints; //which are under Qt coordinate system
public:
	PaintWidget();
	~PaintWidget();
	PaintWidget(int width, int height);//, Mesh *mesh_
protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
public:
	bool savePoints(char *filename);
	void loadPoints(char *fileName);
	void paintPoint(QPoint point, long long index);
	void paintEdge(HalfEdge* edge);

	bool addPoint(LECP_Point point);//double x, double y
	void removeRepeatPoints(); //remove one of the same point to ensure every point in points is unique.

	void changeLECP_PointToQPoint();//×ø±ê±ä»»
public:
	//Mesh *mesh;
	vector<LECP_Point> points;// store all of the points user input.Calculated  coordinate system
};

#endif