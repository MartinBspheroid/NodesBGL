#pragma once 


#include "cinder/app/App.h"
#include "cinder/gl/gl.h"


#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/breadth_first_search.hpp>


#include "boost/signals2/signal.hpp"

using namespace boost;



class BaseNode
	{
	public:
	BaseNode(const ci::Vec2f &position, const std::string &nodeName, ci::Color col = ci::Color::white()) {
		pos = position;
		color = col;
		name = nodeName;
		nodeBox = ci::Rectf(pos + ci::Vec2f(-30, -15), pos + ci::Vec2f(30, 15));
		updatePoints();
		}

	void translate(const ci::Vec2f &offset) {

		pos += offset;
		nodeBox.offset(offset);
		updatePoints();
		}

	void move(const ci::Vec2f &position) {
		pos = position;
		nodeBox.offset(pos - nodeBox.getCenter() );
		updatePoints();
		}
	void draw() {
		ci::gl::color(color);
		ci::gl::drawSolidRoundedRect(nodeBox, 5);
		//ci::gl::drawSolidRect(nodeBox);
		ci::gl::drawStringCentered(name, pos, ci::Color("black"));
		}
	ci::Vec2f pos, inPoint, outPoint;
	ci::Color color;
	std::string name;
	ci::Rectf nodeBox;
	void updatePoints() {
		inPoint = ci::Vec2f(nodeBox.getLowerLeft().x, nodeBox.getCenter().y);
		outPoint = ci::Vec2f(nodeBox.getLowerRight().x, nodeBox.getCenter().y);
		}
	};

class n_Vertex
	{
	public:
		BaseNode *pNode;
		int id;

	};

class n_Edge
	{
	public:


	};

class n_Graph
	{
	public:


	};

typedef adjacency_list <vecS, vecS, directedS, n_Vertex, n_Edge, n_Graph > nodeGraph;
typedef graph_traits<nodeGraph>::vertex_descriptor nodeVertex;
typedef adjacency_list<>::vertex_iterator nodeIterator;

class Nodes
	{
	public:
		Nodes();



		void init();

		void draw();
		void generateNew(int number);

		void addNode(const ci::Vec2f &position, std::string nodeName);

		void addEdge(const int& input, const int& output);
		void removeNode() {}
		void removeEdge() {}
		void printInfos();
	private:

		nodeGraph mNodeGraph;
		std::vector<BaseNode*> mNodes;
		std::vector<nodeVertex> mVertices;

		boost::signals2::scoped_connection mMouseBeganCallBack,
			mMouseDragCallBack,
			mMouseEndCallBack,
			mMouseMovedCallBack;


		void onMouseDown(ci::app::MouseEvent event);
		void onMouseDragged(ci::app::MouseEvent event);
		void onMouseUp(ci::app::MouseEvent event);
		void onMouseMoved(ci::app::MouseEvent event);


		void doubleClick(ci::app::MouseEvent event);
		bool bDraggingConnection, bDraggingNode, bHitNode;
		std::pair<ci::Vec2f, ci::Vec2f> draggingPos;
		int selectedNode;
		std::pair<int, int> connectNodes;
		ci::Vec2i translateOffset;
		
		double tDoubleClick;
		int nodeCount;

	};
