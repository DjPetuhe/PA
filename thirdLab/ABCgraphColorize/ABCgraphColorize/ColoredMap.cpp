#include "ColoredMap.h"

ColoredMap::ColoredMap(std::vector<std::vector<bool>> newGraph)
{
	graph = newGraph;
	for (int i = 0; i < newGraph.size(); i++)
	{
		colors.push_back(0);
	}
	amountOfColors = 0;
}

int ColoredMap::getAmountOfColors()
{
	return amountOfColors;
}

void ColoredMap::setAmountOfColors(int newAmountOfColors)
{
	amountOfColors = newAmountOfColors;
}

std::vector<int> ColoredMap::getColors()
{
	return colors;
}

void ColoredMap::setColors(std::vector<int> newColors)
{
	colors = newColors;
}

std::vector<std::vector<bool>> ColoredMap::getGraph()
{
	return graph;
}

bool ColoredMap::finished()
{
	bool finished = true;
	for (int i = 0; i < colors.size(); i++)
	{
		if (!colors[i])
		{
			finished = false;
		}
	}
	return finished;
}

std::string ColoredMap::getColorName(int i)
{
	switch (i)
	{
	case 1:
		return "red";
	case 2:
		return "green";
	case 3:
		return "blue";
	case 4:
		return "yellow";
	case 5:
		return "brown";
	case 6:
		return "pink";
	case 7:
		return "violet";
	case 8:
		return "gray";
	case 9:
		return "orange";
	case 10:
		return "cyan";
	case 11:
		return "turquoise";
	case 12:
		return "biege";
	case 13:
		return "golden";
	case 14:
		return "coral";
	case 15:
		return "emerald";
	case 16:
		return "copper";
	case 17:
		return "olive";
	case 18:
		return "silver";
	case 19:
		return "khaki";
	case 20:
		return "lilac";
	default:
		return "out of colors :(";
	}
}
