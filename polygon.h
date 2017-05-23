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
		void setVertices(vector<Vertex*>);
		void setPaintWidget(PaintWidget* paintWidget);
		PaintWidget* getPaintWidget();
		vector<Vertex*> getStarPolygon();
		/*create visibility graph
		starPoly:	star-shaped Polygon with points ordered by angle*/
		vector<Vertex*> getVisibilityGraph();
		void proceedNeighborPoints(Vertex* i, Vertex* j, int index_i, int index_j);
		vector<Vertex*> getConvexChain();

	private:
		vector<Vertex *> vertices_;	
		Vertex* kernel_; // which is vertices[0]
		bool comparePolar(Vertex* p, Vertex* q);

		PaintWidget* paint_widget_;
};

#endif