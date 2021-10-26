#pragma once
#include <string>
#include <vector>

class country
{
private:
	std::string countryName;
	int amountOfRegions;
	std::vector<std::string> regionsName;
	std::vector<std::vector<bool> > countryGraph;
	std::vector<int> regionsColor;
public:
	country();
	country(std::string newCountryName, int newAmountOfRegions, std::vector<std::string>& newRegionsName, std::vector<std::vector<bool> >& newCountryGraph);
	std::string getCountryName();
	void setCountryName(std::string newCountryName);
	int getAmountOfRegions();
	void setAmountOfRegions(int newAmountOfRegions);
	std::vector<std::string> getRegionsName();
	void setRegionsName(std::vector<std::string> newRegionsName);
	std::vector<std::vector<bool> > getCountryGraph();
	void setCountryGraph(std::vector<std::vector<bool> > newCountryGraph);
	std::vector<int> getRegionsColor();
	void setRegionsColor(std::vector<int> newRegionsColor);
};
