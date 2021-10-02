#include <iostream>
#include <string>
#include "workWithFile.h"
#include "country.h"
#include "BeamSearch.h"
using namespace std;

int main()
{
	string startDirectory = workWithFile::askDirectory("\nEnter directory of file with country`s info:\n");
	string endDirectory = workWithFile::askDirectory("\nEnter the file directory where to write results:\n");
	country check = workWithFile::readCountry(startDirectory);
	check.setRegionsColor(BeamSearch::ColorizeMap(check));
	workWithFile::writeColored(endDirectory,check);
}