#pragma once 


#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

#include "GraphHelpers.h"
#include "boost/signals2/signal.hpp"
#include "BaseNode.h"

using namespace boost;



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

		bool bDrawTopology;
		void drawTopology();
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
