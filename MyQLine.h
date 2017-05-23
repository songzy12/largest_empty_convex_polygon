#ifndef MYQLINE_H
#define MYQLINE_H

#include <qline.h>
#include <qcolor.h>

class MyQline :public QLine{
public:
	MyQline();
	MyQline(QLine Qline);
	~MyQline(){}
	QColor getColor();
	void setColor(QColor color);
	void setDotStyle(bool use);
	bool getDotStyle();
public:
	QColor color_;
	bool use_dot_style_;
};

#endif