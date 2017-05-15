#include "lecp.h"
#include<QtGui/QPen>
#include<QtGui/QMouseEvent>
#include <qmessagebox.h>
#include<DataStruct.h>
#include<Tool.h>
#include<iostream>
#include<vertex.h>
using namespace std;

extern bool comparePoint(LECP_Point a, LECP_Point b);

LECP::LECP(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	lecp_doc = new LECP_Doc();

	
	Qt::WindowFlags flags = 0;
	flags |= Qt::WindowMinimizeButtonHint;
	setWindowFlags(flags); // 设置禁止最大化
	setFixedSize(lecp_doc->windowWidth, lecp_doc->windowHeight);
	

	int width = this->width();
	int height = this->height();
	mesh = new Mesh();
	paintWidget = new PaintWidget(width, height);
	this->setCentralWidget(paintWidget);

	QObject::connect(ui.polar_angle_sort, SIGNAL(triggered()), this, SLOT(polarAngleSortSlot()));
	
	lecp_doc = new LECP_Doc();

	// deal with button signals
	signalMapper = new QSignalMapper(this);
	connect(ui.btn_vg, SIGNAL(clicked()),signalMapper, SLOT(map()));
	signalMapper->setMapping(ui.btn_vg, "VG_show");
	connect(signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(doClicked(const QString &)));
	connect(this, SIGNAL(showVGSignal()), this, SLOT(showVGSlot()));

}

LECP::~LECP()
{

}

/*
void LECP::paintEvent(QPaintEvent *event){
	QPainter painter(&pix);

	QPen pen(qRgb(255, 0, 0));

	painter.setPen(pen);

	painter.setBrush(QBrush(Qt::red));

	if (flag){
		LECP_Point point(currentPoint.x(), currentPoint.y());
		bool add=lecp_doc->addPoint(point);
		painter.drawEllipse(currentPoint.x(), currentPoint.x(), 6, 6);

		if (add){
			
			
			//mesh->AddLine((double)currentPoint.x(), (double)currentPoint.y());
		}
		
		QPainter painterTmp(this);
		painterTmp.drawPixmap(0, 0, pix);
	}
	
	
}


void LECP::mouseReleaseEvent(QMouseEvent *event){
	if (event->button() == Qt::LeftButton){//鼠标左键按下
		currentPoint = event->pos();
		flag = true;
		update();
	}
}
*/

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

void LECP::resizeEvent(QResizeEvent *event){
}

<<<<<<< HEAD
void  LECP::polarAngleSortSlot(){
	//首先将输入的所有点按照从左到右的顺序排列
	vector<LECP_Point> points = lecp_doc->points;
	sort(points.begin(), points.end(), comparePoint);

	for (long i = 0; i < points.size(); i++){
		LECP_Point tmpPoint = points[i];
		vector<LECP_Point> subV(points.begin() + i + 1, points.end());
		list<LECP_Point> polarList = getPolarSort(tmpPoint, subV);
		mesh->polarAngleSortedVector.push_back(polarList);
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
=======
void LECP::doClicked(const QString & btnname)
{
	if (btnname == "VG_show")
	{
		emit showVGSignal();
	}
}
void LECP::showVGSlot()
{
	QMessageBox::warning(this, tr("to show"), tr("show animation of VG!"));

>>>>>>> develop
}