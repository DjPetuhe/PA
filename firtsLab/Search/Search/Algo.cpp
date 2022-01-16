#include <random>
#include <queue>
#include <iostream>
#include <windows.h>
#include <psapi.h>
#include "Algo.h"
using namespace std;

Algo::Algo(country newC, int newAmountOfBeams, clock_t newStart)
{
	c = newC;
	amountOfBeams = newAmountOfBeams;
	amountOfIterations = 0;
	amountOfGeneratedStates = 0;
	amountOfFails = 0;
	amountOfColors = 4;
	start = newStart;
}

void Algo::generateNewStates(vector<Node>& beams)
{
	int currentSize = beams.size();
	for (int i = 0; i < currentSize; i++)
	{
		for (int j = 0; j < c.getCountryGraph().size(); j++)
		{
			for (int k = 0; k < amountOfColors; k++)
			{
				Node temp(beams[i], j, k + 1, c.getCountryGraph());
				beams.push_back(temp);
				amountOfGeneratedStates++;
			}
		}
	}
}

vector<Algo::Node> Algo::bestStates(vector<Node> beams)
{
	vector<Node> bestBeams;
	vector<int> bestBeamsIndexes;
	for (int i = 0; i < amountOfBeams; i++)
	{
		int minAmountOfConflicts = INT_MAX;
		int tempIndex;
		for (int j = 0; j < beams.size(); j++)
		{
			bool used = false;
			for (int k = 0; k < bestBeamsIndexes.size(); k++)
			{
				if (j == bestBeamsIndexes[k])
				{
					used = true;
				}
			}
			if (beams[j].amountOfConflicts < minAmountOfConflicts && !used)
			{
				minAmountOfConflicts = beams[j].amountOfConflicts;
				tempIndex = j;
			}
		}
		bestBeams.push_back(beams[tempIndex]);
		bestBeamsIndexes.push_back(tempIndex);
	}
	return bestBeams;
}

std::vector<int> Algo::beamSearch()
{
	Node startNode;
	startNode.generateRandomColors(c.getCountryGraph());
	amountOfGeneratedStates++;
	bool finished = false;
	bool colored = false;
	vector<Node> beams;
	beams.push_back(startNode);
	Node result;
	int amountOfConflictsThisStep = startNode.amountOfConflicts;
	int amountOfConflictsPreviousStep = startNode.amountOfConflicts;
	int timer = 0;
	while (!finished)
	{
		generateNewStates(beams);
		beams = bestStates(beams);
		if (beams[0].amountOfConflicts == 0 && !finished)
		{
			finished = true;
			colored = true;
			result = beams[0];
		}
		amountOfConflictsThisStep = beams[0].amountOfConflicts;
		if (amountOfConflictsThisStep == amountOfConflictsPreviousStep)
		{
			timer++;
		}
		else
		{
			timer = 0;
		}
		amountOfConflictsPreviousStep = amountOfConflictsThisStep;
		if (timer > 1000)
		{
			finished = true;
			colored = false;
			amountOfFails++;
		}
		amountOfIterations++;
	}
	if (!colored)
	{
		PROCESS_MEMORY_COUNTERS_EX pmc;
		K32GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
		SIZE_T TotalMemUsed = pmc.WorkingSetSize;
		int time = (((double)clock() - start) / ((double)CLOCKS_PER_SEC));
		if ((TotalMemUsed < 5000000000) && time < 1800)
		{
			cout << "Total time spend (in seconds): " << time << "\nReload beam search #" << amountOfFails << endl;
			return this->beamSearch();
		}
		else
		{
			cout << endl << "?" << TotalMemUsed << endl;
			vector<int> error;
			error.push_back(-1);
			return error;
		}
	}
	else
	{
		return result.colors;
	}
}

bool Algo::findMRVIndexes(Node& current, vector<int>& mrvIndexes)
{
	vector<vector<bool>> graph = c.getCountryGraph();
	int minMRVCount = INT_MAX;
	for (int i = 0; i < graph.size(); i++)
	{
		if (!current.colors[i])
		{
			vector<bool> emptyColors;
			for (int j = 0; j < amountOfColors + 1; j++)
			{
				emptyColors.push_back(true);
			}
			for (int j = 0; j < graph.size(); j++)
			{
				if (graph[i][j])
				{
					if (current.colors[j])
					{
						emptyColors[current.colors[j]] = false;
					}
				}
			}
			int mrvCount = 0;
			for (int j = 1; j < emptyColors.size(); j++)
			{
				if (emptyColors[j])
				{
					mrvCount++;
				}
			}
			if (mrvCount == minMRVCount)
			{
				mrvIndexes.push_back(i);
			}
			if (mrvCount < minMRVCount)
			{
				minMRVCount = mrvCount;
				mrvIndexes.clear();
				mrvIndexes.push_back(i);
			}
		}
	}
	return minMRVCount == 0 ? true : false;
}

bool Algo::colorizeRandom(Node& current, std::vector<int> mrvIndexes)
{
	int choosen = rand() % mrvIndexes.size();
	vector<vector<bool>> graph = c.getCountryGraph();
	vector<bool> EmptyColors;
	for (int i = 0; i < amountOfColors + 1; i++)
	{
		EmptyColors.push_back(true);
	}
	for (int i = 0; i < graph.size(); i++)
	{
		if (graph[choosen][i])
		{
			EmptyColors[current.colors[i]] = false;
		}
	}
	for (int i = 1; i < EmptyColors.size(); i++)
	{
		if (EmptyColors[i])
		{
			current.colors[mrvIndexes[choosen]] = i;
			return false;
		}
	}
	return true;
}

bool Algo::isFinished(Node& current)
{
	for (int i = 0; i < current.colors.size(); i++)
	{
		if (!current.colors[i])
		{
			return false;
		}
	}
	return true;
}

std::vector<int> Algo::mrv()
{
	Node current(c.getCountryGraph().size());
	amountOfGeneratedStates++;
	bool finished = false;
	bool restart = false;
	while (!finished && !restart)
	{
		amountOfIterations++;
		vector<int> mrvIndexes;
		restart = findMRVIndexes(current, mrvIndexes);
		restart = colorizeRandom(current, mrvIndexes);
		if (isFinished(current))
		{
			finished = true;
		}
	}
	if (restart)
	{
		amountOfFails++;
		PROCESS_MEMORY_COUNTERS_EX pmc;
		K32GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
		SIZE_T TotalMemUsed = pmc.WorkingSetSize;
		int time = (((double)clock() - start) / ((double)CLOCKS_PER_SEC));
		if ((TotalMemUsed < 500000000) && time < 1800)
		{
			cout << "Reload mrv # " << amountOfFails << endl;
			return this->mrv();
		}
	}
	else
	{
		return current.colors;
	}
}

int Algo::getAmountOfIterations()
{
	return amountOfIterations;
}

int Algo::getAmountOfGeneratedStates()
{
	return amountOfGeneratedStates;
}

int Algo::getAmountOfFails()
{
	return amountOfFails;
}
