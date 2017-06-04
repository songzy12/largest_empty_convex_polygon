#include <QtGui/QPen>
#include <QtGui/QMouseEvent>
#include <QInputDialog>
#include <QMessageBox>
#include <iostream>
#include <time.h>
#include <vertex.h>
#include <thread>
#include "util.h"
#include "lecp.h"
#include "polygon.h"
#include "paint.h"
using namespace std;

LECP::LECP(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->setFixedSize(WIN_WIDTH, WIN_HEIGHT);
	
	showSort = false;
	showVG = false;
	showChain = false;

	isStart = false;
	isStop = false;

	showDCEL=false;
	showQ=false;
	showL=false;

	showspeed = 1; // default to fast
	lastSelectedPoint = 0; // TODO: -1 or not?

	mesh = new Mesh();
	
	paintWidget = new PaintWidget(this->width(), this->height());
	this->setCentralWidget(paintWidget);

	poly2show = new Polygon(paintWidget);
	poly2show->setSleepTime(showspeed); // TODO: semantic

	createToolBar();    //创建工具栏 
	this->addToolBarBreak();
	//operationTB:action
	QObject::connect(ui.openFile, SIGNAL(triggered()), this, SLOT(openFileSlot()));
	QObject::connect(ui.saveFile, SIGNAL(triggered()), this, SLOT(saveFileSlot()));
	QObject::connect(ui.reset, SIGNAL(triggered()), this, SLOT(resetPointsSlot())); // TODO: why?
	QObject::connect(ui.randomPoints, SIGNAL(triggered()), this, SLOT(randomPointsGenerationSlot()));
	QObject::connect(ui.finalResultShow, SIGNAL(triggered()), this, SLOT(finalResultShowSlot()));
	QObject::connect(ui.allPointsShow, SIGNAL(triggered()), this, SLOT(allPointsShowSlot()));
	QObject::connect(ui.singlePointShow, SIGNAL(triggered()), this, SLOT(singlePointShowSlot()));

	//pointSelectTB 点选择-工具栏:action
	QObject::connect(ui.lastPoint, SIGNAL(triggered()), this, SLOT(lastPointSlot()));
	QObject::connect(ui.nextPoint, SIGNAL(triggered()), this, SLOT(nextPointSlot()));

	//strartShowTB 开始演示-工具栏:action
	QObject::connect(ui.startShow, SIGNAL(triggered()), this, SLOT(startShowSlot()));

	//DCEL 动画
	QObject::connect(ui.DCEL_animation, SIGNAL(triggered()), this, SLOT(DCELAnimationSlot()));
	QObject::connect(ui.clearDCELAnimation, SIGNAL(triggered()), this, SLOT(clearDCELAnimationSlot()));
}

LECP::~LECP()
{
	delete mesh;
	delete poly2show;
	delete paintWidget;
	clearToolBar();
}

