#ifndef POLYGON_H
#define POLYGON_H

#include "vertex.h"

class PaintWidget;
class Polygon {
public:
	Polygon();
	Polygon(PaintWidget* paint_widget);
	~Polygon();

		void clear();
		vector<Vertex *> vertices() { return vertices_; }
		void setVertices(vector<Vertex*>);
		void setPaintWidget(PaintWidget* paintWidget);
		PaintWidget* getPaintWidget();
		vector<Vertex*> getStarPolygon();
		/*create visibility graph
		starPoly:	star-shaped Polygon with points ordered by angle*/

		vector<Vertex*> getVisibilityGraph(bool showVG, bool showQ , int currMode);
		void proceedNeighborPoints(Vertex* i, Vertex* j, int index_i, int index_j, bool showVG, bool showQ,  int currMode);
		vector<Vertex*> getConvexChain(bool showChain, bool showL, int currMode);
		HalfEdge* ConvexChainPoint(Vertex * p, int &len, bool showChain, bool showL,int currMode);
		int sleepTime();
		void setSleepTime(int time);

	vector<Vertex*> convex_chain_;
	Vertex * kernel() { return kernel_; }
private:
	vector<Vertex *> vertices_;	
	Vertex* kernel_; // which is vertices[0]
	bool comparePolar(Vertex* p, Vertex* q);

	PaintWidget* paint_widget_;
	int sleepTime_;//0.1s
};
int delta(int data1, int data2,int delta);
#endif
