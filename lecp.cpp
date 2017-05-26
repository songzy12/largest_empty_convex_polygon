#include "lecp.h"
#include <QtGui/QPen>
#include <QtGui/QMouseEvent>
#include <iostream>
#include <vertex.h>
#include <util.h>
#include "lecp_doc.h"
#include <QInputDialog>
#include"time.h"
#include <QMessageBox>
using namespace std;

LECP::LECP(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	lecp_doc = new LECP_Doc();

	setFixedSize(WIN_WIDTH, WIN_HEIGHT);
	
	int width = this->width();
	int height = this->height();
	lastSelectedPoint = 0;

	mesh = new Mesh();
	poly2show = new Polygon();

	paintWidget = new PaintWidget(width, height);
	this->setCentralWidget(paintWidget);
	
	poly2show->setPaintWidget(paintWidget);

	createToolBar();    //创建工具栏 
	this->addToolBarBreak();

	//operationTB:action
	QObject::connect(ui.openFile, SIGNAL(triggered()), this, SLOT(openFileSlot()));
	QObject::connect(ui.saveFile, SIGNAL(triggered()), this, SLOT(saveFileSlot()));
	QObject::connect(ui.reset, SIGNAL(triggered()), this, SLOT(resetPointsSlot()));
	QObject::connect(ui.randomPoints, SIGNAL(triggered()), this, SLOT(randomPointsGenerationSlot()));
	QObject::connect(ui.finalResultShow, SIGNAL(triggered()), this, SLOT(finalResultShowSlot()));
	QObject::connect(ui.allPointsShow, SIGNAL(triggered()), this, SLOT(allPointsShowSlot()));
	QObject::connect(ui.singlePointShow, SIGNAL(triggered()), this, SLOT(singlePointShowSlot()));

	//pointSelectTB 点选择-工具栏:action
	QObject::connect(ui.lastPoint, SIGNAL(triggered()), this, SLOT(lastPointSlot()));
	QObject::connect(ui.nextPoint, SIGNAL(triggered()), this, SLOT(nextPointSlot()));

	//strartShowTB 开始演示-工具栏:action
	QObject::connect(ui.startShow, SIGNAL(triggered()), this, SLOT(startShowSlot()));


	QObject::connect(ui.polar_angle_sort, SIGNAL(triggered()), this, SLOT(polarAngleSortSlot()));
	QObject::connect(ui.create_VG, SIGNAL(triggered()), this, SLOT(showVisibilityGraphSlot()));
	QObject::connect(ui.sortedDCEL, SIGNAL(triggered()), this, SLOT(polarAngleSortDCELSlot()));
	//DCEL 动画
	QObject::connect(ui.DCEL_animation, SIGNAL(triggered()), this, SLOT(DCELAnimationSlot()));
	QObject::connect(ui.clearDCELAnimation, SIGNAL(triggered()), this, SLOT(clearDCELAnimationSlot()));
	QObject::connect(ui.reset, SIGNAL(triggered()), this, SLOT(resetSlot()));

}

LECP::~LECP()
{

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
	poly2show->clear();
	paintWidget->clearMyQPandMyQL();
	poly2show->setPaintWidget(paintWidget);
	
}