void LECP::createToolBar()
{
	//工具栏 
	this->ui.pointSelectTB->hide();
	this->ui.strartShowTB->hide();
	this->ui.showContentTB->hide();
	this->ui.sortTB->hide();
	this->ui.qTB->hide();
	this->ui.lTB->hide();
	this->ui.showControlTB->hide();

	//pointSelectTB 点选择-工具栏
	QLabel* psLabel= new QLabel(tr("select a point to show animation: "));
	pointSpinBox = new QSpinBox(this);
	pointSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
	pointSpinBox->setValue(0);
	pointSpinBox->setMinimum(0);
	pointSpinBox->setMaximum(10000);
	pointSpinBox->setSingleStep(1);
	this->ui.pointSelectTB->insertWidget(this->ui.nextPoint, pointSpinBox);

	//showContentTB 演示内容-工具栏
	QLabel* contentLabel = new QLabel(tr("show contents:     "));
	sortComboBox = new QCheckBox(tr("1.sort    "));
	vgComboBox = new QCheckBox(tr("2.VG    "));
	chainComboBox = new QCheckBox(tr("3.chain    "));
	this->ui.showContentTB->addWidget(contentLabel);
	this->ui.showContentTB->addWidget(sortComboBox);
	this->ui.showContentTB->addWidget(vgComboBox);
	this->ui.showContentTB->addWidget(chainComboBox);

	connect(sortComboBox, SIGNAL(stateChanged(int)), this, SLOT(onSortSelected(int)));
	connect(vgComboBox, SIGNAL(stateChanged(int)), this, SLOT(onVGSelected(int)));
	connect(chainComboBox, SIGNAL(stateChanged(int)), this, SLOT(onChainSelected(int)));

	//sortTB 排序-工具栏
	dcelComboBox = new QCheckBox(tr("dcel sort"));
	this->ui.sortTB->addWidget(dcelComboBox);
	connect(dcelComboBox, SIGNAL(stateChanged(int)), this, SLOT(onDCELSelected(int)));

	//qTB vg-工具栏
	qComboBox = new QCheckBox(tr("show Q"));
	this->ui.qTB->addWidget(qComboBox);
	connect(qComboBox, SIGNAL(stateChanged(int)), this, SLOT(onQueueSelected(int)));

	//lTB chain-工具栏
	lComboBox = new QCheckBox(tr("show L"));
	this->ui.lTB->addWidget(lComboBox);
	connect(lComboBox, SIGNAL(stateChanged(int)), this, SLOT(onLSelected(int)));

	//showControlTB 速度控制-工具栏
	QLabel* speedLabel = new QLabel(tr("show speed:    "));

	speedSpinBox = new QSpinBox(this);
	speedSpinBox->setMinimum(showSpeedMin);
	speedSpinBox->setMaximum(showSpeedMax);
	speedSpinBox->setSingleStep(1);

	speedSlider = new QSlider(this);
	speedSlider->setOrientation(Qt::Horizontal);
	speedSlider->setMinimum(showSpeedMin);
	speedSlider->setMaximum(showSpeedMax);
	speedSlider->setSingleStep(1);
	speedSlider->setTickInterval(1);
	speedSlider->setTickPosition(QSlider::TicksAbove);
	speedSlider->setFixedWidth(240);

	this->ui.showControlTB->addWidget(speedLabel);
	this->ui.showControlTB->addWidget(speedSpinBox);
	this->ui.showControlTB->addWidget(speedSlider);

	connect(speedSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeSpeedSlot(int)));
	connect(speedSlider, SIGNAL(valueChanged(int)), this, SLOT(changeSpeedSlot(int)));
	
}

void LECP::clearToolBar() {	
	delete sortComboBox;
	delete vgComboBox;
	delete chainComboBox;
	delete dcelComboBox;
	delete qComboBox;
	delete lComboBox;

	delete pointSpinBox;
	delete speedSpinBox;
	delete speedSlider;
}


//operationTB:slot
void LECP::openFileSlot() {
	QDir dir;
	QString fileName = QFileDialog::getOpenFileName(this, QString("Open File"), dir.absolutePath());
	if (fileName.isEmpty()){
		return;
	}

	QByteArray ba = fileName.toLocal8Bit();
	char* fileName_str = ba.data();

	paintWidget->loadPoints(fileName_str);
}

void LECP::saveFileSlot() {
	QString saveFileName;
	saveFileName = QFileDialog::getSaveFileName(this, tr("save file"));

	if (!saveFileName.isNull())
	{
		char *str = (char *)malloc(255);
		QByteArray ba = saveFileName.toLatin1();
		strcpy(str, ba.data());

		bool re = paintWidget->savePoints(str);
		if (re)
		{
			QMessageBox box;
			box.about(paintWidget, "Success", "Save successfull!");
			box.show();
			paintWidget->update();
		}
	}
}

void LECP::resetPointsSlot()
{
	mesh->clear();
	mesh->init();
	poly2show->clear();
	paintWidget->clear();
}

void LECP::randomPointsGenerationSlot(){
	bool isOK;
	QString text = QInputDialog::getText(NULL, "Input points number", "Please input the number of points:", QLineEdit::Normal, "points number", &isOK);
	if (isOK){
		resetPointsSlot();
		int points_number = text.toInt();
		qDebug() << "random points number:" << points_number << endl;
		paintWidget->setPoints(generateRandomPoints(points_number));
	}
}

