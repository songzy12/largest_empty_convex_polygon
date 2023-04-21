/*
All painting operations  are executed by this file.
*/

#ifndef PAINT_H
#define PAINT_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets\qwidget.h>
#include <QtGui/qpainter.h>
#include <QColor>
#include <QBasicTimer>
#include <qwidget.h>
#include <qpaintengine.h>
#include <vector>

#include "MyQLine.h"
#include "MyQPoint.h"
#include "point.h"
#include "mesh.h"
#include "vertex.h"
#include "half_edge.h"

class PaintWidget:public QWidget
{
private:
	double scaleX ;
	double scaleY ;
	double penWidth;


public:
	PaintWidget();
	~PaintWidget();
	PaintWidget(int width, int height);//, Mesh *mesh_
protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void timerEvent(QTimerEvent *event);
public:
	void clear();

	void setPoints(vector<LECP_Point*> points_);
	bool savePoints(char *filename);
	void loadPoints(char *fileName);

	void paintPoint(MyQPoint point);
	void paintPoint(MyQPoint *point);
	void paintEdge(HalfEdge* edge);

	bool addPoint(LECP_Point *point);//double x, double y

	LECP_Point* changeMyQPointToLECP_Point(MyQPoint *qPoint);
	MyQPoint* changeLECP_PointToMyQPoint(LECP_Point *point);
	
	void changeLECP_PointsToQPoints();//坐标变换

	void paintAllPoints();//绘制当前所有点,LECP_Point

	void animationPoint(MyQPoint  *qPoint, vector<pair<LECP_Point*, LECP_Point*>> lecp_points, double showSpeed);
	long long getOriginPointIndex(MyQPoint* qPoint);

	//------------------for animation------------------------------------------------------
	void paintAllLine();
	void paintLine(MyQline *line);
	void paintIntersectPoints();
	MyQline* addLine(MyQPoint *point);
	QLine getPaintLine(MyQPoint *qPoint);
	void displayIntersectionPoint(vector<pair<LECP_Point*, LECP_Point*>> lecp_points, double showSpeed);
	void getSuitCoordinate(double a,double  b,double &x1,double &y1,double &x2,double &y2);
	/////////////show animation///////////////////////////
	void paintPoints(MyQPoint *point);
	void paintAllEdges();
	void paintEdges(MyQline *line);

public:
	QPoint currentPoint;//current kernel

	bool drawKernel;//whether to draw kernel

	vector<LECP_Point*> points;// store all of the points user input. Calculated  coordinate system	
	//vector<QPoint> qPoints; //which are under Qt coordinate system
	vector<MyQPoint*> myQPoints;//绘制都用它，与points的区别在于y（取负）	

	vector<MyQline*> lines;
	vector<LECP_Point*> intersectPoints;//can not use MyQPoint, because there is  Deviation

	/////////////show animation///////////////////////////
	/*all MYQPoints needed to be draw*/
	vector<MyQPoint> allQPoints2Draw;
	/*all MYQLines needed to be draw*/
	vector<MyQline> allQLines2Draw;
};


#endif