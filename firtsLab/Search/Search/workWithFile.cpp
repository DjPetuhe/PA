#include <fstream>
#include <vector>
#include <iostream>
#include "workWithFile.h"
using namespace std;

country workWithFile::readCountry(string directory)
{
	ifstream fileName(directory);
	if (fileName.is_open())
	{
		string buff;
		string countryName;
		getline(fileName, countryName);
		int amountOfRegions;
		fileName >> amountOfRegions;
		vector<string> regionsName(amountOfRegions);
		getline(fileName, buff);
		for (int i = 0; i < amountOfRegions; i++)
		{
			getline(fileName, regionsName[i]);
		}
		vector<vector<bool> > countryGraph(amountOfRegions, vector<bool>(amountOfRegions));
		for (int i = 0; i < amountOfRegions; i++)
		{
			for (int j = 0; j < amountOfRegions; j++)
			{
				int temp;
				fileName >> temp;
				countryGraph[i][j] = temp;
			}
		}
		return country(countryName, amountOfRegions, regionsName, countryGraph);
	}
	else
	{
		return country();
	}
}

void workWithFile::writeColored(string directory, country c)
{
	ofstream fileName(directory);
	if (fileName.is_open())
	{
		vector<string> regionsName = c.getRegionsName();
		vector<int> regionsColor = c.getRegionsColor();
		string tempColor;
		for (int i = 0; i < c.getAmountOfRegions(); i++)
		{
			if (regionsColor[i] == 1) { tempColor = "red"; }
			else if (regionsColor[i] == 2) { tempColor = "green"; }
			else if (regionsColor[i] == 3) { tempColor = "blue"; }
			else if (regionsColor[i] == 4) { tempColor = "yellow"; }
			else { tempColor = "empty"; }
			fileName << regionsName[i] << " -> " << tempColor << endl;
		}
	}
}

std::string workWithFile::askDirectory(string question)
{
	cout << question;
	string dir;
	cin >> dir;
	cout << endl;
	return dir;
}