void LECP::finalResultShowSlot()
{
	//控件显示控制
	this->ui.pointSelectTB->hide();
	this->ui.strartShowTB->show();
	this->ui.showContentTB->hide();
	this->ui.sortTB->hide();
	this->ui.qTB->hide();
	this->ui.lTB->hide();
	this->ui.showControlTB->hide();

	showSort = false;
	showVG = false;
	showChain = false;
	showDCEL = false;
	showQ = false;
	showL = false;
	
	//演示模式设置
	currMode = finalRes;
	if (pointSpinBox->value() >= 0 && pointSpinBox->value() < paintWidget->myQPoints.size())
		paintWidget->myQPoints.at(pointSpinBox->value())->setColor(Qt::red); 
	paintWidget->repaint();
}

void LECP::allPointsShowSlot()
{
	//控件显示控制
	this->ui.pointSelectTB->hide();
	if (showSort || showVG ||showChain)
		this->ui.strartShowTB->show();
	else
		this->ui.strartShowTB->hide();

	this->ui.showContentTB->show();
	if (showSort)
		this->ui.sortTB->show();
	else
		this->ui.sortTB->hide();

	if (showVG)
		this->ui.qTB->show();
	else
		this->ui.qTB->hide();

	if (showChain)
		this->ui.lTB->show();
	else
		this->ui.lTB->hide();

	this->ui.showControlTB->show();

	//演示模式设置
	currMode = allPoints;
	if (pointSpinBox->value() >= 0 && pointSpinBox->value() < paintWidget->myQPoints.size())
		paintWidget->myQPoints.at(pointSpinBox->value())->setColor(Qt::red);
	paintWidget->repaint();
}

void LECP::singlePointShowSlot()
{
	//控件显示控制
	this->ui.pointSelectTB->show();

	if (showSort || showVG || showChain)
		this->ui.strartShowTB->show();
	else
		this->ui.strartShowTB->hide();

	this->ui.showContentTB->show();
	if (showSort)
		this->ui.sortTB->show();
	else
		this->ui.sortTB->hide();

	if (showVG)
		this->ui.qTB->show();
	else
		this->ui.qTB->hide();

	if (showChain)
		this->ui.lTB->show();
	else
		this->ui.lTB->hide();

	this->ui.showControlTB->show();

	//演示模式设置
	currMode = singlePoint;

	//默认选择0号点
	if (paintWidget->myQPoints.size() != 0){  // Added by zyx
		paintWidget->myQPoints.at(0)->setColor(Qt::cyan); // TODO: why different?
		paintWidget->repaint();
	}
	
}


//pointSelectTB 点选择-工具栏:slot
void LECP::lastPointSlot()
{
	int val = max(pointSpinBox->value() - 1, 0);
	pointSpinBox->setValue(val);
	if (lastSelectedPoint >= 0 && lastSelectedPoint < paintWidget->myQPoints.size())
		paintWidget->myQPoints.at(lastSelectedPoint)->setColor(Qt::red);
	if (val >= 0 && val < paintWidget->myQPoints.size())
		paintWidget->myQPoints.at(val)->setColor(Qt::cyan);
	lastSelectedPoint = val;
	paintWidget->repaint();
}

void LECP::nextPointSlot()
{    
	int val = lastSelectedPoint;
	if (pointSpinBox->value() + 1 < paintWidget->myQPoints.size())
		val = pointSpinBox->value() + 1;
	pointSpinBox->setValue(val);
	if (lastSelectedPoint >= 0 && lastSelectedPoint < paintWidget->myQPoints.size())
		paintWidget->myQPoints.at(lastSelectedPoint)->setColor(Qt::red);
	if (val >= 0 && val < paintWidget->myQPoints.size())
		paintWidget->myQPoints.at(val)->setColor(Qt::cyan);
	lastSelectedPoint = val;
	paintWidget->repaint();
}


