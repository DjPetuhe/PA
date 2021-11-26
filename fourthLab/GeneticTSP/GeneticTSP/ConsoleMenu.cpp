#include <iostream>
#include <random>
#include <iomanip>
#include <string>
#include <fstream>
#include "ConsoleMenu.h"
#include "GAalgo.h"
using namespace std;

ConsoleMenu::ConsoleMenu(int newSizeOfGraph)
{
	this->sizeOfGraph = newSizeOfGraph;
	this->TypeOfCrossingover = 0;
	this->TypeOfMutation = 0;
	this->TypeOfLocalImprovement = 0;
}

void ConsoleMenu::startMenu()
{
	cout << "Do you want to:\n(0)generate graph randomly\n(1)read it from file" << endl;
	bool choise;
	cin >> choise;
	system("cls");
	vector<vector<int>> graph;
	if (!choise)
	{
		graph = generateRandom();
		if (this->sizeOfGraph <= 20)
		{
			printGraph(graph);
			system("pause");
			system("cls");
		}
		cout << "Do you want to save this graph to file?\n(0)no\n(1)yes\n";
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
	system("cls");
	cout << "Do you want to use:\n(0)One-point crossover\n(1)Two-point crossover\n(2)Three-point crossover\n" << endl;
	cin >> TypeOfCrossingover;
	system("cls");
	cout << "Do you want to use:\n(0)Swap mutation\n(1)Reverse mutation\n" << endl;
	cin >> TypeOfMutation;
	system("cls");
	cout << "Do you want to use:\n(0)Improvement in random point\n(1)Improvement in worst Point\n" << endl;
	cin >> TypeOfLocalImprovement;
	cout << "Finding path...\n";
	GAsolve(graph);
}

vector<vector<int>> ConsoleMenu::generateRandom()
{
	vector<vector<int>> graph(this->sizeOfGraph, vector<int>(this->sizeOfGraph));
	for (int i = 0; i < this->sizeOfGraph; i++)
	{
		for (int j = 0; j < this->sizeOfGraph; j++)
		{
			if (j == i)
			{
				graph[i][j] = 0;
			}
			else
			{
				graph[i][j] = 5 + rand() % 146;
			}
		}
	}
	return graph;
}

void ConsoleMenu::printGraph(vector<vector<int>>& graph)
{
	cout << "\nGenerated graph:\n";
	cout << "       ";
	for (int i = 0; i < this->sizeOfGraph; i++)
	{
		cout << setw(4) << i + 1;
	}
	cout << endl;
	cout << "       ";
	for (int i = 0; i < this->sizeOfGraph; i++)
	{
		cout << "____";
	}
	cout << "_" << endl;
	for (int i = 0; i < this->sizeOfGraph; i++)
	{
		cout << setw(5) << i + 1 << " | ";
		for (int j = 0; j < this->sizeOfGraph; j++)
		{
			cout << setw(4) << graph[i][j];
		}
		cout << endl;
	}
}

vector<vector<int>> ConsoleMenu::readFromFile()
{
	cout << "\nEnter file directory:\n";
	string dir;
	cin >> dir;
	ifstream file(dir);
	vector<vector<int>> graph(this->sizeOfGraph, vector<int>(this->sizeOfGraph));
	bool temp;
	if (file.is_open())
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
	else
	{
		cout << "\nCant open file :(\n";
		return {};
	}
	file.close();
	return graph;
}

void ConsoleMenu::printToFile(vector<vector<int>>& graph)
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
	file.close();
}

void ConsoleMenu::GAsolve(vector<vector<int>>& graph)
{
	Population unsolved(graph);
	Population bestResult(graph);
	Population result(graph);
	vector<int> lengthResults;
	for (int i = 0; i < 1000; i++)
	{
		GAalgo TSP(graph);
		result = TSP.findResult(unsolved, this->TypeOfCrossingover, this->TypeOfMutation, this->TypeOfLocalImprovement);
		if ((i == 0) || (result.getLength() < bestResult.getLength()))
		{
			bestResult = result;
		}
		lengthResults.push_back(bestResult.getLength());
		if ((i + 1) % 100 == 0 || i == 0)
		{
			cout << "\nIteration #" << setw(4) << i + 1 << " Length: " << bestResult.getLength();
		}
	}
	cout << "\n\nColorizing finihsed!";
	printResult(lengthResults, bestResult);
}

void ConsoleMenu::printResult(vector<int> lengths, Population bestResult)
{
	ofstream file("resutls.txt");
	file << "Best result after 1000 iterations:\n\n";
	file << "Length: " << bestResult.getLength() << '\n';
	file << "Path:\n";
	vector<int> order = bestResult.getOrder();
	for (int i = 0; i < order.size(); i++)
	{
		if (i != 0)
		{
			cout << "--->";
		}
		cout << "City#" << order[i] + 1;
	}
	cout << "--->City#" << order[0] + 1<< "\n\n";
	file << "\nBest results by iterations number: " << "\n\n";
	for (int i = 0; i < 1000; i++)
	{
		file << "iteration #" << setw(6) << i + 1 << " result: " << lengths[i] << '\n';
	}
	file.close();
}
