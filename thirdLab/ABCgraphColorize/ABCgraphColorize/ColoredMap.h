#include <vector>
#include <string>
#include <vector>
#pragma once

class ColoredMap
{
	std::vector<std::vector<bool>> graph;
	std::vector<int> colors;
	int amountOfColors;
public:
	ColoredMap(std::vector<std::vector<bool>> newGraph);
	int getAmountOfColors();
	void setAmountOfColors(int newAmountOfColors);
	std::vector<int> getColors();
	void setColors(std::vector<int> newColors);
	std::vector<std::vector<bool>> getGraph();
	bool finished();
	static std::string getColorName(int i);
};

