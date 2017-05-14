#ifndef PAINT_H
#define PAINT_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets\qwidget.h>
#include <DataStruct.h>
#include <list>
#include <QtGui/qpainter.h>
using namespace std;

class PaintWidget:public QWidget
{
private:
	
	bool paintFlag;
	list<LECP_Point*> points;

	//Mesh *mesh;
public:
	PaintWidget(){ paintFlag = false; }
	PaintWidget(int width, int height);
protected:
	void paintEvent(QPaintEvent *event);
public:
	void paintPoint(double x, double y);
	void paintPoint(LECP_Point point_);
	void setpaint(bool flag)
	{ 
		paintFlag = flag;
	}
};

#endif