//strartShowTB 开始演示-工具栏:slot
void LECP::startShowSlot()
{
	if (!checkPoints())
		QMessageBox::warning(this, tr("Warning"), tr("the number of the points should >=3"));
	else {

		isStart = true;//演示结束时设为false
		/*if (lecp_doc->points.size() < 3)
		{
		QMessageBox::warning(NULL, "Warning", "add at lest 3 points to start animation!", QMessageBox::Yes);
		return ;
		}*/
		poly2show->clear();
		//dcel
		if (showDCEL)
		{
			DCELAnimationSlot();
			_sleep(1500);
			clearDCELAnimationSlot();
		}
		else {
			//std::thread t1(&LECP::polarAngleSortDCELSlot, this);
			//t1.join();
			polarAngleSortDCELSlot();
		}

		int kernalNum = mesh->sortedVector.size();

		//mode 选择
		switch (currMode)
		{
		case finalRes:
		{
			vector<Vertex *> longest_convex_chain;
			longest_convex_chain.clear();
			Vertex * longest_chain_kernel = nullptr;
			for (int kernal_index = kernalNum - 1; kernal_index >= 0; kernal_index--) {
				poly2show->clear();
				trans2Poly(kernal_index);
				if (poly2show->convex_chain_.size() > longest_convex_chain.size()) {
					longest_convex_chain = poly2show->convex_chain_;
					longest_chain_kernel = poly2show->kernel();
				}
			}
			poly2show->clear();
			poly2show->getPaintWidget()->allQLines2Draw.clear();
			
			if (longest_convex_chain.size() > 2){
				longest_convex_chain.push_back(longest_chain_kernel);
				MyQline temp_edge;
				temp_edge.setLine(longest_chain_kernel->point().first, longest_chain_kernel->point().second*-1, longest_convex_chain.at(0)->point().first, longest_convex_chain.at(0)->point().second*-1);
				temp_edge.setColor(Qt::black);
				poly2show->getPaintWidget()->allQLines2Draw.push_back(temp_edge);
				for (int i = 0; i < longest_convex_chain.size() - 1; i++){
					temp_edge.setLine(longest_convex_chain.at(i)->point().first, longest_convex_chain.at(i)->point().second*-1, longest_convex_chain.at(i + 1)->point().first, longest_convex_chain.at(i + 1)->point().second*-1);
					temp_edge.setColor(Qt::black);
					poly2show->getPaintWidget()->allQLines2Draw.push_back(temp_edge);
				}
				this->repaint();
			}
			else
				QMessageBox::warning(this, tr("Not find LECP"), tr("Not find LECP"));
			break;
		}

		case allPoints: {
			//循环处理每个点
			vector<Vertex *> longest_convex_chain;
			longest_convex_chain.clear();
			Vertex * longest_chain_kernel = nullptr;
			for (int kernal_index = kernalNum - 1; kernal_index >= 0; kernal_index--) {
				poly2show->clear();
				trans2Poly(kernal_index);
				if (poly2show->convex_chain_.size() > longest_convex_chain.size()) {
					longest_convex_chain = poly2show->convex_chain_;
					longest_chain_kernel = poly2show->kernel();
				}
			}
			/*qDebug() << "longest_convex_chain length:" << longest_convex_chain.size();

			if (longest_chain_kernel)
			qDebug() << "longest chain kernel:" << longest_chain_kernel->point().first << longest_chain_kernel->point().second;*/

			//_sleep(2000);
			poly2show->clear();
			poly2show->getPaintWidget()->allQLines2Draw.clear();

			if (longest_convex_chain.size() > 2){
				longest_convex_chain.push_back(longest_chain_kernel);
				MyQline temp_edge;
				temp_edge.setLine(longest_chain_kernel->point().first, longest_chain_kernel->point().second*-1, longest_convex_chain.at(0)->point().first, longest_convex_chain.at(0)->point().second*-1);
				temp_edge.setColor(Qt::black);
				poly2show->getPaintWidget()->allQLines2Draw.push_back(temp_edge);
				for (int i = 0; i < longest_convex_chain.size() - 1; i++){
					temp_edge.setLine(longest_convex_chain.at(i)->point().first, longest_convex_chain.at(i)->point().second*-1, longest_convex_chain.at(i + 1)->point().first, longest_convex_chain.at(i + 1)->point().second*-1);
					temp_edge.setColor(Qt::black);
					poly2show->getPaintWidget()->allQLines2Draw.push_back(temp_edge);
				}
				this->repaint();
			}
			else
				QMessageBox::warning(this, tr("Not find LECP"), tr("Not find LECP"));
			break;
		}
		case singlePoint:{
			if (showVG) {
				poly2show->clear();
				int kernalSelected = getSortedIndex(pointSpinBox->value());
				trans2Poly(kernalSelected);
			}
			break; 
		}
		}
	}
}

