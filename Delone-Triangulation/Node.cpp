
#include "Node.h"


Node::Node(void)
{
}


Node::~Node(void)
{
}


Node::Node(float _x, float _y)
{
	x = _x;
	y = _y;
}


bool Node::operator!= (Node p)
{
	if((this->x == p.x) && (this->y == p.y))
		return false;
	return true;
}


bool Node::operator==(Node p)
{
	if((this->x == p.x) && (this->y == p.y))
		return true;
	return false;
}