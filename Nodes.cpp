#include "Nodes.h"

using namespace std;
using namespace ci;
using namespace ci::app;


Nodes::Nodes() {

	}

void Nodes::draw() {
	auto i = edges(mNodeGraph);
	for (auto it = i.first; it != i.second; it++) {
		gl::drawLine(mNodeGraph[source(*it, mNodeGraph)].pNode->pos, mNodeGraph[target(*it, mNodeGraph)].pNode->pos);
		}

	pair<nodeIterator, nodeIterator> p = vertices(mNodeGraph);

	for (auto it = p.first; it != p.second; it++) {
		gl::color(mNodeGraph[*it].pNode->color);
		gl::drawSolidCircle(mNodeGraph[*it].pNode->pos, 10);
		gl::drawStringCentered(mNodeGraph[*it].pNode->name, mNodeGraph[*it].pNode->pos, Color("red"));

		}
	}

void Nodes::addNode(const Vec2f &position, std::string nodeName) {

	
	PointNode *w = new PointNode(position, nodeName, Color(1,1,0));

	nodeVertex v = add_vertex(mNodeGraph);
	mNodeGraph[v].pNode = w;
	//mVertices.push_back(v);
	mNodes.push_back(w);

	cout << mNodeGraph.m_vertices.back().m_property.pNode->name << endl;
	cout << "vertices: " << mNodeGraph.m_vertices.size() << endl;
	}

void Nodes::printInfos() {

	cout << "\tGraph\n" << "Vertices: " << mNodeGraph.vertex_set().size() << endl;

	pair<nodeIterator, nodeIterator> p = vertices(mNodeGraph);
	for (auto it = p.first; it != p.second; it++) {
		cout << *it << endl;
		if (mNodeGraph[*it].pNode != NULL) {
			cout << mNodeGraph[*it].pNode->name << endl;
			}
		else {
			cout << "SORRY BUDDY.." << endl;
			}
		}
	}
