#include <fstream>
#include <vector>
#include <iostream>
#include "workWithFile.h"
using namespace std;

country workWithFile::readCountry(std::string directory)
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

void workWithFile::writeColored(std::string directory, country c)
{

}
