#include "lecp_doc.h"
#include "util.h"
#include "qdebug.h"
#include <algorithm>

LECP_Doc::LECP_Doc() {
	windowWidth = WIN_WIDTH;
	windowHeight = WIN_HEIGHT;
}

LECP_Doc::~LECP_Doc() {

}

vector<Vertex*> LECP_Doc::sortVerticesOnX() {
	vertices_ = paint_widget_->vertices_;
	sort(vertices_.begin(), vertices_.end(), comparePoint);
	return vertices_;
}

vector<vector<Vertex*>> LECP_Doc::getStarPolygons() {
	polygons_.clear();
	star_polygons_.clear();
	vector<Vertex*>::iterator it = vertices_.begin();
	while (it != vertices_.end()) {
		vector<Vertex*> vertices(it, vertices_.end());
		Polygon* polygon = new Polygon(vertices, paint_widget_); // TODO: need to be new vertex
		polygons_.push_back(polygon);
		star_polygons_.push_back(polygon->getStarPolygon());
		it++;
		break; // TODO: delete this line
	}
	return star_polygons_;
}

vector<vector<Vertex*>> LECP_Doc::getVisibilityGraphs() {
	visibility_graphs_.clear();
	qDebug() << "Polygon Count:" << polygons_.size();
	vector<Polygon*>::iterator it = polygons_.begin();
	while (it != polygons_.end()) {
		visibility_graphs_.push_back((*it)->getVisibilityGraph());
		it++;
		break; // TODO: delete this line
	}
	return visibility_graphs_;
}

vector<vector<Vertex*>> LECP_Doc::getConvexChains() {
	convex_chains_.clear();
	vector<Polygon*>::iterator it = polygons_.begin();
	while (it != polygons_.end()) {
		convex_chains_.push_back((*it)->getConvexChain());
		it++; 
		break; // TODO: delete this line
	}
	return convex_chains_;
}