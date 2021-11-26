#include <vector>
#include "Population.h"
#pragma once

class ConsoleMenu
{
	int sizeOfGraph;
	int TypeOfCrossingover;
	int TypeOfMutation;
	int TypeOfLocalImprovement;
	std::vector<std::vector<int>> generateRandom();
	void printGraph(std::vector<std::vector<int>>& graph);
	std::vector<std::vector<int>> readFromFile();
	void printToFile(std::vector<std::vector<int>>& graph);
	void GAsolve(std::vector<std::vector<int>>& graph);
	void printResult(std::vector<int> AmountOfColors, Population bestResult);
public:
	ConsoleMenu(int newSizeOfGraph);
	void startMenu();
};

