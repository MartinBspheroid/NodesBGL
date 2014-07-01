#include "Nodes.h"
#include "cinder\Rand.h"
#include "cinder\Utilities.h"
#include <math.h>

using namespace std;
using namespace ci;
using namespace ci::app;

Nodes::Nodes() {
	bHitNode = bDraggingConnection = bDraggingNode = false;
	translateOffset = Vec2i::zero();
	nodeCount = 0;
	}

void Nodes::draw() {
	gl::color(Color::black());
	if (bDraggingConnection) {


		gl::drawLine(draggingPos.first, draggingPos.second);
		}

	auto i = edges(mNodeGraph);

	for (auto it = i.first; it != i.second; it++) {
		gl::drawLine(mNodeGraph[source(*it, mNodeGraph)].pNode->pos, mNodeGraph[target(*it, mNodeGraph)].pNode->pos);
		}

	pair<nodeIterator, nodeIterator> p = vertices(mNodeGraph);

	for (auto it = p.first; it != p.second; it++) {
		gl::color(mNodeGraph[*it].pNode->color);
		gl::drawSolidCircle(mNodeGraph[*it].pNode->pos, 10);
		gl::drawStringCentered(mNodeGraph[*it].pNode->name, mNodeGraph[*it].pNode->pos + Vec2f(-30, -30), Color("black"));

		}
	}

void Nodes::addNode(const Vec2f &position, std::string nodeName) {


	PointNode *w = new PointNode(position, nodeName, Color(1, 1, 0));
	nodeVertex v = add_vertex(mNodeGraph);
	mNodeGraph[v].pNode = w;
	mNodeGraph[v].id = nodeCount;
	nodeCount++;

	//mVertices.push_back(v);
	mNodes.push_back(w);
	cout << mNodeGraph.m_vertices.back().m_property.pNode->name << endl;

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

void Nodes::addEdge(const int& input, const int& output) {
	add_edge(input, output, mNodeGraph);
	}

void Nodes::onMouseDown(MouseEvent event) {

	if (bHitNode && event.isLeftDown()) {
		bDraggingConnection = true;
		/*draggingPos.first = event.getPos();
		draggingPos.second = event.getPos();*/

		draggingPos.first = mNodeGraph[connectNodes.first].pNode->pos;
		draggingPos.second = mNodeGraph[connectNodes.first].pNode->pos;

		}
	if (bHitNode && event.isRightDown()) {
		bDraggingNode = true;
		}
	if ((event.isRight() && event.isShiftDown()) || event.isMiddleDown()) {

		translateOffset = event.getPos() - translateOffset;
		}
	if (fabs(tDoubleClick - getElapsedSeconds()) < 0.5) {
		doubleClick(event);
		}
	else {
		tDoubleClick = getElapsedSeconds();
		}

	}

void Nodes::onMouseDragged(MouseEvent event) {
	if (bDraggingConnection && event.isLeftDown()) {
		draggingPos.second = event.getPos();

		}
	if (bDraggingNode && event.isRightDown()) {
		mNodeGraph[selectedNode].pNode->pos = event.getPos();
		}

	if ((event.isRightDown() && event.isShiftDown()) || event.isMiddleDown()) {
		translateOffset = event.getPos() - translateOffset;
		pair<nodeIterator, nodeIterator> p = vertices(mNodeGraph);
		for (auto it = p.first; it != p.second; it++) {

			mNodeGraph[*it].pNode->pos += translateOffset;
			}
		translateOffset = event.getPos();
		}
	}

void Nodes::onMouseUp(MouseEvent event) {
	if (bDraggingConnection && event.isLeft()) {

		pair<nodeIterator, nodeIterator> p = vertices(mNodeGraph);
		int NodeCounter = 0;
		for (auto it = p.first; it != p.second; it++) {
			if (mNodeGraph[*it].pNode->pos.distance(event.getPos()) < 10.0f) {

				connectNodes.second = NodeCounter;

				addEdge(connectNodes.first, connectNodes.second);
				bHitNode = false;

				break;
				}
			else {
				mNodeGraph[*it].pNode->color = Color("teal");
				bHitNode = false;

				NodeCounter++;
				}
			}
		bDraggingConnection = false;
		}
	if (bDraggingNode && event.isRight()) {
		bDraggingNode = false;
		}
	translateOffset = Vec2i::zero();
	}

void Nodes::onMouseMoved(MouseEvent event) {

	int NodeCounter = 0;

	pair<nodeIterator, nodeIterator> p = vertices(mNodeGraph);

	for (auto it = p.first; it != p.second; it++) {
		if (mNodeGraph[*it].pNode->pos.distance(event.getPos()) < 10.0f) {



			bHitNode = true;

			mNodeGraph[*it].pNode->color = Color("yellow");
			connectNodes.first = selectedNode = NodeCounter;
			break;
			}
		else {
			mNodeGraph[*it].pNode->color = Color("teal");
			bHitNode = false;
			NodeCounter++;
			}

		}
	}

void Nodes::init() {
	//	generateNew(10);

	ci::app::WindowRef window = cinder::app::getWindow();

	mMouseBeganCallBack = window->getSignalMouseDown().connect(std::bind(&Nodes::onMouseDown, this, std::placeholders::_1));
	mMouseDragCallBack = window->getSignalMouseDrag().connect(std::bind(&Nodes::onMouseDragged, this, std::placeholders::_1));
	mMouseEndCallBack = window->getSignalMouseUp().connect(std::bind(&Nodes::onMouseUp, this, std::placeholders::_1));
	mMouseMovedCallBack = window->getSignalMouseMove().connect(std::bind(&Nodes::onMouseMoved, this, std::placeholders::_1));
	}

void Nodes::generateNew(int number = 10) {

	for (size_t i = 0; i < number; i++) {

		addNode(Vec2f(Rand::randFloat(getWindowWidth()), Rand::randFloat(getWindowHeight())), "node #" + toString(i));

		}

	}

void Nodes::doubleClick(ci::app::MouseEvent event) {
	if (event.isLeft()) {
		addNode(event.getPos(), "new node");
		}

	if (event.isRight() && bHitNode) {

		
		boost::graph_traits<nodeGraph>::vertex_iterator vi, vi_end, next;

		int NodeCounter = 0;
		tie(vi, vi_end) = vertices(mNodeGraph);
		for (next = vi; vi != vi_end; vi = next) {
			++next;

			if (NodeCounter == selectedNode /*mNodeGraph[*vi].id == selectedNode*/) {
				remove_vertex(*vi, mNodeGraph);
				nodeCount--;
				bHitNode = false;
				break;
				}
			NodeCounter++;
			}
		}
	}
