#pragma once
#include <string>
#include "country.h"
using namespace std;

class workWithFile
{
public:
	static country readCountry(std::string directory);
	static void writeColored(std::string directory, country c);
};
