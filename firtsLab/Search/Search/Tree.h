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
		Node* parent;
		int heuristic;
		Node(std::vector<int> newRegionsColor) { parent = nullptr; regionsColor = newRegionsColor; childs.clear(); }
		static Node* makeNode(std::vector<int> newRegionsColor)
		{
			Node* n = new Node(newRegionsColor);
			n->regionsColor = newRegionsColor;
			n->childs.clear();
			n->parent = nullptr;
			return n;
		}
		static Node* makeNode(Node* newParent, std::vector<int> newRegionsColor)
		{
			Node* n = new Node(newRegionsColor);
			n->regionsColor = newRegionsColor;
			n->childs.clear();
			n->parent = newParent;
			return n;
		}
	};
	Node* root;
	country c;
	int amountOfBeams;
	int getHeuristic(Node* current);
	std::vector<int> randomStartingPoints();
	int IsMapColorized(std::vector<Node*> beams);
	void getAllPossibleNodes(std::vector<Node*>& allNodes, Node* current);
public:
	Tree(country newC, int newAmountOfBeams);
	std::vector<int> ColorizeMap();
};

