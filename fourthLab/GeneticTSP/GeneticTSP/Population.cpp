#include "Population.h"

Population::Population(std::vector<std::vector<int>> newGraph)
{
	this->graph = newGraph;
	this->bestOrder.resize(newGraph.size());
}

std::vector<int> Population::getOrder()
{
	return this->bestOrder;
}

void Population::setOrder(std::vector<int> newBestOrder)
{
	this->bestOrder = newBestOrder;
}

std::vector<std::vector<int>> Population::getGraph()
{
	return this->graph;
}

int Population::getLength()
{
	int length = 0;
	for (int i = 0; i < this->bestOrder.size() - 1; i++)
	{
		length += graph[bestOrder[i]][bestOrder[i + 1]];
	}
	length += graph[bestOrder[bestOrder.size() - 1]][bestOrder[0]];
	return length;
}
