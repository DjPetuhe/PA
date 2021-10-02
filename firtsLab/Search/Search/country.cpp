#include "country.h"

country::country()
{
	this->countryName = "";
	this->amountOfRegions = 0;
	this->regionsName.clear();
	this->regionsColor.clear();
	this->countryGraph.clear();
}

country::country(std::string newName, int newAmountOfRegions, std::vector<std::string>& newRegionsName, std::vector<std::vector<bool>>& newCountryGraph)
{
	this->countryName = newName;
	this->amountOfRegions = newAmountOfRegions;
	this->regionsName = newRegionsName;
	this->countryGraph = newCountryGraph;
	this->regionsColor.resize(amountOfRegions);
	for (int i = 0; i < amountOfRegions; i++)
	{
		regionsColor[i] = 0;
	}
}

std::string country::getCountryName()
{
	return this->countryName;
}

void country::setCountryName(std::string newCountryName)
{
	this->countryName = newCountryName;
}

int country::getAmountOfRegions()
{
	return this->amountOfRegions;
}

void country::setAmountOfRegions(int newAmountOfRegions)
{
	this->amountOfRegions = newAmountOfRegions;
}

std::vector<std::string> country::getRegionsName()
{
	return this->regionsName;
}

void country::setRegionsName(std::vector<std::string> newRegionsName)
{
	this->regionsName = newRegionsName;
}

std::vector<std::vector<bool>> country::getCountryGraph()
{
	return this->countryGraph;
}

void country::setCountryGraph(std::vector<std::vector<bool>> newCountryGraph)
{
	this->countryGraph = newCountryGraph;
}

std::vector<int> country::getRegionsColor()
{
	return this->regionsColor;
}

void country::setRegionsColor(std::vector<int> newRegionsColor)
{
	this->regionsColor = newRegionsColor;
}
