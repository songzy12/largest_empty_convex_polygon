#include "mesh.h"
#include <cstdio>
#include <list>
#include <util.h>
#include <qDebug.h>
using namespace std;

#define  INFINITY  999999999999
#define  DELTA 0.000000000000001

Mesh::Mesh() {
	half_edges_ = list<HalfEdge*>();
	vertices_ = list<Vertex*>();

	init();//DCEL初始化
}

Mesh::~Mesh() {
	clear();
}
void Mesh ::clear(){
	for (HalfEdge *e : half_edges_)
		delete e;
	half_edges_.clear();
	for (Vertex *v : vertices_)
		delete v;
	vertices_.clear();
}

/*simple version: add new vertex at the end of the vertex list*/
void Mesh::AddVertex(Vertex *v) {
	vertices_.push_back(v);
}

void Mesh::ConnectVertices(Vertex *v1, Vertex *v2) {

}

//屏幕上增加一个点，对应的对偶图中增加一条线
vector<pair<LECP_Point*, LECP_Point*>>  Mesh::AddLine(LECP_Point *point){
	//The first is intersection,and the second is corresponding original user input point.
	vector<pair<LECP_Point*, LECP_Point*>> return_intersections;

	list<LECP_Point*> sortedAngle;// kernel point's sorted result.
	sortedAngle.push_back(point);
	
	double a = point->x;
	double b = point->y;

	qDebug() << "AddLine:" << a << b;

	Vertex vRet;

	//找到新插入的直线和bounding box的哪个线段相交
	HalfEdge *firstIntersect = getIntersectBundingBox(a, b, vRet);

	//找到交点，并且更新boudingBox
	Vertex* v = new Vertex();
	v->set_point(vRet.point());

	qDebug() << "vRet: " << vRet.point().first << vRet.point().second;
	
	HalfEdge* newHalf = new HalfEdge();// belong to bounding box
	HalfEdge* poH = new HalfEdge();
	HalfEdge* neH = new HalfEdge();

	// for polar angle sort
	LECP_Point *tmpPoint = new  LECP_Point();
	tmpPoint->x = point->x;
	tmpPoint->y = point->y;
	poH->lecp_point = tmpPoint;//新插入的边
	neH->lecp_point = tmpPoint;//新插入的边

	newHalf->set_next(firstIntersect->next());
	newHalf->set_origin(v);
	newHalf->set_prev(neH);

	firstIntersect->next()->set_prev(newHalf);//2017-05-18添加

	poH->set_origin(v);
	poH->set_prev(firstIntersect);
	poH->set_twin(neH);

	neH->set_next(newHalf);
	neH->set_twin(poH);

	firstIntersect->set_next(poH);

	v->set_half_edge(newHalf);

	vertices_.push_back(v);

	// end intersection with bouding box

	//计算接下来直线和平面上已有直线的一个又一个的交点，知道最后的交点落在bounding box上结束

	Vertex* newIntersection = new Vertex();
	HalfEdge* intersectHalfEdgeLeft;//原来的
	HalfEdge* intersectHalfEdgeRight = new HalfEdge();//新增的

	half_edges_.push_back(intersectHalfEdgeRight);

	intersectHalfEdgeLeft = getIntersection(a, b, *newHalf, *newIntersection, *intersectHalfEdgeRight);//返回直线和面中有交点的半边和交点坐标

	// for polar angle sort 
	// TODO: check whether intersectHalfEdgeLeft->lecp_point is set?
	intersectHalfEdgeRight->lecp_point = intersectHalfEdgeLeft->lecp_point;

	//后加
	intersectHalfEdgeLeft->next()->set_prev(intersectHalfEdgeRight);

	newIntersection->set_half_edge(neH);//新产生的Vertex的half_edge设置为逆着插入直线。随意设置

	poH->set_next(intersectHalfEdgeRight);
	neH->set_prev(intersectHalfEdgeLeft);
	neH->set_origin(newIntersection);

	boundingBox.push_back(newHalf);
	half_edges_.push_back(newHalf);
	half_edges_.push_back(poH);
	half_edges_.push_back(neH);

	intersectHalfEdgeLeft->set_next(neH);
	intersectHalfEdgeRight->set_prev(poH);

	//判断当前的交点是否在bounding box上
	bool onBB = onBoundingBox(newIntersection);

	while (!onBB){ //死循环
		//---------------start add new pair--------------------------------------------------------
		// add a new intersection vertex to the return vector.
		LECP_Point* first = new LECP_Point();
		first->setX(newIntersection->point().first);
		first->setY(newIntersection->point().second);

		LECP_Point* second = intersectHalfEdgeRight->lecp_point;

		qDebug() << "first" << newIntersection->point().first << newIntersection->point().first;
		qDebug() << "second:" << (intersectHalfEdgeRight->lecp_point)->x << (intersectHalfEdgeRight->lecp_point)->y;

		pair<LECP_Point*, LECP_Point*> intersectionPair;
		intersectionPair.first = first;
		intersectionPair.second = second;

		return_intersections.push_back(intersectionPair);
		//-----------end add new pair--------------------------------------------------



		sortedAngle.push_back(intersectHalfEdgeLeft->lecp_point);


		HalfEdge* newPoH = new HalfEdge();
		HalfEdge* newNeH = new HalfEdge();

		//处理中间的交点
		//poH和neH存储返回值
		//newIntersection, intersectHalfEdgeLeft, intersectHalfEdgeRight共线 Yes
		dealWithNormalIntersection(newIntersection, intersectHalfEdgeLeft, intersectHalfEdgeRight, newPoH, newNeH);
		newHalf = intersectHalfEdgeLeft->twin();

		// for polar angle sort
		newHalf->lecp_point = intersectHalfEdgeLeft->lecp_point;
		newPoH->lecp_point = tmpPoint;// a new half edge which belongs to the added line 
		newNeH->lecp_point = tmpPoint;// a new half edge which belongs to the added line 

		//遗漏
		newHalf->next()->set_prev(newHalf);


		half_edges_.push_back(newHalf);
		half_edges_.push_back(newPoH);
		half_edges_.push_back(newNeH);


		//返回直线和面中有交点的半边和交点坐标
		//newIntersection，intersectHalfEdgeRight为新的
		//此步newHalf已经改变，之后不再用
		Vertex tmpV;
		HalfEdge *newRight = new HalfEdge();
		// TODO: here is where everything begins
		intersectHalfEdgeLeft = getIntersection(a, b, *newHalf, tmpV, *newRight);

		// for polar angle sort
		// TODO: newRight->lecp_point may not be set
		newRight->lecp_point = intersectHalfEdgeLeft->lecp_point;

		Vertex *intersection = new Vertex();
		intersection->set_point(tmpV.point());

		//half_edges_.push_back(intersectHalfEdgeLeft);
		half_edges_.push_back(newRight);

		intersection->set_half_edge(newNeH);//新产生的Vertex的half_edge设置为逆着插入直线。随意设置

		newPoH->set_next(newRight);
		newNeH->set_prev(intersectHalfEdgeLeft);
		newNeH->set_origin(intersection);

		intersectHalfEdgeLeft->set_next(newNeH);
		newRight->set_prev(newPoH);

		//判断当前的交点是否在bounding box上
		onBB = onBoundingBox(intersection);

		//更新变量
		intersectHalfEdgeRight = newRight;
		newIntersection = intersection;
	}

	//最后一个交点
	boundingBox.push_back(intersectHalfEdgeRight);

	// 交点的顺序可能正好相反，和新插入的直线与哪个bounding box首先相交有关（每条新插入的直线都和两个bounding box相交）

	postAjustIntersections(sortedAngle);// 2017-05-24添加
	postAjustIntersections(return_intersections);// 2017-05-24添加

	//save current kernel's polar angle sorted result
	sortedPoint.push_back(sortedAngle);

	return return_intersections;
}

