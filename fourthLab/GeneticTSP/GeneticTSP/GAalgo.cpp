#include <algorithm>
#include "GAalgo.h"
using namespace std;

GAalgo::GAalgo(std::vector<std::vector<int>> newGraph)
{
	graph = newGraph;
}

vector<vector<int>> GAalgo::generateStartPopulation(int sizeOfPopulation)
{
	vector<vector<int>> popul(sizeOfPopulation, vector<int>(graph.size()));
	for (int i = 0; i < graph.size(); i++)
	{
		popul[0][i] = i;
	}
	for (int i = 1; i < sizeOfPopulation; i++)
	{
		popul[i] = shuffleOrder(popul[0]);
	}
	return popul;
}

std::vector<int> GAalgo::shuffleOrder(std::vector<int> order)
{
	for (int i = 0; i < order.size(); i++)
	{
		order[i] = i;
	}
	for (int i = 0; i < order.size(); i++)
	{
		int j = rand() % order.size();
		int k = order[i];
		order[i] = order[j];
		order[j] = k;
	}
	return order;
}

vector<int> GAalgo::crossingOver(std::vector<int> firstParent, std::vector<int> secondParent, int TypeOfCrossingover)
{
	int size = firstParent.size();
	vector<int> child;
	vector<bool> usedCities;
	vector<int> crossingoverPoints = generateCrossingOverPoints(TypeOfCrossingover, size);
	int parentIterator = 0;
	int pointsIterator = 0;
	for (int i = 0; i < size; i++)
	{
		usedCities.push_back(false);
	}
	while (child.size() < size)
	{
		if (parentIterator == size - 1)
		{
			for (int i = 0; i < firstParent.size(); i++)
			{
				if (usedCities[firstParent[i]] == false)
				{
					child.push_back(firstParent[i]);
				}
			}
		}
		else
		{
			if (pointsIterator % 2 == 0)
			{
				if (usedCities[firstParent[parentIterator]] == false)
				{
					child.push_back(firstParent[parentIterator]);
					usedCities[firstParent[parentIterator]] = true;
				}
			}
			else
			{
				if (usedCities[secondParent[parentIterator]] == false)
				{
					child.push_back(secondParent[parentIterator]);
					usedCities[secondParent[parentIterator]] = true;
				}
			}
			parentIterator++;
			if (pointsIterator < TypeOfCrossingover + 1)
			{
				if (child.size() > crossingoverPoints[pointsIterator])
				{
					pointsIterator++;
				}
			}
		}
	}
	return child;
}

std::vector<int> GAalgo::generateCrossingOverPoints(int TypeOfCrossingover, int size)
{
	int amountOfPoints = TypeOfCrossingover + 1;
	vector<int> point(amountOfPoints);
	for (int i = 0; i < amountOfPoints; i++)
	{
		if (i == 0)
		{
			point[i] = rand() % (size - amountOfPoints);
		}
		else
		{
			point[i] = point[i - 1] + rand() % (size - (amountOfPoints + point[i - 1]));
		}
	}
	return point;
}

void GAalgo::generateTwoIndex(int& firstParentIndex, int& secondParentIndex, int sizeOfPopulation)
{
	firstParentIndex = rand() % sizeOfPopulation;
	secondParentIndex = rand() % sizeOfPopulation;
	while (firstParentIndex == secondParentIndex)
	{
		secondParentIndex = rand() % sizeOfPopulation;
	}
}

void GAalgo::mutation(vector<int>& child, int mutationChance, int TypeOfMutation)
{
	if (rand() % 100 < mutationChance)
	{
		vector<int> mutatedChild;
		if (TypeOfMutation == 0)
		{
			int firstIndex, secondIndex;
			generateTwoIndex(firstIndex, secondIndex, child.size());
			mutatedChild = child;
			mutatedChild[firstIndex] = child[secondIndex];
			mutatedChild[secondIndex] = child[firstIndex];
		}
		else
		{
			for (int i = 0; i < child.size(); i++)
			{
				mutatedChild.push_back(child[child.size() - i - 1]);
			}
		}
		if (calculateLength(mutatedChild) < calculateLength(child))
		{
			child = mutatedChild;
		}
	}
}

int GAalgo::calculateLength(vector<int> order)
{
	int length = 0;
	vector<int> temp;
	for (int i = 0; i < order.size() - 1; i++)
	{
		length += graph[order[i]][order[i + 1]];
	}
	length += graph[order[order.size() - 1]][order[0]];
	return length;
}

