#include <iostream>
#include <random>
#include <iomanip>
#include <string>
#include <fstream>
#include "ConsoleMenu.h"
#include "ColoredMap.h"
#include "ABCalgorithm.h"
using namespace std;

ConsoleMenu::ConsoleMenu(int newSizeOfGraph, int newMaxPowerOfNodes, int newMinPowerOfNode, int newAmountOfBees, int newAmountOfScouts, int newBottomLineOfIterations, int newUpperLineOfIterations)
{
	this->sizeOfGraph = newSizeOfGraph;
	this->maxPowerOfNode = newMaxPowerOfNodes;
	this->minPowerOfNode = newMinPowerOfNode;
	this->amountOfBees = newAmountOfBees;
	this->amountOfScouts = newAmountOfBees;
	this->bottomLineOfIterations = newBottomLineOfIterations;
	this->upperLineOfIterations = newUpperLineOfIterations;
}

void ConsoleMenu::startMenu()
{
	cout << "Do you want to:\n(0)generate graph randomly\n(1)read it from file" << endl;
	bool choise;
	cin >> choise;
	system("cls");
	vector<vector<bool>> graph;
	if (choise)
	{
		graph = generateRandom();
		printGraph(graph);
		system("pause");
		system("cls");
		cout << "\nDo you want to save this graph to file?\n";
		cin >> choise;
		if (choise)
		{
			printToFile(graph);
		}
	}
	else
	{
		graph = readFromFile();
	}
	colorizeGraph(graph);
}

vector<vector<bool>> ConsoleMenu::generateRandom()
{
	vector<vector<bool>> graph(this->sizeOfGraph, vector<bool>(this->sizeOfGraph));
	for (int i = 0; i < this->sizeOfGraph; i++)
	{
		for (int j = 0; j < this->sizeOfGraph; j++)
		{
			graph[i][j] = 0;
		}
	}
	for (int i = 0; i < this->sizeOfGraph; i++)
	{
		int amountOfConnections = 0;
		for (int j = 0; j < this->sizeOfGraph; j++)
		{
			if (j <= i)
			{
				if (graph[i][j] == 1)
				{
					amountOfConnections++;
				}
			}
			else
			{
				if (!(rand() % 20) && amountOfConnections <= 20)
				{
					graph[i][j] = 1;
					graph[j][i] = 1;
				}
			}
		}
		if (amountOfConnections == 0)
		{
			int tempJ;
			int tempAmountOfConnectionsInJ;
			do
			{
				tempAmountOfConnectionsInJ = 0;
				tempJ = rand() % this->sizeOfGraph;
				for (int k = 0; k < this->sizeOfGraph; k++)
				{
					if (graph[tempJ][k] == 1)
					{
						tempAmountOfConnectionsInJ++;
					}
				}
			} while (tempAmountOfConnectionsInJ >= 20 || tempJ == i);
			graph[i][tempJ] = 1;
			graph[tempJ][i] = 1;
		}
	}
	return graph;
}

void ConsoleMenu::printGraph(vector<vector<bool>>& graph)
{
	cout << "\nGenerated graph:\n";
	cout << "       ";
	for (int i = 0; i < this->sizeOfGraph; i++)
	{
		cout << setw(4) << i;
	}
	for (int i = 0; i < this->sizeOfGraph; i++)
	{
		cout << setw(5) << i << " | ";
		for (int j = 0; j < this->sizeOfGraph; j++)
		{
			cout << setw(4) << graph[i][j];
		}
	}
}

vector<vector<bool>> ConsoleMenu::readFromFile()
{
	cout << "\nEnter file directory:\n";
	string dir;
	cin >> dir;
	ifstream file(dir);
	vector<vector<bool>> graph(this->sizeOfGraph,vector<bool>(this->sizeOfGraph));
	bool temp;
	if (file.is_open())
	{
		while (!file.eof())
		{
			for (int i = 0; i < this->sizeOfGraph; i++)
			{
				for (int j = 0; j < this->sizeOfGraph; j++)
				{
					file >> temp;
					graph[i][j] = temp;
				}
			}
		}
	}
	else
	{
		cout << "\nCant open file :(\n";
		return {};
	}
	return graph;
}

void ConsoleMenu::printToFile(vector<vector<bool>>& graph)
{
	cout << "\nEnter file directory:\n";
	string dir;
	cin >> dir;
	ofstream file(dir);
	bool temp;
	for (int i = 0; i < this->sizeOfGraph; i++)
	{
		for (int j = 0; j < this->sizeOfGraph; j++)
		{
			temp = graph[i][j];
			file << temp << " ";
		}
		file << '\n';
	}
}

void ConsoleMenu::colorizeGraph(std::vector<std::vector<bool>>& graph)
{
	ColoredMap uncoloredMap(graph);
	ColoredMap bestResult(graph);
	ColoredMap result(graph);
	vector<int> AmountOfColorResults;
	for (int i = 0; i < this->upperLineOfIterations; i++)
	{
		result = ABCalgorithm::findResult(uncoloredMap, this->amountOfBees, this->amountOfScouts);
		if ((i == 0) || (result.getAmountOfColors() < bestResult.getAmountOfColors()))
		{
			bestResult = result;
		}
		if (i >= this->bottomLineOfIterations)
		{
			AmountOfColorResults.push_back(bestResult.getAmountOfColors());
		}
	}
}
