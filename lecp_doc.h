#define WIN_WIDTH  1200
#define WIN_HEIGHT 800
#include "polygon.h"
#include "paint.h"

class LECP_Doc{
public:
	LECP_Doc();
	~LECP_Doc(); 
	
	int windowWidth;
	int windowHeight;

	void set_paint_widget(PaintWidget* paint_widget) { paint_widget_ = paint_widget; }

	vector<Vertex*> vertices_;

	vector<Vertex*> sortVerticesOnX();

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