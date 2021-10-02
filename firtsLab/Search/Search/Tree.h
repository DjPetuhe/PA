#pragma once
#include <vector>
#include "country.h"

class Tree
{
private:
	struct Node
	{
		std::vector<int> regionsColor;
		std::vector<Node*> childs;
		Node(std::vector<int> newRegionsColor) { regionsColor = newRegionsColor; childs.clear(); }
		static Node* makeNode(std::vector<int> newRegionsColor)
		{
			Node* n = new Node(newRegionsColor);
			n->regionsColor = newRegionsColor;
			n->childs.clear();
			return n;
		}
	};
	Node* root;
	country c;
	int getHeuristic(Node* current);
public:
	Tree(country newC);
	std::vector<int> ColorizeMap();
};

