#ifdef TRIANGULAION_EXPORTS
#define TRIALGULATION_API __declspec(dllexport) 
#else
#define TRIALGULATION_API __declspec(dllimport) 
#endif

#include <vector>

namespace Triangulation
{
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
			if ((i < (int)nodes.size()) && (i >= 0))
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

	TRIALGULATION_API  std::vector<Triangle*> TriangulationDelone(std::vector<Node> nodes);

}