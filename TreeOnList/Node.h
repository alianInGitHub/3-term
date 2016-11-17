#pragma once
class Node
{
public:
	int key;
	Node* next;
	Node* previous;
	Node(int k, Node* _next, Node* _previous) { key = k; next = _next; previous = _previous; }
};