// 2017-05-24添加
void Mesh::postAjustIntersections(list<LECP_Point*>  &return_intersections){
	if (return_intersections.size() <= 2)
		return;

	vector<LECP_Point*> tmpVector{ return_intersections.begin(), return_intersections.end() };
	
	LECP_Point* p1 = tmpVector[1];
	LECP_Point* p2 = tmpVector[2];
	if (p1->x > p2->x){
		reverse(return_intersections.begin(), return_intersections.end());
	}
	else if (p1->x == p1->x && p1->y > p2->y){
		reverse(++return_intersections.begin(), return_intersections.end());
	}
}

// 2017-05-24添加
void Mesh::postAjustIntersections(vector<pair<LECP_Point*, LECP_Point*>>  &return_intersections){
	if (return_intersections.size() < 2)
		return;

	LECP_Point* p1 = return_intersections[0].first;
	LECP_Point* p2 = return_intersections[1].first;
	if (p1->x > p2->x){
		reverse(return_intersections.begin(), return_intersections.end());
	}
	else if (p1->x == p1->x && p1->y > p2->y){
		reverse(++return_intersections.begin(), return_intersections.end());
	}
}

//最外围的墙，no twins,翻不出去
void Mesh::init(){
	//init four vertex, which are the four window points. 

	double half_x = MAX_X;
	double half_y = MAX_Y;

	Vertex *v1 = new Vertex();
	pair<double, double> p1;
	p1.first = -half_x;
	p1.second = half_y;
	v1->set_point(p1);

	Vertex *v2 = new Vertex();
	pair<double, double> p2;
	p2.first = half_x;
	p2.second = half_y;
	v2->set_point(p2);

	Vertex *v3 = new Vertex();
	pair<double, double> p3;
	p3.first = half_x;
	p3.second = -half_y;
	v3->set_point(p3);

	Vertex *v4 = new Vertex();
	pair<double, double> p4;
	p4.first = -half_x;
	p4.second = -half_y;
	v4->set_point(p4);

	// four half_edge
	HalfEdge *h1 = new HalfEdge();
	h1->set_origin(v1);

	HalfEdge *h2 = new HalfEdge();
	h2->set_origin(v2);

	HalfEdge *h3 = new HalfEdge();
	h3->set_origin(v3);

	HalfEdge *h4 = new HalfEdge();
	h4->set_origin(v4);

	// set the half_edges of each vertex
	v1->set_half_edge(h1);
	v2->set_half_edge(h2);
	v3->set_half_edge(h3);
	v4->set_half_edge(h4);

	//relation between the four half edges
	h1->set_next(h2);
	h1->set_prev(h4);

	h2->set_next(h3);
	h2->set_prev(h1);

	h3->set_next(h4);
	h3->set_prev(h2);

	h4->set_next(h1);
	h4->set_prev(h3);

	vertices_.push_back(v1);
	vertices_.push_back(v2);
	vertices_.push_back(v3);
	vertices_.push_back(v4);

	half_edges_.push_back(h1);
	half_edges_.push_back(h2);
	half_edges_.push_back(h3);
	half_edges_.push_back(h4);

	boundingBox.push_back(h1);
	boundingBox.push_back(h2);
	boundingBox.push_back(h3);
	boundingBox.push_back(h4);
}

