#include "DisplayDCEL.h"

DisplayDCEL::DisplayDCEL(){

}

DisplayDCEL::DisplayDCEL(int width, int height){
	setFixedSize(width, height);
	this->setWindowIconText("Display DCEL");
}

void DisplayDCEL::paintEvent(QPaintEvent *event){
	//QPainter painter(this);
	//painter.setBrush(Qt::blue);

	paintAllLine();
}

void DisplayDCEL::paintAllLine(){
	for (long long i = 0; i < points.size(); i++){
		MyQPoint *tmpP = points[i];
		paintLine(tmpP);
	}
}

void DisplayDCEL::paintLine(MyQPoint *point){
	QPainter painter(this);
	painter.setBrush(point->getColor());

	double a, b;
	a = point->x();
	b = point->y();

	double x1, x2, y1, y2;
	x1 = -300;
	y1 = x1*a - b;
	x2 = 300;
	y2 = x2*a - b;

	QLine line(x1,y1,x2,y2);

	painter.drawLine(line);
	update();
}

void DisplayDCEL::addLine(MyQPoint *qPoint){
	points.push_back(qPoint);
	repaint();
	update();
}