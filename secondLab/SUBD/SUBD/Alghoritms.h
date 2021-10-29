#pragma 
#include <vector>
#include <utility>
#include <string>

class Alghoritms
{
public:
	static std::vector<std::pair<int, std::string>> generateRandomElements(int amount, int& amountOfElements, int& lastNumber);
	static std::vector<int> ShuffleOrder(int amount);
	static std::pair<int, std::string> sharrSearch(std::vector<std::pair<int,std::string>> &values, int realSize, int key, int& index);
	static std::pair<int, std::string> homogeneousBinarySearch(std::vector<std::pair<int,std::string>> &values, int key, int i, int l, int realSize, int& index);
};

