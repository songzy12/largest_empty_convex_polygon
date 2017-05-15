#ifndef LECP_H
#define LECP_H

#include <QtWidgets/QMainWindow>
#include "ui_lecp.h"
#include <QtGui/QPainter>
#include<QtGui/QPen>
#include <qsignalmapper.h>
#include"Tool.h"
#include"DataStruct.h"
#include "mesh.h"
#include "Paint.h"

class LECP : public QMainWindow
{
	Q_OBJECT

public:
	LECP(QWidget *parent = 0);
	~LECP();

private:
	Ui::LECPClass ui;

	PaintWidget *paintWidget;
protected:
	//void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void resizeEvent(QResizeEvent *event);
	//void mouseReleaseEvent(QMouseEvent *event);
	//void mouseMoveEvent(QMouseEvent *event);

	list<LECP_Point> getPolarSort(LECP_Point tmpPoint,vector<LECP_Point> subV);

public:
	QPoint currentPoint;//当前点
	QPixmap pix;//保存绘画结果

	/*deal with signals mapping*/
	QSignalMapper *signalMapper;

	bool flag;//画点是否开启

	LECP_Doc *lecp_doc;
	Mesh *mesh;
public slots:
  void polarAngleSortSlot();//对于每个输入点，该点左侧的所有点按照关于该点进行极角排序

private slots:
	void doClicked(const QString & btnname);
	void showVGSlot();

signals:
	void showVGSignal();
};

#endif // LECP_H
