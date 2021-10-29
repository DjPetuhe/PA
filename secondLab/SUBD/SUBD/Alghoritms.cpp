#include <vector>
#include <math.h>
#include "Alghoritms.h"
using namespace std;

vector<pair<int, string>> Alghoritms::generateRandomElements(int amount, int& amountOfElements)
{
    vector<pair<int, string>> newValues;
    string tempStr;
    pair<int, string> tempPair;
    for (int i = 0; i < amount; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (rand() % 2 == 0)
            {
                tempStr += rand() % 25 + 65;
            }
            else
            {
                tempStr += rand() % 25 + 97;
            }
        }
        amountOfElements++;
        tempPair.first = amountOfElements;
        tempPair.second = tempStr;
        newValues.push_back(tempPair);
        tempStr.clear();
    }
    return newValues;
}

vector<int> Alghoritms::ShuffleOrder(int amount)
{
    vector<int> shuffle(amount);
    for (int i = 0; i < amount; i++)
    {
        shuffle[i] = i;
    }
    for (int i = 0; i < amount; i++)
    {
        int j = rand() % amount;
        int k = shuffle[i];
        shuffle[i] = shuffle[j];
        shuffle[j] = k;
    }
    return shuffle;
}

pair<int, string> Alghoritms::sharrSearch(vector<pair<int, string>> &values, int realSize, int key, int& index)
{
    int k = log2(realSize);
    int i = pow(2,k);
    if (values[i - 1].first < key)
    {
        int l = log2(realSize - pow(2,k) + 1);
        i = realSize + 1 - pow(2, l);
        return homogeneousBinarySearch(values, key, i, l, realSize, index);
    }
    else if (values[i - 1].first > key)
    {
        return homogeneousBinarySearch(values, key, i, k, realSize, index);
    }
    else
    {
        index = i - 1;
        return values[i - 1];
    }
    return {};
}

std::pair<int, std::string> Alghoritms::homogeneousBinarySearch(std::vector<std::pair<int, std::string>>& values, int key, int i, int l, int realSize, int& index)
{
    vector<bool> visited;
    for (int j = 0; j < values.size(); j++)
    {
        visited.push_back(false);
    }
    int j = 1;
    int b;
    do
    {
        visited[i - 1] = true;
        b = pow(2, l - j);
        j++;
        if (values[i - 1].first < key)
        {
            i += (b / 2) + 1;
        }
        else if (values[i - 1].first > key)
        {
            i -= (b / 2) + 1;
        }
        else
        {
            index = i - 1;
            return values[i - 1];
        }
        if (i == 0)
        {
            index = 0;
            return pair<int, string>(-1, to_string(i + 1));
        }
        if (i == realSize + 1)
        {
            index = realSize;
            return pair<int, string>(-1, to_string(i - 1));
        }
    } while (key != values[i - 1].first && visited[i - 1] != true);
    if (values[i - 1].first == key)
    {
        index = i - 1;
        return values[i - 1];
    }
    else
    {
        index = i - 1;
        return pair<int, string>(-1,to_string(i));
    }
    return std::pair<int, std::string>();
}
