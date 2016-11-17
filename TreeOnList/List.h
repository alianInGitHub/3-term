#pragma once
#include "Node.h"

class List
{
public:
	List();
	~List();

	Node* head;
	Node* tail;
	int size;
	void create(int* mas, int n);
	void insert(int key, Node* &p);
	void pushFront(int key);
	void pushBack(int key);
	void remove(int key);
	void erase();
	void sort();
};

