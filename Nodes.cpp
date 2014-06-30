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
		gl::drawSolidCircle(mNodeGraph[*it].pNode->pos, 10);
		gl::drawStringCentered(mNodeGraph[*it].pNode->name, mNodeGraph[*it].pNode->pos, Color("red"));
		}
}

void Nodes::addNode(const Vec2f &position, std::string &nodeName) {

	mNodes.emplace_back(position, nodeName);
	mVertices.emplace_back();

	mVertices.back() = add_vertex(mNodeGraph);


}
