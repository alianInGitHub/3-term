#include "Triangulation.h"
#include <math.h>
#include <iostream>
#include <algorithm>

using namespace std;

namespace Triangulation
{
	//.............................................................................................//
	//...........................     NODE CLASS REALISATION      .................................//
	//.............................................................................................//

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
		if ((this->x == p.x) && (this->y == p.y))
			return false;
		return true;
	}


	bool Node::operator==(Node p)
	{
		if ((this->x == p.x) && (this->y == p.y))
			return true;
		return false;
	}

	//.............................................................................................//
	//.........................     TRIANGLE CLASS REALISATION      ...............................//
	//.............................................................................................//


	Triangle::Triangle(void)
	{
	}


	Triangle::~Triangle(void)
	{
	}


	Triangle::Triangle(Node n1, Node n2, Node n3)
	{
		nodes.push_back(n1);
		nodes.push_back(n2);
		nodes.push_back(n3);
	}


	bool Triangle::operator==(Triangle &tr)
	{
		if (this->nodes.size() != tr.nodes.size())
			return false;
		for (vector<Node>::iterator jt = tr.nodes.begin(), it = this->nodes.begin(); jt != tr.nodes.end(); jt++, it++)
		{
			if (*jt != *it)
				return false;
		}
		return true;
	}


	bool Triangle::operator!=(Triangle &tr)
	{
		if (this->nodes.size() != tr.nodes.size())
			return true;
		for (vector<Node>::iterator jt = tr.nodes.begin(), it = this->nodes.begin(); jt != tr.nodes.end(); jt++, it++)
		{
			if (*jt != *it)
				return true;
		}
		return false;
	}


	void Triangle::print()
	{
		for (vector<Node>::iterator it = nodes.begin(); it != nodes.end(); it++)
		{
			cout << (*it).x << " " << (*it).y << "; ";
		}
	}


	//.............................................................................................//

	bool isVertical = true; // in order to devide the nodes in different way: 
							 // 1st time - vertically
							 // 2nd time - horisontically

	std::vector<Triangle*> mergeFourNodes(std::vector<Node> nodes);									// merges 4 nodes into 2 triangles

	std::vector<Node> devideEightNodes(std::vector<Node> &nodes);										// devides 8 nodes into 4 and 4

	std::vector<Node> devideTwelveNodes(std::vector<Node> &nodes);									// devides less then 12 nodes into 3 and other

	std::vector<Node> devideToHalf(std::vector<Node> &nodes);										// devides N nodes into N / 2 and N / 2

	std::vector<Triangle*> merge(std::vector<Triangle*> a_nodes, std::vector<Triangle*> b_nodes);	// merges 2 sets og triangles into 1 set

	std::vector<Triangle*> mergeNodeAndTriangles(Node &dot, std::vector<Triangle*> trians);		// merges set of triangles with 1 nodes (used to merge 5 nodes)

	void print(std::vector<Node> nodes);															// prints information about nodes

	void print(std::vector<Triangle*> trs);															// print informationabout triangles



	//.........................................................................................................................................//
	//......................................									    ...........................................................//
	//......................................        TRIANGULATION REALIZATION       ...........................................................//
	//......................................										...........................................................//
	//.........................................................................................................................................//


	// finds the coordinates of center of the circumscribed circle
	Node cyrcleCenter(vector<Node> &dots)
	{
		float m_a = (dots[1].y - dots[0].y) / (dots[1].x - dots[0].x);
		float m_b = (dots[2].y - dots[1].y) / (dots[2].x - dots[1].x);

		Node center(0, 0);
		center.x = (m_a * m_b * (dots[0].y - dots[2].y) + m_b * (dots[0].x + dots[1].x) - m_a * (dots[1].x + dots[2].x))
			/ (2 * (m_b - m_a));
		center.y = (center.x - (dots[0].x + dots[1].x) / 2) / m_a + (dots[0].y + dots[1].y) / 2;
		return center;
	}


	// checks if array contains the element
	bool contains(Node &p, vector<Node> nodes)
	{
		if (nodes.empty())
			return false;
		for (vector<Node>::iterator it = nodes.begin(); it != nodes.end(); it++)
		{
			if (*it == p)
				return true;
		}
		return false;
	}


	bool compare(Node a, Node b) {
		return a.x < b.x || a.x == b.x && a.y < b.y;
	}

	//clockwise
	bool clockWise(Node a, Node b, Node c) {
		return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) < 0;
	}
	//counterclockwise
	bool counterClockWise(Node a, Node b, Node c) {
		return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) > 0;
	}

	//finds convex hull
	vector<Node> convexHull(vector<Node> _nodes)
	{
		if (_nodes.size() == 1) {
			return _nodes;
		}
		vector<Node> nodes;
		for (vector<Node>::iterator it = _nodes.begin(); it != _nodes.end(); it++)
		{
			nodes.push_back(*it);
		}
		sort(nodes.begin(), nodes.end(), &compare);
		Node p1 = nodes[0], p2 = nodes.back();
		vector<Node> up, down;
		up.push_back(p1);
		down.push_back(p1);
		for (unsigned i = 1; i < nodes.size(); ++i) {
			if (i == nodes.size() - 1 || clockWise(p1, nodes[i], p2)) {
				while (up.size() >= 2 && !clockWise(up[up.size() - 2], up[up.size() - 1], nodes[i]))
					up.pop_back();
				up.push_back(nodes[i]);
			}
			if (i == nodes.size() - 1 || counterClockWise(p1, nodes[i], p2)) {
				while (down.size() >= 2 && !counterClockWise(down[down.size() - 2], down[down.size() - 1], nodes[i]))
					down.pop_back();
				down.push_back(nodes[i]);
			}
		}
		_nodes.clear();
		for (unsigned i = 0; i < up.size(); ++i)
			_nodes.push_back(up[i]);
		for (unsigned i = down.size() - 2; i > 0; --i)
			_nodes.push_back(down[i]);
		return _nodes;
	}


	// returns distance from one node to another
	float length(Node* from, Node* to)
	{
		return sqrtf(pow(from->x - to->x, 2) + pow(from->y - to->y, 2));
	}

	//finds the lowest node
	Node Lowest(vector<Triangle*> &trs)
	{
		Node lowest = (*trs[0])[0];
		for (vector<Triangle*>::iterator it = trs.begin(); it != trs.end(); it++)
		{
			for (int i = 0; i < 3; i++)
			{
				if ((**it)[i].y > lowest.y)
				{
					lowest = (**it)[i];
				}
			}
		}
		return lowest;
	}

	//fins the highestnode
	Node Highest(vector<Triangle*> &trs)
	{
		Node highest = (*trs[0])[0];
		for (vector<Triangle*>::iterator it = trs.begin(); it != trs.end(); it++)
		{
			for (int i = 0; i < 3; i++)
			{
				if ((**it)[i].y < highest.y)
				{
					highest = (**it)[i];
				}
			}
		}
		return highest;
	}

	// ckecks if the node is inside the circle
	bool isInside(Node* _node, Node* center, float r)
	{
		if (pow(_node->x - center->x, 2) + pow(_node->x - center->x, 2) <= r * r)
			return true;
		return false;
	}

	//ckecks if the node belongs to triangle
	bool contains(Triangle tr, Node* p)
	{
		if (((tr[0]) == (*p)) || (tr[1] == *p) || (tr[2] == *p))
			return true;
		return false;
	}


	//checks if the node
	bool isInnerNode(Triangle tr, int nearest, Node* h, Node* center)
	{
		vector<int> vc;
		vector<vector<int>> v;
		//vector to the center from the highest
		vc.push_back(center->x - h->x);
		vc.push_back(center->y - h->y);
		//vector from the highest to the nodes
		for (int i = 0; i < 3; i++)
		{
			vector<int> vi;
			if (tr[i] != *h)
			{
				vi.push_back(tr[i].x - h->x);
				vi.push_back(tr[i].y - h->y);
				v.push_back(vi);
			}
		}
		if (v.size() > 2)
		{
			cout << "Error H inner node" << endl;
			system("pause");
		}
		if (nearest > 1) nearest = 1;
		double a[2];

		a[0] = acos((vc[0] * v[0][0] + vc[1] * v[0][1]) /
			(sqrt(vc[0] * vc[0] + vc[1] * vc[1]) *            //mod vc
				sqrt(v[0][0] * v[0][0] + v[0][1] * v[0][1])));    //mod v[0]
		a[1] = acos((vc[0] * v[1][0] + vc[1] * v[1][1]) /
			(sqrt(vc[0] * vc[0] + vc[1] * vc[1]) *            //mod vc
				sqrt(v[1][0] * v[1][0] + v[1][1] * v[1][1])));    //mod v[1]

		if (a[nearest] < a[(nearest + 1) % 2])
			return false;
		return true;
	}


	bool convexity(std::vector<Node> &_nodes)
	{
		std::vector<Node> conv = convexHull(_nodes);
		if (conv.size() == _nodes.size()) return true;
		return false;
	}


	bool isInside(Node p, Triangle tr)
	{
		//sort by x
		for (int i = 0; i < 2; i++)
			for (int j = i; j < 2; j++)
				if (tr[j].x > tr[j + 1].x)
				{   //swap
					Node t = tr[j];
					tr[j] = tr[j + 1];
					tr[j + 1] = t;
				}
		if (!((p.x > tr[0].x) && (p.x < tr[2].x)))
			return false;

		//sort by y
		for (int i = 0; i < 2; i++)
			for (int j = i; j < 2; j++)
				if (tr[j].y > tr[j + 1].y)
				{ //swap
					Node t = tr[j];
					tr[j] = tr[j + 1];
					tr[j + 1] = t;
				}
		if (!((p.y > tr[0].y) && (p.y < tr[2].y)))
			return false;
		return true;
	}


	bool isInside(Node p, vector<Node> nodes, int first)
	{
		//sort by x
		for (int i = 0; i < nodes.size() - 1; i++)
			for (int j = i; j < nodes.size() - 1; j++)
				if (nodes[j].x > nodes[j + 1].x)
				{   //swap
					Node t = nodes[j];
					nodes[j] = nodes[j + 1];
					nodes[j + 1] = t;
				}
		if (first == 1)
		{
			if (!((p.x >= nodes[0].x) && (p.x < nodes[nodes.size() - 1].x)))
				return false;
		}
		else
			if (first == 0)
			{
				if (!((p.x > nodes[0].x) && (p.x <= nodes[nodes.size() - 1].x)))
					return false;
			}
			else
			{
				if (!((p.x > nodes[0].x) && (p.x < nodes[nodes.size() - 1].x)))
					return false;
			}

		//sort by y
		for (int i = 0; i < nodes.size() - 1; i++)
			for (int j = i; j < nodes.size() - 1; j++)
				if (nodes[j].y > nodes[j + 1].y)
				{ //swap
					Node t = nodes[j];
					nodes[j] = nodes[j + 1];
					nodes[j + 1] = t;
				}
		if (first == 1)
		{
			if (!((p.y >= nodes[0].y) && (p.y < nodes[nodes.size() - 1].y)))
				return false;
			return true;
		}
		else
			if (!first)
			{
				if (!((p.y > nodes[0].y) && (p.y <= nodes[nodes.size() - 1].y)))
					return false;
				return true;
			}
			else
			{
				if (!((p.y > nodes[0].y) && (p.y < nodes[nodes.size() - 1].y)))
					return false;
				return true;
			}
	}




	///..........................................................................................................................///
	///................................................TriangulationDelone.......................................................///
	///..........................................................................................................................///


	/*******************************************************************************************************************************
	Description
	Triangulation Delone triangulate the array of nodes, that for every triangle all nodes,
	exept those which are it's vertexes, lays out of circumscribed circle.

	ALGORITHM
	let's n - number of nodes
	1) if n > 12 devide to half
	if n = 8 devide to half (4 and 4 nodes)
	if n > 4 devide to 3 and rest nodes
	if n = 3 connect all nodes
	if n = 4
	- if they compose a convex quadrangle, build a circumscribed circle for 3 nodes and check the position of the 4th:
	* if node is outside of the circle, everything is OK, connect it with 2 nearest nodes
	* if node is inside of the circle, connect node with all other nodes, connect other nodes that no edges intersects
	* if it's on circle, no matter with way to move
	- if it's not a convex quedrangle, we just connect the node with all other nodes
	2) merge all triangles
	**********************************************************************************************************************************/
	vector<Triangle*> TriangulationDelone(vector<Node> nodes)
	{
		vector<Triangle*> result;
		if (nodes.size() < 3) return result;
		if (nodes.size() == 3)
		{
			Triangle* tr = new Triangle(nodes[0], nodes[1], nodes[2]);
			result.push_back(tr);
		}
		else
		{
			if (nodes.size() == 4)
			{
				result = mergeFourNodes(nodes);
			}
			else
			{

				vector<Node> new_array;
				if (nodes.size() == 8)
				{
					new_array = devideEightNodes(nodes);
				}
				else

					if (nodes.size() <= 12)
					{
						new_array = devideTwelveNodes(nodes);
					}
					else
					{
						new_array = devideToHalf(nodes);
					}
				if (nodes.size() < 3)
				{
					if (nodes[0].x < nodes[1].x)
					{
						new_array.push_back(nodes[0]);
						result = mergeFourNodes(new_array);
						result = mergeNodeAndTriangles(nodes[1], result);
					}
					else
					{
						new_array.push_back(nodes[1]);
						result = mergeFourNodes(new_array);
						result = mergeNodeAndTriangles(nodes[0], result);
					}
				}
				else
				{
					vector<Triangle*> temp;
					temp = TriangulationDelone(new_array);
					result = TriangulationDelone(nodes);
					result = merge(temp, result);
				}
			}
		}
		print(result);
		return result;
	}



	//used to merge 5 nodes
	vector<Triangle*> mergeNodeAndTriangles(Node &dot, vector<Triangle*> trians)
	{
		vector<Node> nodes;
		if (trians.size() == 1)
		{
			nodes = trians[0]->get_nodes();
			nodes.push_back(dot);
			return mergeFourNodes(nodes);
		}
		bool done = false;
		int n = trians.size();
		for (int i = 0; i < n; i++)
		{
			if (isInside(dot, *trians[i]))
			{
				done = true;
				Triangle* tr = new Triangle(dot, (*trians[i])[0], (*trians[i])[1]);
				trians.push_back(tr);
				tr = new Triangle(dot, (*trians[i])[0], (*trians[i])[2]);
				trians.push_back(tr);
				tr = new Triangle(dot, (*trians[i])[1], (*trians[i])[2]);
				trians.push_back(tr);
			}

		}
		if (!done)
		{
			// find the highest and the lowest node
			Node H1 = Highest(trians);
			Node L1 = Lowest(trians);

			// find all nodes exept dot
			vector<Node> tnodes;
			for (vector<Triangle*>::iterator it = trians.begin(); it != trians.end(); it++)
			{
				if (!nodes.empty())
				{
					for (vector<Node>::iterator j = (*it)->get_nodes().begin(); j != (*it)->get_nodes().end(); j++)
					{
						if (!contains(*j, nodes))
							nodes.push_back(*j);
					}
				}
				else nodes = (*it)->get_nodes();
			}

			tnodes = nodes;
			// find a convex for all nodes with dot
			tnodes.push_back(dot);
			tnodes = convexHull(tnodes);
			// check if dot is seen from the highest and the lowest node
			// if not, change H1 and L1
			for (int i = 0; i < tnodes.size(); i++)
			{
				if (tnodes[i] == L1)
				{
					while (tnodes[(i + 1) % tnodes.size()] != dot)
					{
						L1 = tnodes[(i + 1) % tnodes.size()];
						i = (i + 1) % tnodes.size();
					}
					i = tnodes.size();
				}
			}

			for (int i = 0; i < tnodes.size(); i++)
			{
				if (tnodes[i] == dot)
				{
					H1 = tnodes[(i + 1) % tnodes.size()];
					i = tnodes.size();
				}
			}
			// delete dot from convex hull of all nodes
			tnodes = convexHull(nodes);
			// while we haven't went through all border noder to the lowest one
			while (H1 != L1)
			{
				// set center of circle
				float radius = 20;
				Node* center = new Node((H1.x + dot.x) / 2, (H1.y + dot.y) / 2);
				Node nearest_1;
				// and find the nearest node, exept H1
				float nearest_len_1 = theNearestNode(center, nodes, &H1, nearest_1);

				// find the triangle which consist thisnode
				Triangle nearest_triangle;
				for (vector<Triangle*>::iterator it = trians.begin(); it != trians.end(); it++)
				{
					if (contains(**it, &nearest_1) && contains(**it, &H1) && contains(**it, &L1))
					{
						nearest_triangle = **it;
						it = trians.end() - 1;
					}
				}
				// if the node is inner (there's an edge which is intersected by new edge)
				bool convex = false;
				if (isInside(nearest_1, tnodes, 1))
				{
					// we break the Triangle
					if (convexity(nodes))
					{
						trians.clear();
						convex = true;
					}
					else
					{
						bool away = false;
						for (vector<Triangle*>::iterator it = trians.begin(); it != trians.end(); it++)
						{
							if ((**it) == nearest_triangle)
							{
								trians.erase(it);
								away = true;
							}
							if (away)
								break;
						}
					}
				}
				// and form the new one
				if (convex)
				{
					Triangle* tr = new Triangle(dot, H1, nearest_1);
					trians.push_back(tr);
					for (auto it : nodes)
					{
						if ((it != H1) && (it != L1) && (it != nearest_1))
						{
							tr = new Triangle(dot, nearest_1, it);
							trians.push_back(tr);
							tr = new Triangle(dot, it, L1);
							trians.push_back(tr);
							tr = new Triangle(it, H1, nearest_1);
							trians.push_back(tr);
						}
					}
					H1 = L1;
				}
				else
				{
					Triangle* new_tr = new Triangle(H1, dot, nearest_1);
					trians.push_back(new_tr);
					H1 = nearest_1;
				}
			}
		}
		return trians;
	}


	vector<Triangle*> merge(vector<Triangle*> trians, vector<Triangle*> trians_2)
	{
		if (trians.empty() && trians_2.empty())
		{
			return trians;
		}
		else
			if (trians.empty())
			{
				return trians_2;
			}
			else
				if (trians_2.empty())
					return trians;

		// find H1 and H2,  L1 and L2
		Node H1 = Highest(trians);
		Node H2 = Highest(trians_2);

		Node L1 = Lowest(trians);
		Node L2 = Lowest(trians_2);

		// vector of nodes, which these triangls consist
		// tnodes - all nodes
		// tnodes_1 - consist in trian_1
		// tnodes_2 - consist in trian_2

		vector<Node> tnodes;
		vector<Node> tnodes_1;
		vector<Node> tnodes_2;

		// fill these vectors
		for (auto it : trians)
		{
			if (!tnodes_1.empty())
			{
				for (auto jt : (*it).get_nodes())
				{
					if (!contains(jt, tnodes_1))
					{
						tnodes_1.push_back(jt);
					}
				}
			}
			else
				tnodes_1 = it->get_nodes();
		}

		for (auto it : trians_2)
		{
			if (!tnodes_2.empty())
			{
				for (auto jt : it->get_nodes())
				{
					if (!contains(jt, tnodes_2))
						tnodes_2.push_back(jt);
				}
			}
			else
				tnodes_2 = it->get_nodes();
		}

		tnodes = tnodes_1;
		tnodes.insert(tnodes.end(), tnodes_2.begin(), tnodes_2.end());

		trians.insert(trians.end(), trians_2.begin(), trians_2.end());

		// find H1 and others :)
		tnodes = convexHull(tnodes);
		for (int i = 0; i < tnodes.size(); i++)
		{
			if (tnodes[i] == H2)
			{
				while (contains(tnodes[(i + 1) % tnodes.size()], tnodes_2))
				{
					H2 = tnodes[(i + 1) % tnodes.size()];
					i = (i + 1) % tnodes.size();
				}
				if (tnodes[(i + 1) % tnodes.size()] != H1)
				{
					H1 = tnodes[(i + 1) % tnodes.size()];
				}
				i = tnodes.size();
			}
		}

		for (int i = 0; i < tnodes.size(); i++)
		{
			if (tnodes[i] == L1)
			{
				while (!contains(tnodes[(i + 1) % tnodes.size()], tnodes_2))
				{
					L1 = tnodes[(i + 1) % tnodes.size()];
					i = (i + 1) % tnodes.size();
				}
				if (tnodes[(i + 1) % tnodes.size()] != L2)
				{
					L2 = tnodes[(i + 1) % tnodes.size()];
				}
			}
		}

		// initialisation ended+++ ^_^

		//main_loop
		/****************************************************************************************/
		//  MERGE ALGORITHM
		// H1 - the highest node in first array of triangles from wich we can directly see the H2
		// L1 - the lowest node in .-.-.-.-.-.- see the L2
		// 1) Find the third node N
		//    We connect by edge H1 and H2 and find the closest node to this edge.
		//    The search is done by broading the circle with a center in the middle 
		//    of H1-H2 edge. The nearest node N will get caught firstly.
		// 2) Add triangle H1-N-H2 to the result
		// 3) if N contains in H1 we set N as H1 
		//    else set the H2 as N
		// do all these steps while H1 != L1 and H2 != L2
		/****************************************************************************************/

		while ((H1 != L1) || (H2 != L2))
		{
			// set the center of the search circle
			float radius = 20;
			Node* center = new Node((H1.x + H2.x) / 2, (H1.y + H2.y) / 2);

			tnodes.clear();

			// find the nearest node in every array
			Node nearest_1;
			float nearest_len_1 = theNearestNode(center, tnodes_1, &H1, nearest_1);

			Node nearest_2;
			float neares_len_2 = theNearestNode(center, tnodes_2, &H2, nearest_2);

			// chose the nearest one
			bool chosen_node_is_in_first_array;
			if (nearest_len_1 < neares_len_2)
			{
				if (H1 != L1)
				{
					chosen_node_is_in_first_array = true;
				}
				else
				{
					chosen_node_is_in_first_array = false;
				}
			}
			else
			{
				if (H2 != L2)
				{
					chosen_node_is_in_first_array = false;
				}
				else
					chosen_node_is_in_first_array = true;
			}

			if (chosen_node_is_in_first_array)
			{
				tnodes = convexHull(tnodes_1);
				// find triangle which contains this node
				// if node is not on the border of triangulation
				Node next_to_H1;
				for (int i = 0; i < tnodes.size(); i++)
				{
					if (tnodes[(i + 1) % tnodes.size()] == H1)
					{
						next_to_H1 = tnodes[i];
						i = tnodes.size();
					}
				}
				if (next_to_H1 != nearest_1)
				{
					// find triangle which contains this node
					// we break intersected Triangles
					// and form new ones
					Triangle nearest_triangle;

					pair<Node, Node> edge;
					vector<Node> nodes_to_merge_again;
					edge.first = next_to_H1;
					edge.second = H1;
					while (edge.second != nearest_1)
					{
						for (vector<Triangle*>::iterator it = trians.begin(); it != trians.end(); it++)
						{
							if (contains(**it, &edge.first) && contains(**it, &edge.second))
							{
								for (auto i = (*it)->get_nodes().begin(); i != (*it)->get_nodes().end(); i++)
								{
									if ((*i != edge.first) && (*i != edge.second))
									{
										edge.second = *i;
										i = (*it)->get_nodes().end() - 1;
									}
								}
								if (nodes_to_merge_again.empty())
								{
									nodes_to_merge_again = (*it)->get_nodes();
								}
								else
								{
									for (auto i : (*it)->get_nodes())
										if (!contains(i, nodes_to_merge_again))
											nodes_to_merge_again.push_back(i);
								}
								trians.erase(it);
								it = trians.end() - 1;
							}
						}
					}
					nodes_to_merge_again.push_back(H2);
					vector<Triangle*> temp_trians = TriangulationDelone(nodes_to_merge_again);
					trians.insert(trians.end(), temp_trians.begin(), temp_trians.end());
					H1 = next_to_H1;
				}
				else
				{
					Triangle* new_triangle = new Triangle(H1, H2, nearest_1);
					trians.push_back(new_triangle);
					H1 = nearest_1;
				}
			}
			else
			{
				tnodes = convexHull(tnodes_2);
				// find triangle which contains this node
				// if node is not on the border of triangulation
				Node next_to_H2;
				for (int i = 0; i < tnodes.size(); i++)
				{
					if (tnodes[i] == H2)
					{
						next_to_H2 = tnodes[(i + 1) % tnodes.size()];
						i = tnodes.size();
					}
				}
				if (next_to_H2 != nearest_2)
				{
					// find triangle which contains this node
					// we break intersected Triangles
					// and form new ones
					Triangle nearest_triangle;

					pair<Node, Node> edge;
					vector<Node> nodes_to_merge_again;
					edge.first = next_to_H2;
					edge.second = H2;
					while (edge.second != nearest_2)
					{
						for (vector<Triangle*>::iterator it = trians.begin(); it != trians.end(); it++)
						{
							if (contains(**it, &edge.first) && contains(**it, &edge.second))
							{
								for (auto i = (*it)->get_nodes().begin(); i != (*it)->get_nodes().end(); i++)
								{
									if ((*i != edge.first) && (*i != edge.second))
									{
										edge.second = *i;
										i = (*it)->get_nodes().end() - 1;
									}
								}
								if (nodes_to_merge_again.empty())
								{
									nodes_to_merge_again = (*it)->get_nodes();
								}
								else
								{
									for (auto i : (*it)->get_nodes())
										if (!contains(i, nodes_to_merge_again))
											nodes_to_merge_again.push_back(i);
								}
								trians.erase(it);
								it = trians.end() - 1;
							}
						}
					}
					nodes_to_merge_again.push_back(H1);
					vector<Triangle*> temp_trians = TriangulationDelone(nodes_to_merge_again);
					trians.insert(trians.end(), temp_trians.begin(), temp_trians.end());
					H2 = next_to_H2;
				}
				else
				{
					Triangle* new_triangle = new Triangle(H1, H2, nearest_2);
					trians.push_back(new_triangle);
					H2 = nearest_2;
				}
			}
		}
		// fill trians;
		return trians;
	}


	vector<Triangle*> mergeFourNodes(std::vector<Node> nodes)
	{
		vector<Triangle*> result;
		// if rectangle is convex
		if (convexity(nodes))
		{
			// find the cyrcle of a Triangle, ground on first 3 nodes
			// take the 4th node
			// and value the distance from the 4th node to the center of this cyrcle
			Node center = cyrcleCenter(nodes);
			Node radius(center.x - nodes[2].x, center.y - nodes[2].y);
			float radius_len = sqrtf(pow(radius.x, 2) + pow(radius.y, 2));
			Node vector(center.x - nodes[3].x, center.y - nodes[3].y);
			float vector_len = sqrtf(pow(vector.x, 2) + pow(vector.y, 2));

			if (vector_len < radius_len)
			{
				// then we have an irregular rectangle
				// 1) connect the 4th node with all another nodes
				// 2) connect another nodes such way, that no this connnections intersect with built connections

				std::vector<Node> vtemp = convexHull(nodes);
				int* queue = new int[4];
				__int32 i = 0;
				for (std::vector<Node>::iterator it = vtemp.begin(); it != vtemp.end(); it++, i++)
				{
					for (int j = 0; j < 4; j++)
						if (nodes[j] == *it)
						{
							queue[i] = j;
							j = 4;
						}
				}
				Triangle* tr;
				for (int i = 0; i < 4; i++)
				{
					if (queue[i] == 3)
					{
						tr = new Triangle(nodes[queue[i]], nodes[queue[(i + 1) % 4]], nodes[queue[(i + 2) % 4]]);
						result.push_back(tr);
						tr = new Triangle(nodes[queue[(i + 2) % 4]], nodes[queue[(i + 3) % 4]], nodes[queue[i]]);
						result.push_back(tr);
						i = 3;
					}
				}
			}
			else
			{
				// we connect first 3 nodes in one Triangle1
				// and connect the 4th node with the nearest 2 nodes in the second Triangle1

				Triangle* tr = new Triangle(nodes[0], nodes[1], nodes[2]);
				result.push_back(tr);
				float temp0 = length(&nodes[3], &nodes[0]);
				float temp1 = length(&nodes[3], &nodes[1]);
				float temp2 = length(&nodes[3], &nodes[2]);
				int min_1, min_2;
				if (min(temp0, temp1) == temp0)
				{
					min_1 = 0;
				}
				else min_1 = 1;
				if (min(temp1, temp2) == temp1)
				{
					min_2 = 1;
				}
				else min_2 = 2;
				if (min_1 == min_2)
				{
					if (min(temp0, temp2) == temp0)
					{
						min_2 = 0;
					}
					else
						min_2 = 2;
				}
				tr = new Triangle(nodes[3], nodes[min_1], nodes[min_2]);
				result.push_back(tr);
			}
		}
		else
		{
			// we just connect  all nodes with each other
			for (int i = 0; i < nodes.size(); i++)
			{
				Triangle temp(nodes[i], nodes[(i + 1) % 4], nodes[(i + 2) % 4]);
				if (isInside(nodes[(i + 3) % 4], temp.get_nodes(), 2))
				{
					Triangle* tr = new Triangle(nodes[(i + 3) % 4], nodes[i], nodes[(i + 1) % 4]);
					result.push_back(tr);
					tr = new Triangle(nodes[(i + 3) % 4], nodes[i], nodes[(i + 2) % 4]);
					result.push_back(tr);
					tr = new Triangle(nodes[(i + 3) % 4], nodes[(i + 1) % 4], nodes[(i + 2) % 4]);
					result.push_back(tr);
				}
			}
			/*Triangle* tr = new Triangle(nodes[0],nodes[1],nodes[2]);
			result.push_back(tr);
			tr = new Triangle(nodes[0],nodes[1],nodes[3]);
			result.push_back(tr);
			tr = new Triangle(nodes[0],nodes[2],nodes[3]);
			result.push_back(tr);
			tr = new Triangle(nodes[1],nodes[2],nodes[3]);
			result.push_back(tr);*/
		}
		return result;
	}

	vector<Node> devideEightNodes(vector<Node> &dots)
	{
		vector<Node> new_dots;
		float lastx = dots[0].x;

		for (vector<Node>::iterator it = dots.begin(); it != dots.end(); it++)
		{
			if ((*it).x < lastx)
				lastx = (*it).x;
		}

		while (new_dots.size() < 4)
		{
			for (auto it : dots)
			{
				if ((it.x < lastx + 20.0) && (it.x >= lastx))
					new_dots.push_back(it);
			}
			lastx = lastx + 20.0;
		}
		while (new_dots.size() > 4)
		{
			vector<Node>::iterator max = new_dots.begin();
			for (vector<Node>::iterator it = new_dots.begin(); it != new_dots.end(); it++)
			{
				if (max->x < it->x)
					max = it;
			}
			new_dots.erase(max);
		}
		for (vector<Node>::iterator chosen = new_dots.begin(); chosen != new_dots.end(); chosen++)
		{
			for (vector<Node>::iterator it = dots.begin(); it != dots.end(); it++)
			{
				if (*it == *chosen)
				{
					dots.erase(it);
					it = dots.end() - 1;
				}
			}
		}
		return new_dots;
	}


	vector<Node> devideTwelveNodes(std::vector<Node> &dots)
	{

		vector<Node> new_dots;
		float lastx = dots[0].x;

		for (vector<Node>::iterator it = dots.begin() + 1; it != dots.end(); it++)
		{
			if ((*it).x < lastx)
				lastx = (*it).x;
		}
		//new_dots.push_back(last);
		float step = 20.0;
		while (new_dots.size() < 3)
		{
			for (auto it : dots)
			{
				if ((it.x < lastx + step) && (it.x >= lastx))
					new_dots.push_back(it);
			}
			lastx = lastx + step;
		}
		while (new_dots.size() > 3)
		{
			vector<Node>::iterator max = new_dots.begin();
			for (vector<Node>::iterator it = new_dots.begin(); it != new_dots.end(); it++)
			{
				if (max->x < it->x)
					max = it;
			}
			new_dots.erase(max);
		}
		for (vector<Node>::iterator chosen = new_dots.begin(); chosen != new_dots.end(); chosen++)
		{
			for (vector<Node>::iterator it = dots.begin(); it != dots.end(); it++)
			{
				if (*it == *chosen)
				{
					dots.erase(it);
					it = dots.end() - 1;
				}
			}
		}
		return new_dots;
	}

	vector<Node>  devideToHalf(std::vector<Node> &dots)
	{
		unsigned n = dots.size() / 2;
		vector<Node> new_dots;
		float last;
		float step = 20.0;

		if (isVertical)
		{
			last = dots[0].x;
			for (vector<Node>::iterator it = dots.begin(); it != dots.end(); it++)
			{
				if ((*it).x < last)
					last = (*it).x;
			}
			while (new_dots.size() < n)
			{
				for (auto it : dots)
				{
					if ((it.x < last + step) && (it.x >= last))
						new_dots.push_back(it);
				}
				last = last + step;
			}
		}
		else
		{
			last = dots[0].y;
			for (vector<Node>::iterator it = dots.begin(); it != dots.end(); it++)
			{
				if ((*it).y < last)
					last = (*it).y;
			}
			while (new_dots.size() < n)
			{
				for (auto it : dots)
				{
					if ((it.y < last + step) && (it.y >= last))
						new_dots.push_back(it);
				}
				last = last + step;
			}
		}

		while (new_dots.size() > n)
		{
			vector<Node>::iterator max = new_dots.begin();
			for (vector<Node>::iterator it = new_dots.begin(); it != new_dots.end(); it++)
			{
				if (max->x < it->x)
					max = it;
			}
			new_dots.erase(max);
		}
		for (vector<Node>::iterator chosen = new_dots.begin(); chosen != new_dots.end(); chosen++)
		{
			for (vector<Node>::iterator it = dots.begin(); it != dots.end(); it++)
			{
				if (*it == *chosen)
				{
					dots.erase(it);
					it = dots.end() - 1;
				}
			}
		}
		isVertical = !isVertical;
		return new_dots;
	}



	void print(std::vector<Node> nodes)
	{
		for (vector<Node>::iterator it = nodes.begin(); it != nodes.end(); it++)
		{
			cout << (*it).x << " " << (*it).y << endl;
		}
		cout << "************" << endl;
	}


	void print(std::vector<Triangle*> trs)
	{
		for (vector<Triangle*>::iterator jt = trs.begin(); jt != trs.end(); jt++)
		{
			(*jt)->print();
			cout << endl;
		}
		cout << endl << "************" << endl;
	}

}