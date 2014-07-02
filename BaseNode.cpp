#include "BaseNode.h"

BaseNode::BaseNode(const ci::Vec2f &position, const std::string &nodeName, ci::Color col /*= ci::Color::white()*/) {
	pos = position;
	color = col;
	name = nodeName;
	nodeBox = ci::Rectf(pos + ci::Vec2f(-30, -15), pos + ci::Vec2f(30, 15));
	updatePoints();
}

void BaseNode::translate(const ci::Vec2f &offset) {
	pos += offset;
	nodeBox.offset(offset);
	updatePoints();
}

void BaseNode::move(const ci::Vec2f &position) {
	pos = position;
	nodeBox.offset(pos - nodeBox.getCenter());
	updatePoints();
}

void BaseNode::draw() {
	ci::gl::color(color);
	ci::gl::drawSolidRoundedRect(nodeBox, 5);
	//ci::gl::drawSolidRect(nodeBox);
	ci::gl::drawStringCentered(name, pos, ci::Color("black"));
}

void BaseNode::updatePoints() {
	inPoint = ci::Vec2f(nodeBox.getLowerLeft().x, nodeBox.getCenter().y);
	outPoint = ci::Vec2f(nodeBox.getLowerRight().x, nodeBox.getCenter().y);
}