void LECP::resetShowSlot()
{
	poly2show->clear();
}

//showContentTB 演示内容-工具栏:slot
void LECP::onSortSelected(int flag)
{
	switch (flag)
	{
	case 0:
		showSort = false;
		showDCEL = false;
		break;
	case 2:
		showSort = true;
		break;
	}

	if ((!showSort) && (!showChain) && (!showVG))
		this->ui.strartShowTB->hide();
	else
		this->ui.strartShowTB->show();

	if (showSort)
		this->ui.sortTB->show();
	else
		this->ui.sortTB->hide();
}

void LECP::onVGSelected(int flag)
{
	switch (flag)
	{
	case 0:
		showVG = false;
		showQ = false;
		break;
	case 2:
		showVG = true;
		break;
	}
	if ((!showSort) && (!showChain) && (!showVG))
		this->ui.strartShowTB->hide();
	else
		this->ui.strartShowTB->show();

	if (showVG)
		this->ui.qTB->show();
	else
		this->ui.qTB->hide();
}

void LECP::onChainSelected(int flag)
{
	switch (flag)
	{
	case 0:
		showChain = false;
		showL = false;
		break;
	case 2:
		showChain = true;
		break;
	}
	if ((!showSort) && (!showChain) && (!showVG))
		this->ui.strartShowTB->hide();
	else
		this->ui.strartShowTB->show();

	if (showChain)
		this->ui.lTB->show();
	else
		this->ui.lTB->hide();
}


//sortTB 排序-工具栏:slot
void  LECP::onDCELSelected(int flag)
{
	switch (flag)
	{
	case 0:
		showDCEL = false;
		break;
	case 2:
		showDCEL = true;
		break;
	}
}

//qTB vg-工具栏:slot
void  LECP::onQueueSelected(int flag)
{
	switch (flag)
	{
	case 0:
		showQ = false;
		break;
	case 2:
		showQ = true;
		break;
	}
}

//lTB chain-工具栏:slot
void  LECP::onLSelected(int flag)
{
	switch (flag)
	{
	case 0:
		showL = false;
		break;
	case 2:
		showL = true;
		break;
	}
}

//showControlTB 速度控制-工具栏:slot
void LECP::changeSpeedSlot(int newSpeed)
{
	speedSpinBox->setValue(newSpeed);
	speedSlider->setValue(newSpeed);
	showspeed = (showSpeedMax- newSpeed);
	if (poly2show != NULL)
	{
		poly2show->setSleepTime(showspeed);
	}
}

//未归正slots
Vertex* pole;
bool compareVertex(Vertex* p, Vertex* q){
	double px = p->point().first;
	double py = p->point().second;
	double sx = pole->point().first;
	double sy = pole->point().second;
	double qx = q->point().first;
	double qy = q->point().second;


	double area = px*qy - py*qx + qx*sy - qy*sx + sx*py - sy*px;
	if (area > 0)
		return true;
	return false;
}

vector<LECP_Point*> LECP::preprocessingPolarAngleSort() {

	//首先将输入的所有点按照从左到右的顺序排列
	vector<LECP_Point*> points = paintWidget->points;
	sort(points.begin(), points.end(), comparePoint);

	for (long long i = 0; i < points.size(); i++)
		points[i]->sortedIndex = i;

	return points;
}

// if not exit,return -1
long long LECP::getSortedIndex(long long displayIndex) {
	for (long long i = 0; i < paintWidget->points.size(); i++){
		LECP_Point* point = paintWidget->points[i];
		if (point->index == displayIndex)
			return point->sortedIndex;
	}

	return -1;
}

