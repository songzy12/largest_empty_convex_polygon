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

	mesh = new Mesh();
	poly2show = new Polygon();

	paintWidget = new PaintWidget(width, height);
	this->setCentralWidget(paintWidget);
	
	poly2show->setPaintWidget(paintWidget);

	createToolBar();    //创建工具栏 
	this->addToolBarBreak();

	QObject::connect(ui.polar_angle_sort, SIGNAL(triggered()), this, SLOT(polarAngleSortSlot()));
	QObject::connect(ui.create_VG, SIGNAL(triggered()), this, SLOT(showVisibilityGraphSlot()));
	QObject::connect(ui.saveFile, SIGNAL(triggered()), this, SLOT(saveFileSlot()));
	QObject::connect(ui.openFile, SIGNAL(triggered()), this, SLOT(openFileSlot()));
	QObject::connect(ui.sortedDCEL, SIGNAL(triggered()), this, SLOT(polarAngleSortDCELSlot()));
	QObject::connect(ui.randomPoints, SIGNAL(triggered()), this, SLOT(randomPointsGenerationSlot()));


	//DCEL 动画
	QObject::connect(ui.DCEL_animation, SIGNAL(triggered()), this, SLOT(DCELAnimationSlot()));
	QObject::connect(ui.clearDCELAnimation, SIGNAL(triggered()), this, SLOT(clearDCELAnimationSlot()));
	QObject::connect(ui.reset, SIGNAL(triggered()), this, SLOT(resetSlot()));

	//动画演示
	QObject::connect(ui.sortMenu, SIGNAL(triggered()), this, SLOT(sortMenuSlot()));
	QObject::connect(ui.vgMenu, SIGNAL(triggered()), this, SLOT(vgMenuSlot()));
	QObject::connect(ui.chainMenu, SIGNAL(triggered()), this, SLOT(chainMenuSlot()));

}

LECP::~LECP()
{

}

void LECP::createToolBar()
{
	//工具栏  
	this->ui.showContent->hide();
	this->ui.showControl->hide();

	//演示内容 工具栏
	QLabel* contentLabel = new QLabel(tr("show contents:      "));    
	sortComboBox = new QCheckBox(tr("1.sort     "));
	vgComboBox = new QCheckBox(tr("2.VG     "));
	chainComboBox = new QCheckBox(tr("3.chain     "));
	this->ui.showContent->addWidget(contentLabel);
	this->ui.showContent->addWidget(sortComboBox);
	this->ui.showContent->addWidget(vgComboBox);
	this->ui.showContent->addWidget(chainComboBox);

	connect(sortComboBox, SIGNAL(stateChanged(int)), this, SLOT(onSortSelected(int)));
	connect(vgComboBox, SIGNAL(stateChanged(int)), this, SLOT(onVGSelected(int)));
	connect(chainComboBox, SIGNAL(stateChanged(int)), this, SLOT(onChainSelected(int)));


	//演示控制 工具栏
	QLabel* speedLabel = new QLabel(tr("show speed:     "));

	pSpinBox = new QSpinBox(this);
	pSpinBox->setMinimum(showSpeedMin); 
	pSpinBox->setMaximum(showSpeedMax);  
	pSpinBox->setSingleStep(1);  

	speedSlider=new QSlider(this);
	speedSlider->setOrientation(Qt::Horizontal);
	speedSlider->setMinimum(showSpeedMin);
	speedSlider->setMaximum(showSpeedMax);
	speedSlider->setSingleStep(1);
	speedSlider->setTickInterval(1); 
	speedSlider->setTickPosition(QSlider::TicksAbove);
	speedSlider->setFixedWidth(240);

	QLabel* spaceLabel0 = new QLabel(tr("     "));
	pSelectButton = new QPushButton(this);
	pSelectButton->setText(tr("select point"));
	QLabel* spaceLabel1 = new QLabel(tr("     "));
	startButton = new QPushButton(this);
	startButton->setText(tr("start"));
	QLabel* spaceLabel2 = new QLabel(tr("     "));
	stopButton = new QPushButton(this);
	stopButton->setText(tr("stop"));
	QLabel* spaceLabel3 = new QLabel(tr("     "));
	resetButton = new QPushButton(this);
	resetButton->setText(tr("reset"));

	this->ui.showControl->addWidget(speedLabel);
	this->ui.showControl->addWidget(pSpinBox);
	this->ui.showControl->addWidget(speedSlider);
	this->ui.showControl->addWidget(spaceLabel0);
	this->ui.showControl->addWidget(pSelectButton);
	this->ui.showControl->addWidget(spaceLabel1);
	this->ui.showControl->addWidget(startButton);
	this->ui.showControl->addWidget(spaceLabel2);
	this->ui.showControl->addWidget(stopButton);
	this->ui.showControl->addWidget(spaceLabel3);
	this->ui.showControl->addWidget(resetButton);

	connect(pSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeSpeedSlot(int)));
	connect(speedSlider, SIGNAL(valueChanged(int)), this, SLOT(changeSpeedSlot(int)));

	connect(startButton, SIGNAL(clicked()), this, SLOT(startShowSlot()));
	connect(stopButton, SIGNAL(clicked()), this, SLOT(stopShowSlot()));
	connect(resetButton, SIGNAL(clicked()), this, SLOT(resetShowSlot()));

	//TODO: delete this
	connect(pSelectButton, SIGNAL(clicked()), this, SLOT(showConvexChainSlot()));
}



