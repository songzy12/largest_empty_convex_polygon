#include "vertex.h"

class Polygon {
public:
	Polygon();
	Polygon(vector<Vertex*> vertices);
	~Polygon();

	vector<Vertex*> getStarPolygon();
	/*create visibility graph
	starPoly:	star-shaped Polygon with points ordered by angle*/
	vector<Vertex*> getVisibilityGraph();
	vector<Vertex*> getConvexChain();

private:
	vector<Vertex *> vertices_;	
	Vertex* kernel_; // which is vertices[0]
	bool comparePolar(Vertex* p, Vertex* q);
};