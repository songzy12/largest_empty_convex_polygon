#ifndef MYQLINE_H
#define MYQLINE_H

#define ARROW_ANGLE 0.5
#define ARROW_SIZE 10
#define Pi 3.14159265358979323846264338327950288419717
#define TwoPi 2.0 * Pi
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
	void setArrowStyle(bool use);
	bool getArrowStyle();
	float length();
	int L();
	void setL(int l);
	bool showL();
	void setShowL(bool showL);
public:
	QColor color_;
	//是否使用虚线风格
	bool use_dot_style_;
	//是否带箭头
	bool have_arrow_;
	//是否显示数值L
	bool show_l_;
	int L_;
};

#endif