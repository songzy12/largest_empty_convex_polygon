#include <cstdio>
#include <qdebug.h>
#include "vertex.h"
#include "mesh.h"
#include "util.h"

void point_test() {
	Vertex *v = new Vertex();
	v->set_point({ 1, 2 });
	printf("%lf\n", v->point().first);
	return;
}

//only test left or right ; not test point on the line
void toleft_test(){
	Vertex *v1 = new Vertex(); v1->set_point({ 1, 1 });
	Vertex *v2 = new Vertex(); v2->set_point({ 2, 3 });
	Vertex *v3 = new Vertex(); v3->set_point({ 1, 3 });
	Vertex *v4 = new Vertex(); v4->set_point({ 2, 2 });

	bool res1 = toLeft(v1, v2, v3);
	bool res2 = toLeft(v1, v2, v4);

	if (res1 == 1 && res2 == 0)
		qDebug() << "toLeft pass the test";
	else
	{
		qDebug() << "toLeft don't pass the test";
	}
}



void visibility_test()
{
	Mesh* starPoly = new Mesh();
	//vector<Vertex *> points(6,new Vertex());
	//vector<pair<double, double>> points_data = { { 0, 4 }, { 1, 1 }, { 3, 2 }, { 5, 3 }, { 4, 5 }, { 2, 6 } };
	//for (int i = 0; i < 6; i++)
	//{
	//	points.at(i)->set_point(points_data.at(i));
	//}

	//for (int i = 0; i < 6; i++)
	//{
	//	starPoly->AddVertex(points.at(i));
	//}

	Vertex *p = new Vertex(); p->set_point({ 0, 4 });
	Vertex *p1 = new Vertex(); p1->set_point({ 1, 1 });
	Vertex *p2 = new Vertex(); p2->set_point({ 3, 2 });
	Vertex *p3 = new Vertex(); p3->set_point({ 5, 3 });
	Vertex *p4 = new Vertex(); p4->set_point({ 4, 5 });
	Vertex *p5 = new Vertex(); p5->set_point({ 2, 6 });
	starPoly->AddVertex(p);
	starPoly->AddVertex(p1);
	starPoly->AddVertex(p2);
	starPoly->AddVertex(p3);
	starPoly->AddVertex(p4);
	starPoly->AddVertex(p5);

	visibility(starPoly);
	

}

int main() {
    point_test();
	toleft_test();
	visibility_test();
    return 0;
}