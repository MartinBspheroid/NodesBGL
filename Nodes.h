#pragma once 


#include "cinder/app/App.h"
#include "cinder/gl/gl.h"


#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/breadth_first_search.hpp>


#include "boost/signals2/signal.hpp"

using namespace boost;



struct PointNode
	{

	PointNode(const ci::Vec2f &position, const std::string &nodeName, ci::Color col = ci::Color::white()) {
		pos = position;
		color = col;
		name = nodeName;

		}
	ci::Vec2f pos;
	ci::Color color;
	std::string name;

	};

class n_Vertex
	{
	public:
		PointNode *pNode;
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
		std::vector<PointNode*> mNodes;
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
