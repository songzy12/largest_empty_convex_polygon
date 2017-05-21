#include<Tool.h>
#include<DataStruct.h>
#include<algorithm>
#include<iostream>
#include<half_edge.h>
using namespace std;

#define  INFINITY  999999999999
#define  DELTA 0.000000000000001

//按照横坐标从左向右排列
bool comparePoint(LECP_Point a, LECP_Point b){
	if (a.x < b.x)
		return true;
	else if (a.x >b.x)
		return false;
	else{
		return a.y < b.y;
	}
}

void LECP_Doc::removeRepeatPoints(){
	sort(points.begin(), points.end(), comparePoint);
	
	//pos = unique(points.begin, points.end());

	//earse(pos, points.end());
}

/*
list<Vertex*> changeLECO_PointToVertex(list<LECP_Point> points){
	list<Vertex*> re;

	list<LECP_Point>::iterator it = points.begin();
	while (it != points.end()){
		LECP_Point point = *it++;
		Vertex *v = new Vertex();
		pair<double, double> p;
		p.first = point.x;
		p.second = point.y;
		v->set_point(p);
		re.push_back(v);
	}

	return re;
}
*/

list<Vertex*> changeLECO_PointToVertex(vector<LECP_Point> points){
	list<Vertex*> re;

	for (long long i = 0; i < points.size(); i++){
		LECP_Point point = points[i];
		Vertex *v = new Vertex();
		pair<double, double> p;
		p.first = point.x;
		p.second = point.y;
		v->set_point(p);
		v->set_index(i);
		re.push_back(v);
	}

	return re;
}


bool addPoint(LECP_Point point, vector<LECP_Point> points){
	vector<LECP_Point>::iterator it, it1;

	it = find(points.begin(), points.end(), point);

	if (it == points.end())
	{
		//points.push_back(point);

		std::cout << points.size() << " point：" << point.x << "," << point.y << endl;

		return true;
	}
	return false;
}

//判断half_edge与直线y=ax-b是否有交点，if intersect,return the Vertex,else return null
Vertex* intersaction(HalfEdge *half_edge, double a, double b){
	//线段的起点和终点
	Vertex* start = half_edge->origin();
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
		k1= (end->point().second - start->point().second) / (end->point().first - start->point().first);
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

bool LECP_Doc::comparePolar(const LECP_Point p, const LECP_Point q){
	double area = p.x*q.y - p.y*q.x + q.x*s.y - q.y*s.x + s.x*p.y - s.y*p.x;
	if (area < 0)
		return true;
	return false;
}

