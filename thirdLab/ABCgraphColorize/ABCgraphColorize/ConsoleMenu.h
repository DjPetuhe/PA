#include <vector>
#include "ColoredMap.h"
#pragma once

class ConsoleMenu
{
	int sizeOfGraph;
	int maxPowerOfNode;
	int minPowerOfNode;
	int amountOfBees;
	int amountOfScouts;
	int bottomLineOfIterations;
	int upperLineOfIterations;
	std::vector<std::vector<bool>> generateRandom();
	void printGraph(std::vector<std::vector<bool>>& graph);
	std::vector<std::vector<bool>> readFromFile();
	void printToFile(std::vector<std::vector<bool>>& graph);
	void colorizeGraph(std::vector<std::vector<bool>>& graph);
	void printResult(std::vector<int> AmountOfColors, ColoredMap bestResult);
public:
	ConsoleMenu(int newSizeOfGraph, int newMaxPowerOfNodes, int newMinPowerOfNode, int newAmountOfBees, int newAmountOfScouts, int newBottomLineOfIterations, int newUpperLineOfIterations);
	void startMenu();
};

