#ifndef UTIL_H
#define UTIL_H
#include "half_edge.h"
#include "mesh.h"

/*toLeft test
direct line i->j, test point k*/
bool toLeft(Vertex* i, Vertex* j, Vertex* k);
bool toLeft(pair<double, double> i, pair<double, double> j, pair<double, double> k);

/*create visibility graph
starPoly:	star-shaped Polygon with points ordered by angle*/
Mesh* visibility(Mesh* starPoly);

/*process bewteen vertex i&j (counterclockwise order:i->j)
in creating visibility graph*/
void VG_process(Vertex* i, Vertex* j, Mesh* starPoly);
#endif
