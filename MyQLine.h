#ifndef MYQLINE_H
#define MYQLINE_H

#include <qline.h>
#include <qcolor.h>

class MyQline :public QLine{
public:
	MyQline(QLine Qline);
	~MyQline(){}
	QColor getColor();
	void setColor(QColor color);
public:
	QColor color_;
};

#endif