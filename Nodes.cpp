#include "Nodes.h"
#include "cinder\Rand.h"
#include "cinder\Utilities.h"
#include <math.h>
#include "cinder\CinderMath.h"

using namespace std;
using namespace ci;
using namespace ci::app;

Nodes::Nodes() {
	bHitNode = bDraggingConnection = bDraggingNode = false;
	translateOffset = Vec2i::zero();
	nodeCount = 0;
	bDrawTopology = false;
	}

void Nodes::draw() {
	gl::color(Color::black());
	if (bDraggingConnection) {


		gl::drawLine(draggingPos.first, draggingPos.second);
		}

	auto i = edges(mNodeGraph);

	for (auto it = i.first; it != i.second; it++) {


		Vec2f &out = mNodeGraph[source(*it, mNodeGraph)].pNode->outPoint;
		Vec2f &in = mNodeGraph[target(*it, mNodeGraph)].pNode->inPoint;


		vector <Vec2f> points;


		points.emplace_back(out);
		points.emplace_back(lerp(out, Vec2f(in.x, out.y), 0.25f));
		points.emplace_back(lerp(in, Vec2f(out.x, in.y), 0.75f));
		points.emplace_back(in);

		BSpline2f line = BSpline2f(points, 3, false, true);

		
		for (float i = 0.0f; i <= 1.0f; i += 0.05f) {
			gl::drawLine(line.getPosition(i), line.getPosition(i + 0.05));
			}

	/*	for_each(points.begin(), points.end(), [&](Vec2f p) {
			gl::drawSolidCircle(p, 5);
			
			});*/


		
	

	//	gl::drawLine(mNodeGraph[source(*it, mNodeGraph)].pNode->outPoint, mNodeGraph[target(*it, mNodeGraph)].pNode->inPoint);
		}

	pair<nodeIterator, nodeIterator> p = vertices(mNodeGraph);

	for (auto it = p.first; it != p.second; it++) {
		mNodeGraph[*it].pNode->draw();

		}
	if (bDrawTopology) {
		drawTopology();
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


	cout << "\tTopological sort... \n" << endl;


	std::deque<int> topo_order;
	boost::topological_sort(mNodeGraph, std::front_inserter(topo_order));
	for (std::deque<int>::const_iterator i = topo_order.begin(); i != topo_order.end(); ++i) {
		std::cout << mNodes[*i]->name << std::endl;
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

		draggingPos.first = mNodeGraph[connectNodes.first].pNode->outPoint;
		draggingPos.second = mNodeGraph[connectNodes.first].pNode->outPoint;

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
			//			mNodeGraph[*it].pNode->color = Color("orange");
			connectNodes.first = selectedNode = NodeCounter;
			break;
			}
		else {
			mNodeGraph[*it].pNode->color = Color("darkorange");
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

void Nodes::drawTopology() {

	float offset = float(int(getElapsedSeconds() * 1000.0f) % 1000) / 1000.0f;
	std::deque<int> topo_order;
	int topologicalCounter = 0;
	Vec2f from = Vec2f::zero();
	boost::topological_sort(mNodeGraph, std::front_inserter(topo_order));
	gl::color(Color("teal"));
	gl::lineWidth(3);
	for (std::deque<int>::const_iterator i = topo_order.begin(); i != topo_order.end(); ++i) {

		gl::drawStringCentered("#" + toString(topologicalCounter), mNodes[*i]->pos + Vec2f(-40, -30), Color::black());


		if (topologicalCounter != 0) {

			gl::begin(GL_LINES);
			float step = 1.0f / mNodes[*i]->pos.distance(from) * 5.f;
			float start = lerp(step * 2, 0.0f, offset);
			for (float j = start; j <= 1.0f; j += step) {
				gl::vertex(lerp(mNodes[*i]->pos, from, j));
				}
			gl::end();


			//gl::drawVector(Vec3f(mNodes[*i]->pos, 0), Vec3f(from, 0));
			}
		from = mNodes[*i]->pos;
	
		topologicalCounter++;
		}
	gl::lineWidth(1);
	}
