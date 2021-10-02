#pragma once
#include <string>
#include "country.h"

class workWithFile
{
public:
	static country readCountry(std::string directory);
	static void writeColored(std::string directory, country c);
	static std::string askDirectory(std::string question);
};