HalfEdge*  Mesh::getIntersectHalfEdge(double a, double b){
	list<HalfEdge*>::iterator it = half_edges_.begin();

	while (it != half_edges_.end()){
		HalfEdge* tmp = *it++;

		//判断半边与直线是否有交点
		Vertex* intersect = intersectWithBoundingBox(tmp,a,b);
		if (intersect!=NULL){
			return tmp;
		}
	}

	return NULL;
}

//判断直线y=ax-b与半边tmp是否有交点,如果有，则返回交点，否则为NULL
Vertex*  Mesh::intersectWithBoundingBox(HalfEdge* tmp, double a, double b){
	double half_x = MAX_X;
	double half_y = MAX_Y;

	//判断当前half_edge所在的boudingBox的边
	double x1 = tmp->origin()->point().first;
	double y1 = tmp->origin()->point().second;

	double x2 = tmp->next()->origin()->point().first;
	double y2 = tmp->next()->origin()->point().second;

	Vertex* re = new Vertex();


	//4种情况
	if (x1 == x2 && x1 == -half_x){//左侧边界 线段x=-half_x

		double tmpY = a* x1 - b;

		if ((tmpY >= y1 && tmpY <= y2) || (tmpY <= y1 && tmpY >= y2))
		{
			pair<double, double> p;
			p.first = -half_x;
			p.second = a*x1 - b;
			re->set_point(p);


			return re;
		}

	}
	else if (x1 == x2 && x1 == half_x){ // x=half_x
		double y = a*x1 - b;
		if ((y >= y1 && y <= y2) || (y <= y1 && y >= y2))
		{
			pair<double, double> p;
			p.first = x1;
			p.second = y;
			re->set_point(p);

			return re;
		}

	}
	else if (y1 == y2 && y1 == -half_y){// y = -half_y
		if (a != 0){
			double x = (b - half_y) / a;
			if ((x >= x1 && x <= x2) || (x <= x1 && x >= x2))
			{
				pair<double, double> p;
				p.first = x;
				p.second = -half_y;
				re->set_point(p);

				return re;
			}
		}
	}
	else if (y1 == y2 && y1 == half_y) // y=maxHeight
	{
		if (a != 0){
			double x = (b + y1) / a;
			if ((x >= x1 && x <= x2) || (x <= x1 && x >= x2))
			{
				pair<double, double> p;
				p.first = x;
				p.second = y1;
				re->set_point(p);


				return re;
			}
		}
	}

	return NULL;
}

