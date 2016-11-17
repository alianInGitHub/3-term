#pragma once
#include "List.h"
#include <iostream>
#include <vector>

class Tree :
	public List
{
	Node* root;
	void add(int key, int i);
	int number;
public:
	Tree();
	Tree(int* mas, int n);
	~Tree();
	void add(int key);
	void print();
};

