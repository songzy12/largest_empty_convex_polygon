#include "util.h"
#include "qDebug" //only for output check, can be removed later,

bool toLeft(Vertex* i, Vertex* j, Vertex* k)
{
	return toLeft(i->point(), j->point(), k->point());
}

bool toLeft(pair<double, double> i, pair<double, double> j, pair<double, double> k)
{
	bool isleft = (get<0>(i)*get<1>(j) -get<1>(i)*get<0>(j)
		+get<0>(j)*get<1>(k) -get<1>(j)*get<0>(k)
		+get<0>(k)*get<1>(i) -get<1>(k)*get<0>(i)) > 0;
	return isleft;
}

void visibility(Mesh* starPoly)
{
	starPoly->all_edges()->clear();// clear the vg of the mesh

	for (int index = 0; index < starPoly->sortedVector.size(); index++){


		list<pair<Vertex*, Vertex*>> all_edges_index;
		starPoly->all_edges()->push_back(all_edges_index);

		//list<Vertex>* vertices = &(starPoly->sortedVector.at(index));
		if (!starPoly->sortedVector.at(index).empty()){
			//int N = vertices->size();
			int N = starPoly->sortedVector.at(index).size();
			//clear the queue of every point
			list<Vertex>::iterator itor_vertex = starPoly->sortedVector.at(index).begin();
			while (itor_vertex != starPoly->sortedVector.at(index).end())
			{
				//Vertex v1 = *itor_vertex;
				itor_vertex->queue2store()->clear();
				itor_vertex++;
			}

			//do process for n-2 points
			itor_vertex = starPoly->sortedVector.at(index).begin();
			list<Vertex>::iterator itor_vertex_temp = itor_vertex++;
			for (int i = 1; i <= N - 2; i++)
			{
				itor_vertex_temp = itor_vertex++;
				Vertex* v1 = &(*itor_vertex_temp);
				itor_vertex_temp++;
				Vertex* v2 = &(*itor_vertex_temp);
				VG_process(v1, v2, starPoly, index);
			}
		}
	}
	//return starPoly;
}

void VG_process(Vertex* i, Vertex* j, Mesh* starPoly,int index)
{
	deque<Vertex*>* Qi = i->queue2store();
	deque<Vertex*>* Qj = j->queue2store();
	while ((!Qi->empty()) && toLeft(Qi->front(), i, j)){
		//PROCEED
		VG_process(Qi->front(), j, starPoly,index);
		//DEQUEUE(Qi)
		Qi->pop_front();
	}
	//ADD(ij)
	starPoly->all_edges()->at(index).push_back({ i, j });
	//ENQUEUE(i,Qj)
	Qj->push_back(i);
	return;
}


/*µ¥¸övertex list*/
//Mesh* visibility(Mesh* starPoly)
//{
//	starPoly->all_edges()->clear();// clear the vg of the mesh
//	list<Vertex*> vertices = starPoly->vertices();
//	int N = (starPoly->vertices()).size();
//	
//	//clear the queue of every point
//	list<Vertex*>::iterator itor_vertex = vertices.begin();
//	while (itor_vertex != vertices.end())
//	{
//		Vertex* v1 = *itor_vertex;
//		(*itor_vertex)->queue2store()->clear();
//		itor_vertex++;
//	}
//
//	//do process for n-2 points
//	itor_vertex = vertices.begin();
//	list<Vertex*>::iterator itor_vertex_temp = itor_vertex++;
//	for (int i = 1; i<=N - 2; i++)
//	{
//		itor_vertex_temp = itor_vertex++;
//		Vertex* v1 = *itor_vertex_temp;
//		itor_vertex_temp++;
//		Vertex* v2 = *itor_vertex_temp;
//		VG_process(v1, v2,starPoly);
//	}
//	vertices.clear();
//	return starPoly;
//}
//
//void VG_process(Vertex* i, Vertex* j, Mesh* starPoly)
//{
//	deque<Vertex*>* Qi = i->queue2store();
//	deque<Vertex*>* Qj = j->queue2store();
//	while ((!Qi->empty()) && toLeft(Qi->front(),i,j)){
//	//PROCEED
//		VG_process(Qi->front(), j, starPoly);
//	//DEQUEUE(Qi)
//		Qi->pop_front();
//	}
//	//ADD(ij)
//	starPoly->all_edges()->push_back({ i, j });
//
//	//ENQUEUE(i,Qj)
//		Qj->push_back(i);
//	return;
//}
/* For each vertex in the VG, we have a list of incoming edges
 * Also, the incoming edges have been sorted counterclock wise
 */


bool IsConvexTurn(HalfEdge *i, HalfEdge *o) {
	return toLeft(i->origin(), i->target(), o->target());
}

int ConvexChainPoint(Vertex * p) {
	vector<HalfEdge*> in_edges = p->incoming_edges();
	vector<HalfEdge*> out_edges = p->outgoing_edges();
	qDebug() << "in edge count:"<<in_edges.size() << "," << "out edge count:" << out_edges.size();
	vector<HalfEdge*>::reverse_iterator it_i;
	vector<HalfEdge*>::iterator it_o = out_edges.begin();

	int m = 0;
	for (it_i = in_edges.rbegin(); it_i != in_edges.rend(); it_i++) {
		// we compute the L for incoming edge i.
		qDebug() << "in point:" << (*it_i)->target()->point().first << "," << (*it_i)->target()->point().second;
		if (it_o != out_edges.end()) {
			qDebug() << "out point:" << (*it_o)->target()->point().first << "," << (*it_o)->target()->point().second;
			qDebug() << IsConvexTurn(*it_i, *it_o) << (*it_o)->L() << endl;
		}
		while (it_o != out_edges.end() && IsConvexTurn(*it_i, *it_o)) {
			m = max(m, (*it_o)->L());
			it_o++;
		}
		qDebug() << "set L point:" << (*it_i)->target()->point().first << "," << (*it_i)->target()->point().second<<":"<<m+1;
		(*it_i)->set_L(m + 1);
	}
	return m + 1;
}

int ConvexChainLength(vector<Vertex*> vertices) {
	int max_len = 0;
	for (size_t i = vertices.size() - 1; i > 0; --i) {
		Vertex* p = vertices[i];
		max_len = max(max_len, ConvexChainPoint(p));
		qDebug() << "max_len for point" << p->point().first << "," << p->point().second << ":" << max_len << endl;
	}
	qDebug() << "max_len for all points:" << max_len << endl;
	return max_len;
}