Vertex* pole;
bool compareVertex(Vertex* p, Vertex* q){
	double px = p->point().first;
	double py = p->point().second;
	double sx = pole->point().first;
	double sy = pole->point().second;
	double qx = q->point().first;
	double qy = q->point().second;


	double area = px*qy - py*qx + qx*sy - qy*sx + sx*py - sy*px;
	if (area < 0)
		return true;
	return false;
}
//极角排序
void LECP::polarAngleSortSlot() {
	time_t start = clock();

	mesh = new Mesh();

	lecp_doc->points = paintWidget->points;
	//首先将输入的所有点按照从左到右的顺序排列
	vector<LECP_Point> points = lecp_doc->points;
	sort(points.begin(), points.end(), comparePoint);
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

	QString msg = QString::number(runTime)+"ms";
	QMessageBox box;
	box.about(this, "running time", msg);
	box.show();
}

void LECP::polarAngleSortDCELSlot() {
	mesh = new Mesh();

	lecp_doc->points = paintWidget->points;
	//首先将输入的所有点按照从左到右的顺序排列
	vector<LECP_Point> points = lecp_doc->points;
	sort(points.begin(), points.end(), comparePoint);

	//from right to left ,get the polar angle sorted list

	for (long long i = points.size()-1; i>= 0; i--){
		LECP_Point *point = &points[i];
		mesh->AddLine(point);
	}

	mesh->postCalcPolarAngle();
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

//DCEL 动画
void LECP::DCELAnimationSlot(){
	lecp_doc->points = paintWidget->points;
	//首先将输入的所有点按照从左到右的顺序排列
	vector<LECP_Point> points = lecp_doc->points;
	sort(points.begin(), points.end(), comparePoint);

	for (long long i = points.size() - 1; i >= 0; i--){
		LECP_Point *point = &points[i];

		MyQPoint  *qPoint = paintWidget->changeLECP_PointToMyQPoint(*point);

		vector<pair<LECP_Point*, LECP_Point*>> lecp_points = mesh->AddLine(point);
		paintWidget->animationPoint(qPoint, lecp_points);
		_sleep(3 * 1000);
		qPoint->setColor(Qt::red);
		paintWidget->update();
	}

}

void LECP::clearDCELAnimationSlot(){
	paintWidget->lines.clear();
}

void LECP::resetSlot(){
	paintWidget->init();
	mesh->clear();
	mesh = new Mesh();
}

//动画演示Menu Slot
void LECP::sortMenuSlot()
{
	this->ui.showContent->hide();
	this->ui.showControl->show();
}
void LECP::vgMenuSlot()
{
	this->ui.showContent->show();
	this->ui.showControl->show();
}
void LECP::chainMenuSlot()
{
	this->ui.showContent->show();
	this->ui.showControl->show();
}

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
}

