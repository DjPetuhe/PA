#include "Tree.h"
using namespace std;

Tree::Tree(country newC)
{
	c = newC;
	root = Node::makeNode(newC.getRegionsColor());
}

int Tree::getHeuristic(Node* current)
{
	int heuristic = 0;
	vector<vector<bool> > graph = c.getCountryGraph();
	for (int i = 0; i < c.getAmountOfRegions(); i++) {
		for (int j = 0; j <= i; j++) {
			if (graph[i][j] == 1 && current->regionsColor[i] == current->regionsColor[j])
			{
				heuristic++;
			}

		}
	}
	return heuristic;
}

std::vector<int> Tree::ColorizeMap()
{
	return std::vector<int>();
}
