#ifndef LECP_H
#define LECP_H
#define showSpeedMax 20
#define showSpeedMin 1

#include <QtWidgets/QMainWindow>
#include <QtGui/QPainter>
#include <QtGui/QPen>

#include <qspinbox.h>
#include <qmessagebox.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <qdebug.h>
#include <qfiledialog.h>
#include <qslider.h>

#include "ui_lecp.h"
#include"Paint.h"
#include"lecp_doc.h"
#include"DisplayDCEL.h"

class LECP : public QMainWindow
{
	Q_OBJECT

public:
	LECP(QWidget *parent = 0);
	~LECP();

	
private:
	Ui::LECPClass ui;

	PaintWidget *paintWidget;

	//toolbar content:
	QCheckBox* sortComboBox;
	QCheckBox* vgComboBox;
	QCheckBox* chainComboBox;
	QPushButton* pSelectButton;
	QPushButton* startButton;
	QPushButton* stopButton;
	QSlider* speedSlider;
	QSpinBox* pSpinBox;

	QAction *openAction;

public:
	void createToolBar();
	Polygon* trans2Poly(int kernal_index);
public slots:
	void polarAngleSortSlot();//对于每个输入点，该点左侧的所有点按照关于该点进行极角排序
	void showVisibilityGraphSlot();
	void saveFileSlot();
	void openFileSlot();
	void polarAngleSortDCELSlot();

	//DCEL 动画
	void DCELAnimationSlot();
	void clearDCELAnimationSlot();
	void resetSlot();
	//动画演示
	void sortMenuSlot();
	void vgMenuSlot();
	void chainMenuSlot();
	void onSortSelected(int flag);
	void onVGSelected(int flag);
	void onChainSelected(int flag);
	void changeSpeedSlot(int newSpeed);
	void startShowSlot();
	void stopShowSlot();

public:
	Mesh *mesh;
	LECP_Doc* lecp_doc;
	Polygon* poly2show;

	//show variable
	enum showMode { finalRes, allPoints, simplePoint };
	bool showSort = false;
	bool showVG = false;
	bool showChain = false;
	bool isStart = false;
	bool isStop = false;
	int showspeed = 1;

	
};

#endif // LECP_H