//判断half_edge与直线y=ax-b是否有交点，if intersect,return the Vertex,else return null
// half_edge没有next
Vertex* intersaction(HalfEdge *half_edge, double a, double b){
	//线段的起点和终点
	Vertex* start = half_edge->origin();
	// TODO: how can half_edge->next()->origin() not set?
	Vertex* end = half_edge->next()->origin();

	double x1 = start->point().first;
	double y1 = start->point().second;
	double x2 = end->point().first;
	double y2 = end->point().second;

	//判断是否平行
	double k1;
	if ((end->point().first - start->point().first) == 0){ //垂直于横坐标轴情况，斜率设置为正无穷，用INFINITY代替
		k1 = INFINITY;
	}
	else{
		k1 = (end->point().second - start->point().second) / (end->point().first - start->point().first);
	}
	double k2 = a;
	if (abs(k1 - k2) <= DELTA)//斜率相同
		return NULL;

	double resultX;
	if (k1 != INFINITY){
		resultX = (b + y1 - k1*x1) / (a - k1);
	}
	else{
		resultX = x1;
	}

	double resultY;
	if (k1 == 0){//平行坐标轴
		resultY = y1;
	}
	else{
		resultY = a*resultX - b;
	}

	Vertex* v = new Vertex();
	pair<double, double> p;
	p.first = resultX;
	p.second = resultY;
	v->set_point(p);

	if (k1 == INFINITY){
		if ((resultY >= y1 && resultY <= y2) || (resultY <= y1 && resultY >= y2))

			return v;
		else
			return NULL;
	}

	if (abs(resultY)> MAX_Y || abs(resultX) >MAX_X){ //交点坐标大于阈值，则认为两条直线平行
		return NULL;
	}

	if ((resultX >= x1 && resultX <= x2) || (resultX <= x1 && resultX >= x2))
		return v;


	return NULL;
}

