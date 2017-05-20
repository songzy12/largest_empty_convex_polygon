#ifndef LECP_H
#define LECP_H

#include <QtWidgets/QMainWindow>
#include <QtGui/QPainter>
#include <QtGui/QPen>
#include "ui_lecp.h"
#include"Paint.h"
#include"lecp_doc.h"

class LECP : public QMainWindow
{
	Q_OBJECT

public:
	LECP(QWidget *parent = 0);
	~LECP();

	
private:
	Ui::LECPClass ui;

	PaintWidget *paintWidget;	

public:
	
public slots:
	void polarAngleSortSlot();//对于每个输入点，该点左侧的所有点按照关于该点进行极角排序
	void showVisibilityGraphSlot();
	void saveFileSlot();
	void openFileSlot();
	void polarAngleSortDCELSlot();
public:
	Mesh *mesh;
	LECP_Doc* lecp_doc;
};

#endif // LECP_H
