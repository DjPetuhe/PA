#include <random>
#include <queue>
#include "Tree.h"
using namespace std;

Tree::Tree(country newC, int newAmountOfBeams)
{
	c = newC;
	root = Node::makeNode(newC.getRegionsColor());
	amountOfBeams = newAmountOfBeams;
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

std::vector<int> Tree::randomStartingPoints()
{
	int temp;
	bool repeat;
	vector<int> randomStarts;
	for (int i = 0; i < amountOfBeams; i++)
	{
		do
		{
			repeat = false;
			temp = rand() % c.getAmountOfRegions();
			for (int j = 0; j < randomStarts.size(); j++)
			{
				if (temp == randomStarts[j])
				{
					repeat = true;
				}
			}
		} while (repeat);
		randomStarts.push_back(temp);
	}
	return randomStarts;
}

int Tree::IsMapColorized(std::vector<Node*> beams)
{
	for (int i = 0; i < amountOfBeams; i++)
	{
		if (beams[i]->heuristic == 0)
		{
			return i;
		}
	}
	return -1;
}

void Tree::getAllPossibleNodes(std::vector<Node*>& allNodes, Node* current)
{

}

std::vector<int> Tree::ColorizeMap()
{
	vector<int> indexes = randomStartingPoints();
	queue<Node*> q;
	for (int i = 0; i < amountOfBeams; i++)
	{
		vector<int> tempRegionsColor;
		for (int j = 0; j < c.getAmountOfRegions(); j++)
		{
			tempRegionsColor.push_back(0);
		}
		tempRegionsColor[indexes[i]] = 1;
		root->childs.push_back(Node::makeNode(root,tempRegionsColor));
	}
	for (int i = 0; i < root->childs.size(); i++)
	{
		q.push(root->childs[i]);
	}
	bool finished = false;
	while (!finished)
	{
		vector<Node*> allNodes;
		Node* current = q.front();
		q.pop();

	}
	return indexes;
}
