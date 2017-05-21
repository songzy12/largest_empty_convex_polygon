#ifndef DISPLAYDCEL_H
#define DISPLAYDCEL_H

#include <qwidget.h>
#include <MyQPoint.h>
#include <vector>
#include<qpaintengine.h>

using namespace std;

class DisplayDCEL :public QWidget{
public:
	DisplayDCEL();
	DisplayDCEL(int width,int height);
	~DisplayDCEL(){};

	void addLine(MyQPoint *qPoint);
	void paintAllLine();
	void paintLine(MyQPoint *line);
protected:
	void paintEvent(QPaintEvent *event);

public:
	vector<MyQPoint*> points;
};

#endif