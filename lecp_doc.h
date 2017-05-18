#include "polygon.h"

#define WIN_WIDTH  1200
#define WIN_HEIGHT 800

class LECP_Doc{
public:
	LECP_Doc();
	~LECP_Doc(); 
	
	int windowWidth;
	int windowHeight;

	bool addPoint(double x, double y);
	void removeRepeatPoints(); //remove one of the same point to ensure every point in points is unique.

	vector<Vertex*> vertices_; //all of the points user input

	vector<Vertex*> sortVerticesOnX();

	vector<vector<Vertex*>> getStarPolygons();
	vector<vector<Vertex*>> getVisibilityGraphs();
	vector<vector<Vertex*>> getConvexChains();

	vector<Polygon*> polygons_;
	vector<vector<Vertex*>> star_polygons_;
	vector<vector<Vertex*>> visibility_graphs_;
	vector<vector<Vertex*>> convex_chains_;
};