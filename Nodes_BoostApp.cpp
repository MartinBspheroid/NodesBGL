#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "cinder/Rand.h"

#include "Nodes.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class Nodes_BoostApp : public AppNative
	{
	public:
		void setup();
		void mouseDown(MouseEvent event);
		void update();
		void draw();
		void prepareSettings(Settings *settings);
		void keyUp(KeyEvent event);

		nodeGraph myGraph;

		PointNode *p1, *p2, *p3, *p4;

		Nodes mNodes;
	};

void Nodes_BoostApp::prepareSettings(Settings *settings) {
	settings->enableConsoleWindow();
	}

void Nodes_BoostApp::setup() {


	mNodes.addNode(Vec2f(50, 50), "new Node");
	mNodes.addNode(Vec2f(100, 75), "new Node2");


	PointNode *p1 = new PointNode(Vec2f(100, 100), "node 1");
	PointNode *p2 = new PointNode(Vec2f(200, 300), "node 2");
	PointNode *p3 = new PointNode(Vec2f(400, 200), "node 3");
	PointNode *p4 = new PointNode(Vec2f(250, 250), "node 4");

	nodeVertex v1 = add_vertex(myGraph);
	myGraph[v1].pNode = p1;

	nodeVertex v2 = add_vertex(myGraph);
	myGraph[v2].pNode = p2;

	nodeVertex v3 = add_vertex(myGraph);
	myGraph[v3].pNode = p3;

	nodeVertex v4 = add_vertex(myGraph);
	myGraph[v4].pNode = p4;

	add_edge(v1, v2, myGraph);
	add_edge(v1, v3, myGraph);
	add_edge(v2, v4, myGraph);
	add_edge(v3, v4, myGraph);

	pair<nodeIterator, nodeIterator> p = vertices(myGraph);

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

void Nodes_BoostApp::update() {
	
	
	}

void Nodes_BoostApp::draw() {
	// clear out the window with black
	gl::clear(Color::white());


	mNodes.draw();


	gl::color(Color::black());
	auto i = edges(myGraph);
	for (auto it = i.first; it != i.second; it++) {
		gl::drawLine(myGraph[source(*it, myGraph)].pNode->pos, myGraph[target(*it, myGraph)].pNode->pos);
		}

	pair<nodeIterator, nodeIterator> p = vertices(myGraph);

	for (auto it = p.first; it != p.second; it++) {
		gl::drawSolidCircle(myGraph[*it].pNode->pos, 10);
		gl::drawStringCentered(myGraph[*it].pNode->name, myGraph[*it].pNode->pos + Vec2f(-30, -30), Color("red"));
		}

	}

void Nodes_BoostApp::keyUp(KeyEvent event) {

	switch (event.getCode()) {
		case KeyEvent::KEY_ESCAPE:
			quit();
			break;
		case KeyEvent::KEY_i:
			mNodes.printInfos();
			break;
		case KeyEvent::KEY_RETURN:
			mNodes.addNode(Vec2f(Rand::randFloat(getWindowWidth()), Rand::randFloat(getWindowWidth())), "teh new dude");
			break;
		default:
			break;
		}
	}

CINDER_APP_NATIVE(Nodes_BoostApp, RendererGl)