void GAalgo::sortPopulation(vector<vector<int>>& population)
{
	for (int i = 0; i < population.size(); i++)
	{
		int indexOfBest = 0;
		for (int j = 0; j < population.size(); j++)
		{
			if (calculateLength(population[indexOfBest]) < calculateLength(population[j]))
			{
				indexOfBest = j;
			}
		}
		vector<int> temp = population[i];
		population[i] = population[indexOfBest];
		population[indexOfBest] = temp;
	}
}

void GAalgo::localImprovement(std::vector<int>& child, int TypeOfLocalImprovement)
{
	if (TypeOfLocalImprovement)
	{
		int worst = 0;
		for (int i = 0; i < child.size() - 1; i++)
		{
			if (graph[child[i]][child[i + 1]] > graph[child[worst]][child[worst + 1]])
			{
				worst = i;
			}
		}
		int lowerWorst;
		int upperWorst;
		if (worst < 5)
		{
			lowerWorst = 0;
			upperWorst = worst + 5;
		}
		else if (worst > 294)
		{
			upperWorst = 299;
			lowerWorst = worst - 5;
		}
		else
		{
			lowerWorst = worst - 5;
			upperWorst = worst + 5;
		}
		vector<int> temp;
		for (int i = 0; i < upperWorst - lowerWorst; i++)
		{
			temp.push_back(child[i]);
		}
		vector<int> improved = improve(temp);
		if (calculateLength(improved) < calculateLength(temp))
		{
			int j = 0;
			for (int i = lowerWorst; i < upperWorst; i++)
			{
				child[i] = improved[j];
				j++;
			}
		}
	}
	else
	{
		int lowerWorst = rand() % (child.size() - 11);
		int upperWorst = lowerWorst + 10;
		vector<int> temp;
		for (int i = 0; i < upperWorst - lowerWorst; i++)
		{
			temp.push_back(child[i]);
		}
		vector<int> improved = improve(temp);
		if (calculateLength(improved) < calculateLength(temp))
		{
			int j = 0;
			for (int i = lowerWorst; i < upperWorst; i++)
			{
				child[i] = improved[j];
				j++;
			}
		}
	}
}

std::vector<int> GAalgo::improve(std::vector<int> part)
{
	vector<int> newPart;
	vector<bool> notUsed;
	for (int i = 0; i < part.size(); i++)
	{
		notUsed.push_back(true);
	}
	newPart.push_back(part[0]);
	for (int i = 0; i < part.size() - 1; i++)
	{
		int temp = 0;
		for (int j = i; j < part.size() - 1; j++)
		{
			if (graph[newPart[i]][part[j]] < graph[newPart[i]][temp] && notUsed[j] == true)
			{
				temp = j;
			}
		}
		notUsed[temp] = false;
		newPart.push_back(temp);
	}
	newPart.push_back(part[part.size() - 1]);
	return newPart;
}

Population GAalgo::findResult(Population unsolved, int TypeOfCrossingover, int TypeOfMutation, int TypeOfLocalImprovement)
{
	int sizeOfPopulation = 10;
	int amountOfGenerations = 50;
	int mutationPercent = 10;
	int firstParentIndex, secondParentIndex;
	vector<vector<int>> popul = generateStartPopulation(sizeOfPopulation);
	while (amountOfGenerations > 0)
	{
		generateTwoIndex(firstParentIndex, secondParentIndex, sizeOfPopulation);
		vector<int> firstChild = crossingOver(popul[firstParentIndex], popul[secondParentIndex], TypeOfCrossingover);
		vector<int> secondChild = crossingOver(popul[secondParentIndex], popul[firstParentIndex], TypeOfCrossingover);
		if (TypeOfMutation < 2)
		{
			mutation(firstChild, mutationPercent, TypeOfMutation);
			mutation(secondChild, mutationPercent, TypeOfMutation);
		}
		if (TypeOfLocalImprovement < 2)
		{
			localImprovement(firstChild, TypeOfLocalImprovement);
			localImprovement(secondChild, TypeOfLocalImprovement);
		}
		sortPopulation(popul);
		while (popul.size() > sizeOfPopulation)
		{
			popul.pop_back();
		}
		amountOfGenerations--;
	}
	unsolved.setOrder(popul[0]);
	return unsolved;
}
