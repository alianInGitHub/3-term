// problem_5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Tree.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	//List _list;
	cout << "Enter array of values:\n";
	cout << "number of elements: n = ";
	int size;
	cin >> size;
	int* array = new int[size];
	for (int i = 0; i < size; i++)
	{
		cin >> array[i];
	}
	Tree newTree(array, size);
	newTree.print();
	system("pause");
	return 0;
}

