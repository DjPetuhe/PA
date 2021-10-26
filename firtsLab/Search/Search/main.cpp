#include <iostream>
#include <string>
#include "workWithFile.h"
#include "country.h"
#include "Tree.h"
using namespace std;

int main()
{
	string startDirectory = workWithFile::askString("\nEnter directory of file with country`s info:\n");
	string endDirectory = workWithFile::askString("\nEnter the file directory where to write results:\n");
	int amountOfBeams = stoi(workWithFile::askString("\nHow many beams would you like to use?:\n"));
	country check = workWithFile::readCountry(startDirectory);
	Tree Beam(check, amountOfBeams);
	check.setRegionsColor(Beam.ColorizeMap());
	workWithFile::writeColored(endDirectory,check);
}