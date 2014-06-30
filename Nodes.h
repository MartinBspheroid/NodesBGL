#pragma once 


#include "cinder/app/App.h"
#include "cinder/gl/gl.h"


#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/breadth_first_search.hpp>


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
		void init() {
			generateNew();
			}

		void draw();
		void generateNew() {}

		void addNode(const ci::Vec2f &position, std::string &nodeName);

		void addEdge(const nodeVertex& input, const nodeVertex& output) {
			add_edge(input, output, mNodeGraph);
			}
		void removeNode() {}
		void removeEdge() {}
	private:

		nodeGraph mNodeGraph;
		std::vector<PointNode> mNodes;
		std::vector<nodeVertex> mVertices;
	};
