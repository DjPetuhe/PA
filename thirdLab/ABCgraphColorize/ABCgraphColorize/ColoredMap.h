#include <vector>
#pragma once

class ColoredMap
{
public:
	ColoredMap(std::vector<std::vector<bool>> newGraph);
	int getAmountOfColors();
};

