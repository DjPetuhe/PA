#include <vector>
#pragma once
class Population
{
	std::vector<std::vector<int>> graph;
	std::vector<int> bestOrder;
public:
	Population(std::vector<std::vector<int>> newGraph);
	std::vector<int> getOrder();
	void setOrder(std::vector<int> newBestOrder);
	std::vector<std::vector<int>> getGraph();
	int getLength();
};

