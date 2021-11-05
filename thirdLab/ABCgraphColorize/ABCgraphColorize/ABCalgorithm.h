#include <vector>
#include "ColoredMap.h"
#pragma once

class ABCalgorithm
{
public:
	static ColoredMap findResult(ColoredMap uncoloredMap, int amountOfBees, int amountOfScouts);
	static int chooseFromNotVisited(std::vector<bool> visitedByScouts);
	static int calculateNectar(ColoredMap& uncoloredMap, int choosenNode);
	static std::vector<int> getNotEmptyIndexes(std::vector<int>& nectar);
	static bool colorizeNode(int amountOfForagerInNode, int& nectarOfCurrentNode, int index, ColoredMap& uncoloredMap, std::vector<int>& nectar);
	static int findPossibleColor(ColoredMap& uncoloredMap, int index);
	static void changeNectar(int index, std::vector<int>& nectar, ColoredMap& uncoloredMap);
};

