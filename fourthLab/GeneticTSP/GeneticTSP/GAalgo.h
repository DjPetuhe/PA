#include <vector>
#include "Population.h"
#pragma once

class GAalgo
{
	std::vector<std::vector<int>> graph;
	std::vector<std::vector<int>> generateStartPopulation(int sizeOfPopulation);
	std::vector<int> shuffleOrder(std::vector<int> order);
	std::vector<int> crossingOver(std::vector<int> firstParent, std::vector<int> secondParent, int TypeOfCrossingover);
	std::vector<int> generateCrossingOverPoints(int TypeOfCrossingover, int size);
	void generateTwoIndex(int& firstParentIndex, int& secondParentIndex, int sizeOfPopulation);
	void mutation(std::vector<int>& child, int mutationPercent, int TypeOfMutation);
	int calculateLength(std::vector<int> order);
	void sortPopulation(std::vector<std::vector<int>>& population);
public:
	GAalgo(std::vector<std::vector<int>> newGraph);
	Population findResult(Population unsolved, int TypeOfCrossingover, int TypeOfMutation, int TypeOfLocalImprovement);
};

