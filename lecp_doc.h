#ifndef LECP_DOC_H
#define LECP_DOC_H

#include "polygon.h"
#include "paint.h"

class LECP_Doc{
public:
	LECP_Doc();
	~LECP_Doc(); 
	
	vector<Vertex*> vertices_;
	vector<LECP_Point> points;//all of the points user input Calculated coordinate system

	//vector<LECP_Point> sortVerticesOnX();
	

	vector<vector<Vertex*>> getStarPolygons();
	vector<vector<Vertex*>> getVisibilityGraphs();
	vector<vector<Vertex*>> getConvexChains();

	vector<Polygon*> polygons_;
	vector<vector<Vertex*>> star_polygons_;
	vector<vector<Vertex*>> visibility_graphs_;
	vector<vector<Vertex*>> convex_chains_;

private:
	PaintWidget *paint_widget_;
};

#endif