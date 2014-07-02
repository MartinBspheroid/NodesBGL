#pragma once
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "boost/signals2.hpp"
#include "boost/signals2/signal.hpp"

class BaseNode
	{
	public:
		BaseNode(const ci::Vec2f &position, const std::string &nodeName, ci::Color col = ci::Color::white());

		void translate(const ci::Vec2f &offset);

		void move(const ci::Vec2f &position);
		void updatePoints();
		void draw();
		//ci::Color color;
		ci::Color  color;
		std::string name;
		ci::Rectf nodeBox;
		ci::Vec2f pos, inPoint, outPoint;

		boost::signals2::signal<void()>  nodeSignal;
		//boost::signals2::signal nodeSignal2;
	};