void LECP::changeSpeedSlot(int newSpeed)
{
	pSpinBox->setValue(newSpeed);
	speedSlider->setValue(newSpeed);
	showspeed = newSpeed;
	if (poly2show != NULL)
	{
		poly2show->setSleepTime(showSpeedMax - showspeed);
	}
}

void LECP::startShowSlot()
{
	isStart = true;//演示结束时设为false

	trans2Poly(0);

	//paintWidget->allQPoints2Draw
	if (showSort){}
	else{}

	if (showVG){}
	else{}

	if (showChain){}
	else{}

}


void LECP::stopShowSlot()
{
	
}

void LECP::resetShowSlot()
{
	poly2show->getPaintWidget()->clearMyQPandMyQL();
}
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
		for (int i = 1; i < vertexNum;i++){//转化vertex为MyQPoint
			MyQPoint temp_myqpoint(QPoint(temp_vertices[i]->point().first, temp_vertices[i]->point().second*-1));
			temp_myqpoint.setColor(Qt::blue);
			temp_myqpoint.setIndex(temp_vertices[i]->index());
			poly2show->getPaintWidget()->allQPoints2Draw.push_back(temp_myqpoint);
			poly2show->getPaintWidget()->repaint();
			_sleep(showspeed * 50);

			MyQline edge_i(QLine(poly2show->vertices()->at(i-1)->point().first, poly2show->vertices()->at(i-1)->point().second*-1, poly2show->vertices()->at(i)->point().first, poly2show->vertices()->at(i)->point().second*-1));
			edge_i.setDotStyle(true);
			poly2show->getPaintWidget()->allQLines2Draw.push_back(edge_i);
			poly2show->getPaintWidget()->repaint();
			//this->paint_widget_->update();
			_sleep(showspeed * 100);
		}
		MyQline edge_i(QLine(poly2show->vertices()->at(vertexNum - 1)->point().first, poly2show->vertices()->at(vertexNum-1)->point().second*-1, poly2show->vertices()->at(0)->point().first, poly2show->vertices()->at(0)->point().second*-1));
		edge_i.setDotStyle(true);
		poly2show->getPaintWidget()->allQLines2Draw.push_back(edge_i);
		poly2show->getPaintWidget()->repaint();
		//animation_kernal & starpolygon end//

//polygon的返回值 不应该直接修改polygon的vertex吗
		temp_vertices = poly2show->getVisibilityGraph();
		
		//animation_做chain之前把点和半边的状态更新一下
		for (int i = 1; i < vertexNum; i++){
			poly2show->getPaintWidget()->allQPoints2Draw.at(i).setColor(Qt::blue);
		}
		int last_index =poly2show->getPaintWidget()->allQLines2Draw.size()-1;
		//poly2show->getPaintWidget()->allQLines2Draw.at(last_index - 1).setColor(Qt::green);
		//poly2show->getPaintWidget()->allQLines2Draw.at(last_index).setColor(Qt::cyan);
		poly2show->getPaintWidget()->allQLines2Draw.at(last_index).setColor(Qt::green);
		int lineNum = poly2show->getPaintWidget()->allQLines2Draw.size();
		for (int i = 0; i < lineNum ; i++)
		{
			poly2show->getPaintWidget()->allQLines2Draw.at(i).setDotStyle(true);
		}
		poly2show->getPaintWidget()->repaint();
		//animation_做chain之前把点和半边的状态更新一下 end//

		temp_vertices = poly2show->getConvexChain();
		temp_vertices.clear();
	/*}*/
	}
	return poly2show;
}

void LECP::randomPointsGenerationSlot(){
	bool isOK;
	QString text = QInputDialog::getText(NULL, "Input points number", "Please input the number of points:", QLineEdit::Normal, "points number", &isOK);

	if (isOK){
		int points_number = text.toInt();

		cout << "random points number:" << points_number << endl;

		vector<LECP_Point> random_points = generateRandomPoints(points_number);
		paintWidget->setPoints( random_points);
	}
}

