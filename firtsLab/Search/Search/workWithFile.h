#pragma once
#include <string>
#include "country.h"

class workWithFile
{
public:
	static country readCountry(std::string directory);
	static void writeColored(std::string directory, country c);
	static std::string askString(std::string question);
};
