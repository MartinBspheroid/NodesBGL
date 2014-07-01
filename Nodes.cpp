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
		gl::drawLine(mNodeGraph[source(*it, mNodeGraph)].pNode->outPoint, mNodeGraph[target(*it, mNodeGraph)].pNode->inPoint);
		}

	pair<nodeIterator, nodeIterator> p = vertices(mNodeGraph);

	for (auto it = p.first; it != p.second; it++) {
		mNodeGraph[*it].pNode->draw();
		
		}
	}

void Nodes::addNode(const Vec2f &position, std::string nodeName) {


	BaseNode *w = new BaseNode(position, nodeName, Color(1, 1, 0));
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

	if (bHitNode && event.isRight()) {
		bDraggingConnection = true;
		bDraggingNode = false;
		/*draggingPos.first = event.getPos();
		draggingPos.second = event.getPos();*/

		draggingPos.first = mNodeGraph[connectNodes.first].pNode->pos;
		draggingPos.second = mNodeGraph[connectNodes.first].pNode->pos;

		}
	if (bHitNode && event.isLeftDown()) {
		bDraggingNode = true;
		bDraggingConnection = false;
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
	if (bDraggingConnection && event.isRightDown()) {
		draggingPos.second = event.getPos();

		}
	if (bDraggingNode && event.isLeftDown()) {
		mNodeGraph[selectedNode].pNode->move(event.getPos());
		}

	if ((event.isRightDown() && event.isShiftDown()) || event.isMiddleDown()) {
		translateOffset = event.getPos() - translateOffset;
		pair<nodeIterator, nodeIterator> p = vertices(mNodeGraph);
		for (auto it = p.first; it != p.second; it++) {

			mNodeGraph[*it].pNode->translate(translateOffset);
			}
		translateOffset = event.getPos();
		}
	}

void Nodes::onMouseUp(MouseEvent event) {
	if (bDraggingConnection && event.isRight()) {

		pair<nodeIterator, nodeIterator> p = vertices(mNodeGraph);
		int NodeCounter = 0;
		for (auto it = p.first; it != p.second; it++) {
			if (mNodeGraph[*it].pNode->nodeBox.contains(event.getPos())) {

				connectNodes.second = NodeCounter;

				addEdge(connectNodes.first, connectNodes.second);
				bHitNode = false;

				break;
				}
			else {
				mNodeGraph[*it].pNode->color = Color("light gray");
				bHitNode = false;

				NodeCounter++;
				}
			}
		bDraggingConnection = false;
		}
	if (bDraggingNode && event.isLeft()) {
		bDraggingNode = false;
		}
	translateOffset = Vec2i::zero();
	}

void Nodes::onMouseMoved(MouseEvent event) {

	int NodeCounter = 0;

	pair<nodeIterator, nodeIterator> p = vertices(mNodeGraph);

	for (auto it = p.first; it != p.second; it++) {
		if (mNodeGraph[*it].pNode->nodeBox.contains(event.getPos())) {



			bHitNode = true;

			mNodeGraph[*it].pNode->color = Color("orange");
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
