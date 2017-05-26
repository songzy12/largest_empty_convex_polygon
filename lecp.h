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
	QCheckBox* sortComboBox,*vgComboBox,*chainComboBox;


	QPushButton* startButton;
	QPushButton* stopButton;
	QPushButton* resetButton;
	QSlider* speedSlider;
	QSpinBox *speedSpinBox,*pointSpinBox;

	QAction *openAction;

public:
	void createToolBar();
	Polygon* trans2Poly(int kernal_index);
public slots:
	//operationTB:slot
	void openFileSlot();
	void saveFileSlot();
	void resetPointsSlot();
	void randomPointsGenerationSlot();
	void finalResultShowSlot();
	void allPointsShowSlot();
	void singlePointShowSlot();

	//pointSelectTB 点选择-工具栏:slot
	void lastPointSlot();
	void nextPointSlot();

	//strartShowTB 开始演示-工具栏:slot
	void startShowSlot();
	void resetShowSlot();

	//showContentTB 演示内容-工具栏:slot
	void onSortSelected(int flag);
	void onVGSelected(int flag);
	void onChainSelected(int flag);

	//sortTB 排序-工具栏:slot
	void onDCELSelected(int flag);

	//qTB vg-工具栏:slot
	void onQueueSelected(int flag);

	//lTB chain-工具栏:slot
	void onLSelected(int flag);

	//showControlTB 速度控制-工具栏:slot
	void changeSpeedSlot(int newSpeed);



	void polarAngleSortSlot();//对于每个输入点，该点左侧的所有点按照关于该点进行极角排序
	void showVisibilityGraphSlot();
	void showConvexChainSlot();

	void polarAngleSortDCELSlot();
	//DCEL 动画
	void DCELAnimationSlot();
	void clearDCELAnimationSlot();
	void resetSlot();



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
