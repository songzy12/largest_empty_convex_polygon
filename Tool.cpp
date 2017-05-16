#include<Tool.h>
#include<DataStruct.h>
#include<algorithm>
#include<iostream>
using namespace std;

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

list<Vertex> changeLECO_PointToVertex(list<LECP_Point> points){
	list<Vertex> re;

	list<LECP_Point>::iterator it = points.begin();
	while (it != points.end()){
		LECP_Point point = *it++;
		Vertex *v = new Vertex();
		pair<double, double> p;
		p.first = point.x;
		p.second = point.y;
		v->set_point(p);
		re.push_back(*v);
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