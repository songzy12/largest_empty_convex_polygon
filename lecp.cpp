#include "lecp.h"
#include<QtGui/QPen>
#include<QtGui/QMouseEvent>
#include<DataStruct.h>
#include<Tool.h>
#include<iostream>
using namespace std;

LECP::LECP(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	Qt::WindowFlags flags = 0;
	flags |= Qt::WindowMinimizeButtonHint;
	setWindowFlags(flags); // 设置禁止最大化
	setFixedSize(1200, 800);

	pix = QPixmap(this->width(), this->height());
	pix.fill(Qt::white);
	flag = false;
	
	lecp_doc = new LECP_Doc();
}

LECP::~LECP()
{

}

void LECP::paintEvent(QPaintEvent *event){
	QPainter painter(&pix);

	QPen pen(qRgb(255, 0, 0));

	painter.setPen(pen);

	painter.setBrush(QBrush(Qt::red));

	if (flag){
		LECP_Point point(currentPoint.x(), currentPoint.y());
		bool add=lecp_doc->addPoint(point);
		painter.drawEllipse(currentPoint.x(), currentPoint.y(), 6, 6);

		if (add)
		cout << lecp_doc->points.size() << " point：" << currentPoint.x()<<","<< currentPoint.y() << endl;

		
	}
	
	QPainter painterTmp(this);
	painterTmp.drawPixmap(0, 0, pix);
}

void LECP::mouseReleaseEvent(QMouseEvent *event){
	if (event->button() == Qt::LeftButton){//鼠标左键按下
		currentPoint = event->pos();
		flag = true;
		update();
	}
}

void LECP::mousePressEvent(QMouseEvent *event){
	flag = false;
}

void LECP::resizeEvent(QResizeEvent *event){
}
