#include "stdafx.h"
#include "Tree.h"
#include <math.h>

using namespace std;

Tree::Tree()
{
	root = nullptr;
	number = 0;
}


Tree::~Tree()
{
	this->erase();
}


Tree::Tree(int* mas, int n)
{
	number = 0;
	for (int i = 0; i < n; i++)
		add(mas[i]);
}


void Tree::add(int key)
{
	add(key, 0);
	root = head;
	number++;
}


void Tree::add(int key, int num)
{
	if (head == nullptr)
	{
		pushFront(key);
		return;
	}

	Node* temp = head;
	for (int i = 0; i < num && temp != nullptr; i++)
		temp = temp->next;
	if (key > temp->key)
	{
		if (size - (2 * num + 2) < 0)
		{
			while (size - (2 * num + 2) < 0)
				pushBack(0);
			tail->key = key;
		}
		else
		{
			for (int i = 0; i < num + 2; i++)
				temp = temp->next;
			if (temp->key == 0)
				temp->key = key;
			else
			add(key, 2 * num + 2);
		}
	}
	else
	{
		if (size - 2 * num + 1 < 0)
		{
			while (size - 2 * num + 1 < 0)
				pushBack(0);
			tail->key = key;
		}
		else
		{
			for (int i = 0; i < num + 1; i++)
				temp = temp->next;
			if (temp->key == 0)
				temp->key = key;
			else
			add(key, 2 * num + 1);
		}
	}
}


void Tree::print()
{
	cout << "Tree" << endl;
	int levels = 0;
	while (pow(2, levels) < size)
		levels++;

	int spaces = 50;
	Node* temp = head;
	for (int i = 0; i < levels; i++)
	{
		for (int j = pow(2, i) - 1; temp != nullptr && i < pow(2, i + 1); j++, temp = temp->next)
		{
			for (int k = 0; k < spaces; k++)
				cout << " ";
			cout << temp->key;
		}
		cout << endl;
		spaces = spaces / 2;
	}
}