//polar angle sort: naive method
void LECP::polarAngleSortSlot() {
	time_t start = clock();

	mesh->clear();
	mesh->init();
	vector<LECP_Point*> points = preprocessingPolarAngleSort();
	
	list<Vertex*> polarVextex = changeLECO_PointToVertex(points);

	list<Vertex*>::iterator it = polarVextex.begin();
	while (it != polarVextex.end()){
		pole = *it;

		list<Vertex*> subV(++it, polarVextex.end());
		subV.sort(compareVertex);

		subV.push_front(pole);

		mesh->sortedVector.push_back(subV);
	}

	time_t end = clock();
	double runTime = double(end - start) * 1000 / CLOCKS_PER_SEC;

	cout << "Naive methon for polar angle sort:" << runTime << "ms," << points.size() << " points" << endl;

	/*
	QString msg = "Naive methon for polar angle sort:"+QString::number(runTime)+"ms"+","+QString::number(points.size())+" points";
	QMessageBox box;
	box.about(this, "running time", msg);
	box.show();
	*/
}

//DCEL algorithm for polar angle sort result
void LECP::polarAngleSortDCELSlot() {
	paintWidget->myQPoints.at(lastSelectedPoint)->setColor(Qt::red);
	paintWidget->repaint();

	time_t start = clock();

	mesh->clear();
	mesh->init();
	vector<LECP_Point*> points = preprocessingPolarAngleSort();
	for (long long i = points.size()-1; i>= 0; i--){
		LECP_Point *point = points[i];
		qDebug() << "point" << i << "of" << points.size();
		vector<pair<LECP_Point*, LECP_Point*>> lecp_points = mesh->AddLine(point);

		//将交点加上当前点存入mesh的sortedPoint中，并处理横坐标相同的点的情况
		mesh->addCurrentAngleSortedResultToVector(point, lecp_points, points);
	}

	mesh->postCalcPolarAngle(); // change LECP to Vertex

	time_t end = clock();
	double runTime = double(end - start) * 1000 / CLOCKS_PER_SEC;

	qDebug() << "DCEL polar angle sort:" << runTime << " ms," << points.size() << " points" << endl;

	/*
	QString msg = "DCEL polar angle sort:" + QString::number(runTime) + "ms" + "," + QString::number(points.size()) + " points";
	QMessageBox box;
	box.about(this, "running time", msg);
	box.show();
	*/

}

//DCEL 动画
//调用之前先clear,否则结果会累加  modified by xyz
void LECP::DCELAnimationSlot(){
	vector<LECP_Point*> points = preprocessingPolarAngleSort();

	for (long long i = points.size() - 1; i >= 0; i--) {
		LECP_Point *point = points[i];

		MyQPoint  *qPoint = paintWidget->changeLECP_PointToMyQPoint(point);

		vector<pair<LECP_Point*, LECP_Point*>> lecp_points = mesh->AddLine(point);

		//将交点加上当前点存入mesh的sortedPoint中，并处理横坐标相同的点的情况
		mesh->addCurrentAngleSortedResultToVector(point,lecp_points,points);

		paintWidget->animationPoint(qPoint, lecp_points,showspeed);

		_sleep(showspeed * 100);
		qPoint->setColor(Qt::red);
		paintWidget->update();
	}

	mesh->postCalcPolarAngle();
}

void LECP::clearDCELAnimationSlot(){
	paintWidget->lines.clear(); // TODO: also delete
}


////////////////////////////////////////////////////////////////////////////

