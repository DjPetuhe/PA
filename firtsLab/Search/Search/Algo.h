#pragma once
#include <vector>
#include "country.h"
#include <time.h>

class Algo
{
private:
	struct Node
	{
		std::vector<int> colors;
		int amountOfConflicts;
		Node()
		{
			colors.clear();
			amountOfConflicts = 0;
		}
		Node(int size)
		{
			colors.clear();
			for (int i = 0; i < size; i++)
			{
				colors.push_back(0);
			}
			amountOfConflicts = 0;
		}
		Node(Node old, int numberOfNode, int changeToColor, std::vector<std::vector<bool>> graph)
		{
			colors = old.colors;
			colors[numberOfNode] = changeToColor;
			amountOfConflicts = 0;
			for (int i = 0; i < graph.size(); i++)
			{
				for (int j = i; j < graph.size(); j++)
				{
					if (graph[i][j] && colors[i] == colors[j])
					{
						amountOfConflicts++;
					}
				}
			}
		}
		void generateRandomColors(std::vector<std::vector<bool>> graph)
		{
			for (int i = 0; i < graph.size(); i++)
			{
				colors.push_back(rand() % 4 + 1);
			}
			for (int i = 0; i < graph.size(); i++)
			{
				for (int j = i; j < graph.size(); j++)
				{
					if (graph[i][j] && colors[i] == colors[j])
					{
						amountOfConflicts++;
					}
				}
			}
		}
	};
	country c;
	int amountOfBeams;
	int amountOfIterations;
	int amountOfGeneratedStates;
	int amountOfFails;
	int amountOfColors;
	clock_t start;

	void generateNewStates(std::vector<Node>& beams);
	std::vector<Node> bestStates(std::vector<Node> beams);
	bool findMRVIndexes(Node& current, std::vector<int>& mrvIndexes);
	bool colorizeRandom(Node& current, std::vector<int> mrvIndexes);
	bool isFinished(Node& current);
public:
	Algo(country newC, int newAmountOfBeams, clock_t);
	std::vector<int> beamSearch();
	std::vector<int> mrv();
	int getAmountOfIterations();
	int getAmountOfGeneratedStates();
	int getAmountOfFails();
};

