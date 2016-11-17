#pragma once
#include "Node.h"
#include <vector>

class Triangle
{
	std::vector<Node> nodes;
public:
	Triangle(void);
	~Triangle(void);
	Triangle(Node n1, Node n2, Node n3);
	bool operator!=(Triangle& tr);
	bool operator==(Triangle& tr);
	Node &operator[](int i)
	{
		if((i < (int)nodes.size()) && (i >= 0))
		   return nodes[i];
		Node p;
		return p;
	}
	std::vector<Node>& get_nodes()
	{
		return nodes;
	}
	void print();
};

