#include "lecp.h"
#include <QtGui/QPen>
#include <QtGui/QMouseEvent>
#include <qmessagebox.h>
#include <qdebug.h>
#include <qfiledialog.h>
#include <iostream>
#include <vertex.h>
#include <util.h>
using namespace std;

LECP::LECP(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	lecp_doc = new LECP_Doc();

	setFixedSize(lecp_doc->windowWidth, lecp_doc->windowHeight);
	
	int width = this->width();
	int height = this->height();

	paintWidget = new PaintWidget(width, height);
	this->setCentralWidget(paintWidget);
	lecp_doc->set_paint_widget(paintWidget);

	QObject::connect(ui.polar_angle_sort, SIGNAL(triggered()), this, SLOT(polarAngleSortSlot()));
	QObject::connect(ui.create_VG, SIGNAL(triggered()), this, SLOT(showVisibilityGraphSlot()));
	QObject::connect(ui.saveFile, SIGNAL(triggered()), this, SLOT(saveFileSlot()));
	QObject::connect(ui.openFile, SIGNAL(triggered()), this, SLOT(openFileSlot()));
}

LECP::~LECP()
{

}

void LECP::resizeEvent(QResizeEvent *event){

}

//极角排序
void LECP::polarAngleSortSlot() {

	//首先将输入的所有点按照从左到右的顺序排列
	vector<Vertex*> vertices = lecp_doc->sortVerticesOnX();
	qDebug() << "Total vertice count:" << vertices.size();
	vector<vector<Vertex*>> star_polygons = lecp_doc->getStarPolygons();

	for (int i = 0; i < star_polygons.size(); ++i) {
		qDebug() << "Star Polygon " << i << ":";
		vector<Vertex*> star_polygon = star_polygons[i];
		vector<Vertex*>::iterator it = star_polygon.begin();
		
		for (; it != star_polygon.end(); ++it) {
			qDebug() << "Vertex" << (*it)->index() << ":" << (*it)->point().first << "," << (*it)->point().second;
		}
		break; // TODO: delete this line
	}
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