Polygon* LECP::trans2Poly(int kernal_index)
{
	if (kernal_index < 0)
		qDebug() << "kernal index should >=0 in Fun trans2Poly(int kernal_index)";
	else{
		int pointsNum = 1;
		//循环处理每个点
		vector<Vertex*> temp_vertices;
		int vertexNum = mesh->sortedVector.at(kernal_index).size();

		if (vertexNum < 3)//不存在一个凸包
			return NULL;

		list<Vertex*>::iterator iter_vertex = mesh->sortedVector.at(kernal_index).begin();
		while (iter_vertex != mesh->sortedVector.at(kernal_index).end())
		{
			temp_vertices.push_back(*iter_vertex);
			iter_vertex++;
		}
		poly2show->setVertices(temp_vertices);

		//animation_kernal & starpolygon
		poly2show->getPaintWidget()->allQPoints2Draw.clear();

		//kernal:
		MyQPoint kernal(QPoint(temp_vertices[0]->point().first, temp_vertices[0]->point().second*-1));
		kernal.setColor(Qt::red);
		kernal.setIndex(temp_vertices[0]->index());
		poly2show->getPaintWidget()->allQPoints2Draw.push_back(kernal);
		//other points
		for (int i = 1; i < vertexNum; i++){//转化vertex为MyQPoint
			MyQPoint temp_myqpoint(QPoint(temp_vertices[i]->point().first, temp_vertices[i]->point().second*-1));
			temp_myqpoint.setColor(Qt::blue);
			temp_myqpoint.setIndex(temp_vertices[i]->index());
			//temp_myqpoint.setQ(temp_vertices[i]->Q_);
			temp_myqpoint.setShowQ(showQ);
			poly2show->getPaintWidget()->allQPoints2Draw.push_back(temp_myqpoint);
			if (currMode != 0){
				poly2show->getPaintWidget()->repaint();
				if (showSort)
					_sleep(showspeed * 100);
			}
			MyQline edge_i(QLine(poly2show->vertices().at(i - 1)->point().first, poly2show->vertices().at(i - 1)->point().second*-1, poly2show->vertices().at(i)->point().first, poly2show->vertices().at(i)->point().second*-1));
			edge_i.setDotStyle(true);
			poly2show->getPaintWidget()->allQLines2Draw.push_back(edge_i);
			if (currMode != 0){
				poly2show->getPaintWidget()->repaint();
				if (showSort)
					_sleep(showspeed * 100);
			}
		}
		MyQline edge_i(QLine(poly2show->vertices().at(vertexNum - 1)->point().first, poly2show->vertices().at(vertexNum - 1)->point().second*-1, poly2show->vertices().at(0)->point().first, poly2show->vertices().at(0)->point().second*-1));
		edge_i.setDotStyle(true);
		poly2show->getPaintWidget()->allQLines2Draw.push_back(edge_i);
		if (currMode != 0)
			poly2show->getPaintWidget()->repaint();
		//animation_kernal & starpolygon end//

		if (currMode != 0)
			_sleep(1500);
		temp_vertices = poly2show->getVisibilityGraph(showVG, showQ, currMode);

		//animation_做chain之前把点和半边的状态更新一下
		for (int i = 1; i < vertexNum; i++){
			poly2show->getPaintWidget()->allQPoints2Draw.at(i).setColor(Qt::blue);
			poly2show->getPaintWidget()->allQPoints2Draw.at(i).setShowQ(false);
		}
		int last_index = poly2show->getPaintWidget()->allQLines2Draw.size() - 1;
		//poly2show->getPaintWidget()->allQLines2Draw.at(last_index - 1).setColor(Qt::green);
		//poly2show->getPaintWidget()->allQLines2Draw.at(last_index).setColor(Qt::cyan);
		poly2show->getPaintWidget()->allQLines2Draw.at(last_index).setColor(Qt::green);
		int lineNum = poly2show->getPaintWidget()->allQLines2Draw.size();
		for (int i = 0; i < lineNum; i++)
		{
			poly2show->getPaintWidget()->allQLines2Draw.at(i).setDotStyle(true);
		}
		if (currMode != 0)
			poly2show->getPaintWidget()->repaint();
		//animation_做chain之前把点和半边的状态更新一下 end//

		if (currMode != 0)
			_sleep(1500);
		temp_vertices = poly2show->getConvexChain(showChain, showL, currMode);
		temp_vertices.clear(); // why?   ans:只是想释放一下
		/*}*/
	}
	return poly2show;
}

bool LECP::checkPoints()
{
	return paintWidget->points.size() >= 3;
}