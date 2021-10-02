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
	vector<vector<bool> > graph;
	for (int i = 0; i < c.getAmountOfRegions(); i++) {
		for (int j = 0; j <= i; j++) {
			if ([i][j] == 1 && regionList.at(i).color == regionList.at(j).color) {
				heuristic++;
				//cout << i + 1 << " & " << j +1<< " have same color";
			}

		}
		//cout << "\n";
	}
	return heuristic;
}

std::vector<int> Tree::ColorizeMap()
{
	return std::vector<int>();
}
