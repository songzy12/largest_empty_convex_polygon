#include "lecp.h"
#include <QtGui/QPen>
#include <QtGui/QMouseEvent>
#include <qmessagebox.h>
#include <qdebug.h>
#include <qfiledialog.h>
#include <iostream>
#include <vertex.h>
#include <util.h>
#include "lecp_doc.h"
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

	paintWidget = new PaintWidget(width, height);
	this->setCentralWidget(paintWidget);
	
	QObject::connect(ui.polar_angle_sort, SIGNAL(triggered()), this, SLOT(polarAngleSortSlot()));
	QObject::connect(ui.create_VG, SIGNAL(triggered()), this, SLOT(showVisibilityGraphSlot()));
	QObject::connect(ui.saveFile, SIGNAL(triggered()), this, SLOT(saveFileSlot()));
	QObject::connect(ui.openFile, SIGNAL(triggered()), this, SLOT(openFileSlot()));
	QObject::connect(ui.sortedDCEL, SIGNAL(triggered()), this, SLOT(polarAngleSortDCELSlot()));
}

LECP::~LECP()
{

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
}

void LECP::polarAngleSortDCELSlot(){
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