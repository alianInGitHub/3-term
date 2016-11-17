#include "Triangle.h"
#include <iostream>

using namespace std;


Triangle::Triangle(void)
{
}


Triangle::~Triangle(void)
{
}


Triangle::Triangle(Node n1,Node n2,Node n3)
{
	nodes.push_back(n1);
	nodes.push_back(n2);
	nodes.push_back(n3);
}


bool Triangle::operator==(Triangle &tr)
{
	if(this->nodes.size() != tr.nodes.size())
		return false;
	for(vector<Node>::iterator jt = tr.nodes.begin(), it = this->nodes.begin(); jt != tr.nodes.end(); jt ++, it++)
	{
		if(*jt != *it)
			return false;
	}
	return true;
}


bool Triangle::operator!=(Triangle &tr)
{
	if(this->nodes.size() != tr.nodes.size())
		return true;
	for(vector<Node>::iterator jt = tr.nodes.begin(), it =this->nodes.begin(); jt != tr.nodes.end(); jt ++, it++)
	{
		if(*jt != *it)
			return true;
	}
	return false;
}


void Triangle::print()
{
	for(vector<Node>::iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		cout << (*it).x << " " << (*it).y << "; ";
	}
}

