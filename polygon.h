#ifndef POLYGON_H
#define POLYGON_H

#include "vertex.h"

class PaintWidget;
class Polygon {
	public:
		Polygon();
		Polygon(vector<Vertex*> vertices);
		Polygon(vector<Vertex*> vertices, PaintWidget* paint_widget);
		~Polygon();

		void clear();
		vector<Vertex *>* vertices();
		void setVertices(vector<Vertex*>);
		void setPaintWidget(PaintWidget* paintWidget);
		PaintWidget* getPaintWidget();
		vector<Vertex*> getStarPolygon();
		/*create visibility graph
		starPoly:	star-shaped Polygon with points ordered by angle*/
		vector<Vertex*> getVisibilityGraph();
		void proceedNeighborPoints(Vertex* i, Vertex* j, int index_i, int index_j);
		vector<Vertex*> getConvexChain();
		HalfEdge* ConvexChainPoint(Vertex * p, int &len);
		////带动画显示的版本
		//vector<Vertex*> getVisibilityGraph_a();
		//void proceedNeighborPoints_a(Vertex* i, Vertex* j, int index_i, int index_j);
		//vector<Vertex*> getConvexChain_a();
		//HalfEdge* ConvexChainPoint_a(Vertex * p, int &len);
		int sleepTime();
		void setSleepTime(int time);

	private:
		vector<Vertex *> vertices_;	
		Vertex* kernel_; // which is vertices[0]
		bool comparePolar(Vertex* p, Vertex* q);

		PaintWidget* paint_widget_;
		int sleepTime_;//0.1s
};
int delta(int data1, int data2,int delta);
#endif