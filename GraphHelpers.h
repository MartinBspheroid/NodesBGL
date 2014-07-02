
#pragma once

#include "BaseNode.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/topological_sort.hpp>


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


typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::directedS, n_Vertex, n_Edge, n_Graph > nodeGraph;
typedef boost::graph_traits<nodeGraph>::vertex_descriptor nodeVertex;
typedef boost::adjacency_list<>::vertex_iterator nodeIterator;