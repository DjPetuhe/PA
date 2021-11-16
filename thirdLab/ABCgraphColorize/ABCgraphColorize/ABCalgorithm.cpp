#include <random>
#include "ABCalgorithm.h"
using namespace std;

ColoredMap ABCalgorithm::findResult(ColoredMap uncoloredMap, int amountOfBees, int amountOfScouts)
{
	int amountOfForager = amountOfBees - amountOfScouts;
	vector<bool> visitedByScouts;
	vector<int> nectar;
	int temp = 0;
	for (int i = 0; i < uncoloredMap.getGraph().size(); i++)
	{
		visitedByScouts.push_back(false);
	}
	for (int i = 0; i < visitedByScouts.size(); i++)
	{
		nectar.push_back(-1);
	}
	for (int i = 0; i < amountOfScouts; i++)
	{
		int choosenNode = chooseFromNotVisited(visitedByScouts);
		if (choosenNode != -1)
		{
			nectar[choosenNode] = calculateNectar(uncoloredMap, choosenNode);
			//visitedByScouts[choosenNode] = true;
		}
		else
		{
			return uncoloredMap;
		}
	}
	while (!uncoloredMap.finished())
	{
		vector<int> indexes = getNotEmptyIndexes(nectar);
		int nectarSum = 0;
		for (int i = 0; i < amountOfScouts; i++)
		{
			if (i < indexes.size())
			{
				nectarSum += nectar[indexes[i]];
			}
		}
		for (int i = 0; i < amountOfScouts; i++)
		{
			if (i < indexes.size())
			{
				if (nectar[indexes[i]] > 0)
				{
					visitedByScouts[indexes[i]] = true;
					double p = (double)nectar[indexes[i]] / (double)nectarSum;
					int amountOfForagerInNode = amountOfForager * p;
					if (colorizeNode(amountOfForagerInNode, nectar[indexes[i]], indexes[i], uncoloredMap, nectar))
					{
						amountOfForager--;
						temp++;
					}
				}
				else if (nectar[indexes[i]] == 0)
				{
					colorizeNode(0, nectar[indexes[i]], indexes[i], uncoloredMap, nectar);
				}
			}
		}
		amountOfScouts += temp;
		temp = 0;
		for (int i = 0; i < amountOfScouts; i++)
		{
			int choosenNode = chooseFromNotVisited(visitedByScouts);
			if (choosenNode != -1)
			{
				nectar[choosenNode] = calculateNectar(uncoloredMap, choosenNode);
				//visitedByScouts[choosenNode] = true;
			}
			else
			{
				return uncoloredMap;
			}
		}
	}
	return uncoloredMap;
}

int ABCalgorithm::chooseFromNotVisited(std::vector<bool> visitedByScouts)
{
	int startedI = rand() % visitedByScouts.size();
	int i = startedI;
	do
	{
		if (visitedByScouts[i] == true)
		{
			i++;
		}
		if (i == visitedByScouts.size())
		{
			i = 0;
		}
	} while (!(visitedByScouts[i] == false || i == startedI));
	if (i == startedI && visitedByScouts[i] == true)
	{
		return -1;
	}
	return i;
}

int ABCalgorithm::calculateNectar(ColoredMap& uncoloredMap, int choosenNode)
{
	vector<bool> lineOfMatrix = uncoloredMap.getGraph()[choosenNode];
	vector<int> colors = uncoloredMap.getColors();
	int nectar = 0;
	for (int i = 0; i < lineOfMatrix.size(); i++)
	{
		if (lineOfMatrix[i] && !colors[i])
		{
			nectar++;
		}
	}
	return nectar;
}

std::vector<int> ABCalgorithm::getNotEmptyIndexes(std::vector<int>& nectar)
{
	vector<int> indexes;
	for (int i = 0; i < nectar.size(); i++)
	{
		if (nectar[i] != -1)
		{
			indexes.push_back(i);
		}
	}
	return indexes;
}

bool ABCalgorithm::colorizeNode(int amountOfForagerInNode, int& nectarOfCurrentNode, int index, ColoredMap& uncoloredMap, vector<int>& nectar)
{
	vector<bool> lineOfMatrix = uncoloredMap.getGraph()[index];
	vector<int> colors = uncoloredMap.getColors();
	for (int i = 0; i < amountOfForagerInNode; i++)
	{
		if (nectarOfCurrentNode == 0)
		{
			colors[index] = findPossibleColor(uncoloredMap, index);
			uncoloredMap.setColors(colors);
			changeNectar(index, nectar, uncoloredMap);
			nectarOfCurrentNode = -1;
			return true;
		}
		else
		{
			int j = 0;
			while (!(lineOfMatrix[j] && !colors[j]))
			{
				j++;
			}
			colors[j] = findPossibleColor(uncoloredMap, j);
			uncoloredMap.setColors(colors);
			changeNectar(j, nectar, uncoloredMap);
		}
	}
	if (nectarOfCurrentNode == 0)
	{
		colors[index] = findPossibleColor(uncoloredMap, index);
		uncoloredMap.setColors(colors);
		changeNectar(index, nectar, uncoloredMap);
		nectarOfCurrentNode = -1;
		return true;
	}
	uncoloredMap.setColors(colors);
	return false;
}

int ABCalgorithm::findPossibleColor(ColoredMap& uncoloredMap, int index)
{
	vector<bool> lineOfMatrix = uncoloredMap.getGraph()[index];
	vector<int> colors = uncoloredMap.getColors();
	vector<int> bannedColors;
	for (int i = 0; i < lineOfMatrix.size(); i++)
	{
		if (lineOfMatrix[i] && colors[i])
		{
			int colorNumber = colors[i];
			bannedColors.push_back(colorNumber);
		}
	}
	bool banned;
	int color = 0;
	do
	{
		banned = false;
		color++;
		for (int i = 0; i < bannedColors.size(); i++)
		{
			if (bannedColors[i] == color)
			{
				banned = true;
			}
		}
	} while (banned);
	if (uncoloredMap.getAmountOfColors() < color)
	{
		uncoloredMap.setAmountOfColors(color);
	}
	return color;
}

void ABCalgorithm::changeNectar(int index, std::vector<int>& nectar, ColoredMap& uncoloredMap)
{
	vector<bool> lineOfMatrix = uncoloredMap.getGraph()[index];
	for (int i = 0; i < lineOfMatrix.size(); i++)
	{
		if (lineOfMatrix[i] && nectar[i] != -1)
		{
			nectar[i] -= 1;
		}
	}
}
