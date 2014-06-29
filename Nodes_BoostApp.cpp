#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/breadth_first_search.hpp>


using namespace ci;
using namespace ci::app;
using namespace std;
using namespace boost;


struct PointNode
	{

	PointNode(const Vec2f &position, const string &nodeName, Color col = Color::white()) {
		pos = position;
		color = col;
		name = nodeName;

		}
	Vec2f pos;
	Color color;
	string name;
	adjacency_list<>::vertex_descriptor vrtx;

	};




class nVertex
	{
	public:
		PointNode *pNode;

	};

class nEdge
	{
	public:


	};

class nGraph
	{
	public:


	};

typedef boost::adjacency_list <	boost::vecS, boost::vecS, boost::directedS, nVertex, nEdge, nGraph > graph_t;
typedef boost::graph_traits<graph_t>::vertex_descriptor vertex_t;
typedef adjacency_list<>::vertex_iterator iter;


class Nodes_BoostApp : public AppNative
	{
	public:
		void setup();
		void mouseDown(MouseEvent event);
		void update();
		void draw();
		void prepareSettings(Settings *settings);
		void keyUp(KeyEvent event);

		graph_t myGraph;

		PointNode *p1, *p2, *p3, *p4;
	};

void Nodes_BoostApp::prepareSettings(Settings *settings) {
	settings->enableConsoleWindow();
	}

void Nodes_BoostApp::setup() {

	PointNode *p1 = new PointNode(Vec2f(100, 100), "node 1");
	PointNode *p2 = new PointNode(Vec2f(200, 300), "node 2");
	PointNode *p3 = new PointNode(Vec2f(400, 200), "node 3");
	PointNode *p4 = new PointNode(Vec2f(250, 250), "node 4");

	vertex_t v1 = add_vertex(myGraph);
	myGraph[v1].pNode = p1;

	vertex_t v2 = add_vertex(myGraph);
	myGraph[v2].pNode = p2;

	vertex_t v3 = add_vertex(myGraph);
	myGraph[v3].pNode = p3;

	vertex_t v4 = add_vertex(myGraph);
	myGraph[v4].pNode = p4;


	add_edge(v1, v2, myGraph);
	add_edge(v1, v3, myGraph);
	add_edge(v2, v4, myGraph);
	add_edge(v3, v4, myGraph);

	pair<iter, iter> p = vertices(myGraph);

	for (auto it = p.first; it != p.second; it++) {
		cout << *it << "\t" << typeid(*it).name() << endl;
		cout << myGraph[*it].pNode->name << endl;

		}

	auto i = edges(myGraph);
	for (auto it = i.first; it != i.second; it++) {


		cout << myGraph[source(*it, myGraph)].pNode->name <<
			" : " << myGraph[target(*it, myGraph)].pNode->name << endl;

		}

	gl::enableAlphaBlending(true);
	}

void Nodes_BoostApp::mouseDown(MouseEvent event) {}

void Nodes_BoostApp::update() {}

void Nodes_BoostApp::draw() {
	// clear out the window with black
	gl::clear(Color(0, 0, 0));


	auto i = edges(myGraph);
	for (auto it = i.first; it != i.second; it++) {
		gl::drawLine(myGraph[source(*it, myGraph)].pNode->pos, myGraph[target(*it, myGraph)].pNode->pos);
		}


	pair<iter, iter> p = vertices(myGraph);

	for (auto it = p.first; it != p.second; it++) {
		gl::drawSolidCircle(myGraph[*it].pNode->pos, 10);
		gl::drawStringCentered(myGraph[*it].pNode->name, myGraph[*it].pNode->pos, Color("red"));
		}



	}

void Nodes_BoostApp::keyUp(KeyEvent event) {

	switch (event.getCode()) {
		case KeyEvent::KEY_ESCAPE:
			quit();
			break;
		default:
			break;
		}
	}

CINDER_APP_NATIVE(Nodes_BoostApp, RendererGl)