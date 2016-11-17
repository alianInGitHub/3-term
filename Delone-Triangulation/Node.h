#pragma once
class Node
{
public:
	Node(void);
	Node(float _x, float _y);
	~Node(void);

	bool operator!= (Node p);
	bool operator==(Node p);

	float x;
	float y;
};

