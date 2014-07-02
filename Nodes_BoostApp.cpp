#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "cinder/Rand.h"

#include "Nodes.h"
#include "cinder/params/Params.h"

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

		Nodes mNodes;

		params::InterfaceGlRef gui;
	};

void Nodes_BoostApp::prepareSettings(Settings *settings) {
	settings->enableConsoleWindow();
	}

void Nodes_BoostApp::setup() {
	gui = params::InterfaceGl::create("Nodes", Vec2i(200, 200));
	
	gui->addParam("Draw topology", &mNodes.bDrawTopology);
	mNodes.init();

	gl::enableAlphaBlending(true);
	}

void Nodes_BoostApp::mouseDown(MouseEvent event) {}

void Nodes_BoostApp::update() {
	
	}

void Nodes_BoostApp::draw() {

	gl::clear(Color("lightgrey"));
	mNodes.draw();



	gui->draw();


	




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