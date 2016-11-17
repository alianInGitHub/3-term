#include "stdafx.h"
#include "List.h"
#include <iostream>

using namespace std;

List::List()
{
	head = tail = nullptr;
	size = 0;
}


List::~List()
{
	this->erase();
}


void List::create(int* mas, int n)
{
	if (n == 0) { head = tail = nullptr; return; }
	head = new Node(mas[0], nullptr, nullptr);
	tail = head;
	for (int i = 1; i < n; i++)
	{
		tail->next = new Node(mas[i], nullptr, tail);
		tail = tail->next;
	}
	size = n;
}

void List::insert(int key, Node* &p)
{
	Node* newNode = new Node(key, p->next, p);
	p->next = newNode;
	if (p == tail) tail = newNode;
	size++;
}

void List::pushFront(int key)
{
	if (head == nullptr)
	{
		head = new Node(key, nullptr, nullptr);
		tail = head;
		return;
	}
	Node* newNode = new Node(key, head, nullptr);
	head->previous = newNode;
	head = newNode;
	size++;
}


void List::pushBack(int key)
{
	if (tail == nullptr)
	{
		head = new Node(key, nullptr, nullptr);
		tail = head;
	}
	else
	{
		tail->next = new Node(key, nullptr, tail);
		tail = tail->next;
	}
	size++;
}

void List::remove(int key)
{
	Node* del_Node = nullptr;
	if (head->key == key)
	{
		del_Node = head;
		head = head->next;
		if (head != nullptr);
		head->previous = nullptr;
	}
	else
	{
		for (auto it = head->next; it != nullptr; it = it->next)
		{
			if (it->next->key == key)
			{
				del_Node = it->next;
				it->next->next->previous = it;
				it->next = it->next->next;
				if (del_Node == tail) { tail = it; }
			}
		}
	}
	if (del_Node != nullptr)
	{
		del_Node->next = nullptr;
		del_Node->previous = nullptr;
		delete(del_Node);
	}
	size--;
}

void List::erase()
{
	while (head != nullptr)
	{
		remove(head->key);
	}
	size = 0;
}

void swap(Node* &a, Node* &b)
{
	int c = a->key;
	a->key = b->key;
	b->key = c;
}


void List::sort()
{
	for (auto it = head; it->next != nullptr; it = it->next)
	{
		for (auto jt = head; jt->next != nullptr; jt = jt->next)
			if (jt->key > jt->next->key)
				swap(jt, jt->next);
	}
	for (auto it = head; it != nullptr; it = it->next)
		cout << it->key << " ";
	cout << endl;
}