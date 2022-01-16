#include <iostream>
#include <string>
#include "workWithFile.h"
#include "country.h"
#include "Algo.h"
#include <time.h>
using namespace std;

int main()
{
	srand(time(NULL));
	string startDirectory = workWithFile::askString("\nEnter directory of file with country`s info:\n");
	string endDirectory = workWithFile::askString("\nEnter the file directory where to write results:\n");
	int type = stoi(workWithFile::askString("\nWhat do you want to use?:\n(0)Beam search\n(1)MRV\n"));
	country c = workWithFile::readCountry(startDirectory);
	clock_t start = clock();
	int amountOfIteration;
	int amountOfGeneratedStates;
	int amountOfFails;
	if (type)
	{
		Algo mrvAlgo(c, 0, start);
		c.setRegionsColor(mrvAlgo.mrv());
		amountOfIteration = mrvAlgo.getAmountOfIterations();
		amountOfGeneratedStates = mrvAlgo.getAmountOfGeneratedStates();
		amountOfFails = mrvAlgo.getAmountOfFails();
	}
	else
	{
		int amountOfBeams = stoi(workWithFile::askString("\nHow many beams would you like to use?:\n"));
		Algo beamAlgo(c, amountOfBeams, start);
		c.setRegionsColor(beamAlgo.beamSearch());
		amountOfIteration = beamAlgo.getAmountOfIterations();
		amountOfGeneratedStates = beamAlgo.getAmountOfGeneratedStates();
		amountOfFails = beamAlgo.getAmountOfFails();
	}
	if (c.getRegionsColor()[0] == -1)
	{
		cout << endl << "Program ran out of time or memory!" << endl;
	}
	else
	{
		workWithFile::writeColored(endDirectory, c, amountOfIteration, amountOfGeneratedStates, amountOfFails);
	}
}