//newIntersection,intersectHalfEdge,intersectHalfEdgeRight作为返回结果
HalfEdge* Mesh::getIntersection(double a, double b, HalfEdge newHalf, Vertex &newIntersection, HalfEdge &intersectHalfEdgeRight){
	//沿着新产生的half_edge找到当前face中与直线y=ax-b有交点的half_edge
	HalfEdge *newInectHalfEdge = newHalf.next();

	Vertex* inter = intersaction(newInectHalfEdge, a, b);

	while (inter == NULL){
		newInectHalfEdge = newInectHalfEdge->next();
		// TODO: how can newInectHalfEdge->next() not set?
		inter = intersaction(newInectHalfEdge, a, b);//
	}

	newIntersection = *inter;

	intersectHalfEdgeRight.set_next(newInectHalfEdge->next());

	Vertex* tmp = new Vertex();
	tmp->set_point(newIntersection.point());

	intersectHalfEdgeRight.set_origin(tmp);//此处有问题
	intersectHalfEdgeRight.set_twin(newInectHalfEdge->twin());

	intersectHalfEdgeRight.next()->set_prev(&intersectHalfEdgeRight);



	return newInectHalfEdge;
}

bool Mesh::onBoundingBox(Vertex* newIntersection){
	double half_x = MAX_X;
	double half_y = MAX_Y;

	if (newIntersection->point().first == -half_x || newIntersection->point().first == half_x ||
		newIntersection->point().second == -half_y || newIntersection->point().second == half_y)
		return true;
	return false;
}
// store the intersection point of line: ax-b with bounding box to vertex, then return the intersected bounding edge
HalfEdge*  Mesh::getIntersectBundingBox(double a, double b, Vertex &vertex){
	list<HalfEdge*>::iterator it = boundingBox.begin();
	HalfEdge *firstHalfEdge = new HalfEdge(); // TODO: code refactor: do not new a HalfEdge here
	while (it != boundingBox.end()){
		firstHalfEdge = *it++;

		//判断半边与直线是否有交点
		Vertex *re = intersectWithBoundingBox(firstHalfEdge, a, b);

		if (re != NULL){
			vertex = *re;

			return firstHalfEdge;
		}
	}

	return NULL;
}

//处理中间的交点
//返回newPoH和newNeH
void Mesh::dealWithNormalIntersection(Vertex* newIntersection, HalfEdge* intersectHalfEdgeLeft, HalfEdge* intersectHalfEdgeRight, HalfEdge* newPoH, HalfEdge* newNeH){

	//产生两条新的HalfEdge
	HalfEdge *alHL = new HalfEdge();
	HalfEdge *alHR = intersectHalfEdgeRight->twin();

	newPoH->set_origin(newIntersection);
	newPoH->set_twin(newNeH);
	newPoH->set_prev(alHR);

	newNeH->set_next(alHL);
	newNeH->set_twin(newPoH);

	alHL->set_origin(newIntersection);
	alHL->set_prev(newNeH);
	if (alHR != NULL){
		alHL->set_next(alHR->next());//此处有bug
	}

	alHL->set_twin(intersectHalfEdgeLeft);

	intersectHalfEdgeLeft->set_twin(alHL);


	alHR->set_next(newPoH);
	alHR->set_origin(intersectHalfEdgeRight->next()->origin());
	alHR->set_twin(intersectHalfEdgeRight);
	//newPoH->set_next(alHR->prev());

}

void Mesh::postCalcPolarAngle(){
	for (long long i = 0; i < sortedPoint.size(); i++){
		vector<LECP_Point> tmpList;

		list<LECP_Point*> tmpPoints = sortedPoint[i];
		list<LECP_Point*>::iterator it = tmpPoints.begin();
		LECP_Point *pole = *it++;//标杆点

		tmpList.push_back(*pole);

		while (it != tmpPoints.end()){//对其后的每个点进行处理
			LECP_Point* tmpPoint = *it++;
			tmpList.push_back(*tmpPoint);
		}

		//LECP_Point to Vertex*
		list<Vertex*> polarVextex = changeLECO_PointToVertex(tmpList);// no index
		sortedVector.push_back(polarVextex);
	}

	reverse(sortedVector.begin(), sortedVector.end());//reverse kernel
}