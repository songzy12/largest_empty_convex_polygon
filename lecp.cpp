#include "lecp.h"
#include<QtGui/QPen>
#include<QtGui/QMouseEvent>
#include <qmessagebox.h>
#include <qdebug.h>

#include<DataStruct.h>
#include<Tool.h>
#include<iostream>
#include<vertex.h>
#include <util.h>
using namespace std;

extern bool comparePoint(LECP_Point a, LECP_Point b);

LECP::LECP(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	lecp_doc = new LECP_Doc();

	setFixedSize(lecp_doc->windowWidth, lecp_doc->windowHeight);
	
	int width = this->width();
	int height = this->height();

	mesh = new Mesh();
	paintWidget = new PaintWidget(width, height);
	this->setCentralWidget(paintWidget);

	QObject::connect(ui.polar_angle_sort, SIGNAL(triggered()), this, SLOT(polarAngleSortSlot()));
	QObject::connect(ui.create_VG, SIGNAL(triggered()), this, SLOT(showVGSlot()));
	lecp_doc = new LECP_Doc();

	

}

LECP::~LECP()
{

}

/*
void LECP::paintEvent(QPaintEvent *event){
	QPainter painter(this);

	QPen pen(qRgb(255, 0, 0));

	painter.setPen(pen);

	painter.setBrush(QBrush(Qt::red));

	painter.drawEllipse(currentPoint.x(), currentPoint.y(), 6, 6);

}


void LECP::mouseReleaseEvent(QMouseEvent *event){
	if (event->button() == Qt::RightButton){//鼠标左键按下
	currentPoint = event->pos();
	update();
	}
}


void LECP::mousePressEvent(QMouseEvent *event){
	//flag = false;
	if (event->button() == Qt::LeftButton){//鼠标左键按下
		currentPoint = event->pos();
		LECP_Point point(currentPoint.x(), currentPoint.y());
		bool add = lecp_doc->addPoint(point);
		if (add){
			paintWidget->setpaint(true);
			paintWidget->paintPoint(currentPoint.x(), currentPoint.y());
			mesh->AddLine((double)currentPoint.x(), (double)currentPoint.y());
		}
	}
}
*/

void LECP::resizeEvent(QResizeEvent *event){
}

Vertex* pole;
bool compareVertex(Vertex* p, Vertex* q){
	double px = p->point().first;
	double py = p->point().second;
	double sx = pole->point().first;
	double sy = pole->point().second;
	double qx = q->point().first;
	double qy = q->point().second;


	double area = px*qy - py*qx + qx*sy - qy*sx + sx*py - sy*px;
	if (area < 0)
		return true;
	return false;
}


void  LECP::polarAngleSortSlot(){
	lecp_doc->points = paintWidget->points;
	//首先将输入的所有点按照从左到右的顺序排列
	vector<LECP_Point> points = lecp_doc->points;
	sort(points.begin(), points.end(), comparePoint);
	list<Vertex*> polarVextex = changeLECO_PointToVertex(points);

	list<Vertex*>::iterator it = polarVextex.begin();
	while (it != polarVextex.end()){
		pole = *it;

		list<Vertex*> subV(++it, polarVextex.end());
		subV.sort(compareVertex);
		
		subV.push_front(pole);

		mesh->sortedVector.push_back(subV);
	}
}

LECP_Point s;
bool comparePolar(const LECP_Point p, const LECP_Point q){
	double area = p.x*q.y - p.y*q.x + q.x*s.y - q.y*s.x + s.x*p.y - s.y*p.x;
	if (area < 0)
		return true;
	return false;
}

//极角从小到大排列
list<LECP_Point>  LECP::getPolarSort(LECP_Point tmpPoint, vector<LECP_Point> subV){
	list<LECP_Point> reList;

	s = tmpPoint;
	//to left test进行极角排序
	sort(subV.begin(), subV.end(), comparePolar);

	std::copy(subV.begin(), subV.end(), std::back_inserter(reList));

	return reList;
}

extern void visibility(Mesh* starPoly);
void LECP::showVGSlot()
{
	QMessageBox::warning(this, tr("to show"), tr("show animation of VG!"));

	visibility(mesh);
	for (int i = 0; i < mesh->sortedVector.size(); i++){
		qDebug() << " for point" << i << ":";
		list<pair<Vertex*, Vertex*>>::iterator itor_edge = mesh->all_edges()->at(i).begin();
		while (itor_edge != mesh->all_edges()->at(i).end())
		{
			qDebug() << itor_edge->first->index() << "->" << itor_edge->second->index();
			itor_edge++;
		}
	}
}