void LECP::randomPointsGenerationSlot(){
	bool isOK;
	QString text = QInputDialog::getText(NULL, "Input points number", "Please input the number of points:", QLineEdit::Normal, "points number", &isOK);

	if (isOK){
		int points_number = text.toInt();

		cout << "random points number:" << points_number << endl;

		vector<LECP_Point*> random_points = generateRandomPoints(points_number);
		paintWidget->setPoints(random_points);
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
	this->ui.showControlTB->show();
	
	//演示模式设置
	currMode = finalRes;
}

void LECP::allPointsShowSlot()
{
	//控件显示控制
	this->ui.pointSelectTB->hide();
	this->ui.strartShowTB->hide();
	this->ui.showContentTB->show();
	this->ui.sortTB->hide();
	this->ui.qTB->hide();
	this->ui.lTB->hide();
	this->ui.showControlTB->show();

	//演示模式设置
	currMode = allPoints;
}

void LECP::singlePointShowSlot()
{
	//控件显示控制
	this->ui.pointSelectTB->show();
	this->ui.strartShowTB->hide();
	this->ui.showContentTB->show();
	this->ui.sortTB->hide();
	this->ui.qTB->hide();
	this->ui.lTB->hide();
	this->ui.showControlTB->show();

	//演示模式设置
	currMode = singlePoint;
}


//pointSelectTB 点选择-工具栏:slot
void LECP::lastPointSlot()
{
	int val = pointSpinBox->value() - 1 < 0 ? 0 : pointSpinBox->value() - 1;
	pointSpinBox->setValue(val);
	paintWidget->myQPoints.at(lastSelectedPoint)->setColor(Qt::red);
	paintWidget->myQPoints.at(val)->setColor(Qt::green);
	lastSelectedPoint = val;
	paintWidget->repaint();
	_sleep(1000);
}

void LECP::nextPointSlot()
{    //TODO change 20 to point_num
	int val = pointSpinBox->value() + 1 > poly2show->getPaintWidget()->points.size() - 1 ? poly2show->getPaintWidget()->points.size() - 1 : pointSpinBox->value() + 1;
	pointSpinBox->setValue(val);
	paintWidget->myQPoints.at(lastSelectedPoint)->setColor(Qt::red);
	paintWidget->myQPoints.at(val)->setColor(Qt::green);
	lastSelectedPoint = val;
	paintWidget->repaint();
	_sleep(1000);
}


//strartShowTB 开始演示-工具栏:slot
void LECP::startShowSlot()
{
	isStart = true;//演示结束时设为false

	int kernalNum = mesh->sortedVector.size();
	//dcel
	polarAngleSortDCELSlot();

	vector<Vertex *> longest_convex_chain;
	//mode 选择
	switch (currMode)
	{
	case finalRes:

		break;

	case allPoints:
		//循环处理每个点
		longest_convex_chain.clear();
		for (int kernal_index = 0; kernal_index < kernalNum; kernal_index++) {
			trans2Poly(kernal_index);
			if (poly2show->convex_chain_.size() > longest_convex_chain.size()) {
				longest_convex_chain = poly2show->convex_chain_;
			}
		}
		qDebug() << "longest_convex_chain length:" << longest_convex_chain.size();
		_sleep(1000);
		poly2show->clear();
		break;

	case singlePoint:
		poly2show->clear();
		int kernalSelected = pointSpinBox->value();//TODO 需要改
		trans2Poly(kernalSelected);

		break;
	}
	//all points
	//for (int kernal_index = 0;kernal_index<)


	//certain point



	//paintWidget->allQPoints2Draw
	if (showSort){}
	else{}

	if (showVG){}
	else{}

	if (showChain){}
	else{}

}

void LECP::resetShowSlot()
{
	//poly2show->getPaintWidget()->clearMyQPandMyQL();
	poly2show->clear();
}

//showContentTB 演示内容-工具栏:slot
void LECP::onSortSelected(int flag)
{
	switch (flag)
	{
	case 0:
		showSort = false;
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
void  LECP::onDCELSelected(int flag){}

//qTB vg-工具栏:slot
void  LECP::onQueueSelected(int flag){}

//lTB chain-工具栏:slot
void  LECP::onLSelected(int flag){}

//showControlTB 速度控制-工具栏:slot
void LECP::changeSpeedSlot(int newSpeed)
{
	speedSpinBox->setValue(newSpeed);
	speedSlider->setValue(newSpeed);
	showspeed = newSpeed;
	if (poly2show != NULL)
	{
		poly2show->setSleepTime(showSpeedMax - showspeed);
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

vector<LECP_Point*>   LECP::preprocessingPolarAngleSort(){
	mesh = new Mesh();

	//首先将输入的所有点按照从左到右的顺序排列
	vector<LECP_Point*> points = paintWidget->points;
	sort(points.begin(), points.end(), comparePoint);

	return points;
}

//polar angle sort: naive method
void LECP::polarAngleSortSlot() {
	time_t start = clock();

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

	QString msg = "Naive methon for polar angle sort:"+QString::number(runTime)+"ms"+","+QString::number(points.size())+" points";
	QMessageBox box;
	box.about(this, "running time", msg);
	box.show();
}

//DCEL algorithm for polar angle sort result
void LECP::polarAngleSortDCELSlot() {
	time_t start = clock();

	vector<LECP_Point*> points = preprocessingPolarAngleSort();
	for (long long i = points.size()-1; i>= 0; i--){
		LECP_Point *point = points[i];
		vector<pair<LECP_Point*, LECP_Point*>> lecp_points = mesh->AddLine(point);

		//将交点加上当前点存入mesh的sortedPoint中，并处理横坐标相同的点的情况
		mesh->addCurrentAngleSortedResultToVector(point, lecp_points, points);
	}

	mesh->postCalcPolarAngle();

	time_t end = clock();
	double runTime = double(end - start) * 1000 / CLOCKS_PER_SEC;

	QString msg = "DCEL polar angle sort:" + QString::number(runTime) + "ms" + "," + QString::number(points.size()) + " points";
	QMessageBox box;
	box.about(this, "running time", msg);
	box.show();
}

void LECP::showVisibilityGraphSlot()
{
	//QMessageBox::warning(this, tr("to show"), tr("show animation of VG!"));
	vector<vector<Vertex*>> visibility_graphs = lecp_doc->getVisibilityGraphs();

	for (int i = 0; i < visibility_graphs.size(); i++){
		qDebug() << "Visibility Graph " << i << ":";
		vector<Vertex*> visibility_graph = visibility_graphs[i];

		vector<Vertex*>::iterator it = visibility_graph.begin();
		for (; it != visibility_graph.end(); ++it) {
			qDebug() << "Vertex with index " << (*it)->index() << ":";
			vector<HalfEdge*> incoming_edges = (*it)->incoming_edges_;
			vector<HalfEdge*>::iterator it_e = incoming_edges.begin();
			for (; it_e != incoming_edges.end(); ++it_e) {
				qDebug() << (*it_e)->origin()->index() << "->" << (*it_e)->target()->index();
			}
		}
		break; // TODO: delete this line
	}
}

void LECP::showConvexChainSlot() {

}

//DCEL 动画
void LECP::DCELAnimationSlot(){
	vector<LECP_Point*> points = preprocessingPolarAngleSort();

	for (long long i = points.size() - 1; i >= 0; i--){
		LECP_Point *point = points[i];

		MyQPoint  *qPoint = paintWidget->changeLECP_PointToMyQPoint(point);

		vector<pair<LECP_Point*, LECP_Point*>> lecp_points = mesh->AddLine(point);

		//将交点加上当前点存入mesh的sortedPoint中，并处理横坐标相同的点的情况
		mesh->addCurrentAngleSortedResultToVector(point,lecp_points,points);

		paintWidget->animationPoint(qPoint, lecp_points);
		_sleep(3 * 1000);
		qPoint->setColor(Qt::red);
		paintWidget->update();
	}

	mesh->postCalcPolarAngle();
}

void LECP::clearDCELAnimationSlot(){
	paintWidget->lines.clear();
}

void LECP::resetSlot(){
	paintWidget->init();
	mesh->clear();
	mesh = new Mesh();
}


////////////////////////////////////////////////////////////////////////////

Polygon* LECP::trans2Poly(int kernal_index)
{
	if (kernal_index < 0)
		qDebug() << "kernal index should >=0 in Fun trans2Poly(int kernal_index)";
	//int pointsNum = mesh->sortedVector.size();
	else{
		int pointsNum = 1;
		//循环处理每个点
		/*for (int points_index = 0; points_index < pointsNum; points_index++)
		{*/
		//int points_index = 3;
		//temp 存储用来初始化polygon的vertor<vertex>
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
			temp_myqpoint.setQ(temp_vertices[i]->Q_);
			temp_myqpoint.setShowQ(true);
			poly2show->getPaintWidget()->allQPoints2Draw.push_back(temp_myqpoint);
			poly2show->getPaintWidget()->repaint();
			_sleep(showspeed * 50);

			MyQline edge_i(QLine(poly2show->vertices()->at(i - 1)->point().first, poly2show->vertices()->at(i - 1)->point().second*-1, poly2show->vertices()->at(i)->point().first, poly2show->vertices()->at(i)->point().second*-1));
			edge_i.setDotStyle(true);
			poly2show->getPaintWidget()->allQLines2Draw.push_back(edge_i);
			poly2show->getPaintWidget()->repaint();
			//this->paint_widget_->update();
			_sleep(showspeed * 100);
		}
		MyQline edge_i(QLine(poly2show->vertices()->at(vertexNum - 1)->point().first, poly2show->vertices()->at(vertexNum - 1)->point().second*-1, poly2show->vertices()->at(0)->point().first, poly2show->vertices()->at(0)->point().second*-1));
		edge_i.setDotStyle(true);
		poly2show->getPaintWidget()->allQLines2Draw.push_back(edge_i);
		poly2show->getPaintWidget()->repaint();
		//animation_kernal & starpolygon end//

		//polygon的返回值 不应该直接修改polygon的vertex吗
		temp_vertices = poly2show->getVisibilityGraph();

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
		poly2show->getPaintWidget()->repaint();
		//animation_做chain之前把点和半边的状态更新一下 end//

		temp_vertices = poly2show->getConvexChain();
		temp_vertices.clear(); // why?
		/*}*/
	}
	return poly2show;
}
