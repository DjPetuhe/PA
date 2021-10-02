#include <iostream>
#include <string>
#include "workWithFile.h"
#include "country.h"
using namespace std;

int main()
{
	string s;
	cin >> s;
	country check = workWithFile::readCountry(s);

}