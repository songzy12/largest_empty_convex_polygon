/*
All painting operations  are executed by this file.
*/

#ifndef PAINT_H
#define PAINT_H

#include "lecp_doc.h"
#include <QtWidgets/QMainWindow>
#include <QtWidgets\qwidget.h>
#include <QtGui/qpainter.h>
#include <list>

class PaintWidget:public QWidget
{
public:
	PaintWidget();
	~PaintWidget();
	PaintWidget(int width, int height, LECP_Doc *lecp_doc);
protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
public:
	bool savePoints(char *filename);
	void loadPoints(char *fileName);
	void paintPoint(Vertex* point);
	void paintEdge(HalfEdge* edge);

	LECP_Doc* lecp_doc_;
};

#endif