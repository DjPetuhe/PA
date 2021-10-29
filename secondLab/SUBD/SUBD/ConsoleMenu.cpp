#include <iostream>
#include <fstream>
#include "ConsoleMenu.h"
#include "Alghoritms.h"
using namespace std;

void ConsoleMenu::addToBTree(int amount, Btree &tree)
{
	vector<pair<int, string>> elements = Alghoritms::generateRandomElements(amount, amountOfElements);
	vector<int> order = Alghoritms::ShuffleOrder(amount);
	for (int i = 0; i < amount; i++)
	{
		tree.bTreeInsert(elements[order[i]]);
	}
	tree.dfsTraverse(true);
}

void ConsoleMenu::deleteBTreeElements(Btree &tree)
{
	Btree newTree(10);
	tree = newTree;
	std::ofstream file("database.txt", std::ofstream::out | std::ofstream::trunc);
	file.close();
	amountOfElements = 0;
}

void ConsoleMenu::printElementsToConsole(Btree &tree)
{
	tree.dfsTraverse(false);
}

void ConsoleMenu::findElement(Btree& tree, int key)
{
	pair<int, string> searchedElement = tree.bTreeSearch(key);
	if (searchedElement.first == -1)
	{
		cout << "Searched element wasnt found!\n";
	}
	else
	{
		cout << "Searched element:\nkey: " << searchedElement.first << " value: " << searchedElement.second << endl;
	}
}

void ConsoleMenu::deleteElement(Btree& tree, int key)
{

}

void ConsoleMenu::editElement(Btree& tree, int key, std::string)
{
	bool deleted = tree.
}

Btree ConsoleMenu::readFile()
{
	Btree tree(10);
	ifstream file("database.txt");
	int tempKey;
	string tempStr;
	pair<int, string> tempValue;
	if (file.is_open() && !(file.peek() == ifstream::traits_type::eof()))
	{
		while (!file.eof())
		{
			file >> tempKey;
			file >> tempStr;
			tempValue.first = tempKey;
			tempValue.second = tempStr;
			if (!file.eof())
			{
				tree.bTreeInsert(tempValue);
				amountOfElements++;
			}
		}
	}
	file.close();
	return tree;
}

void ConsoleMenu::startMenu()
{
	Btree tree = readFile();
	int tempChoose = -1;
	do
	{
		system("cls");
		cout << "Current database has: " << amountOfElements << " elements\n\n";
		cout << "Enter number of action:\n(1)Add random elements\n(2)Delete all elements\n(3)Print all elements\n(4)Find element\n(5)Delete element\n(6)Edit element\n(7)Exit\n";
		cin >> tempChoose;
		system("cls");
		if (tempChoose == 1)
		{
			int tempAmount;
			cout << "How many elements would you like to add?\n";
			cin >> tempAmount;
			system("cls");
			addToBTree(tempAmount, tree);
			cout << "Elements were added!\n";
			system("pause");
		}
		else if (tempChoose == 2)
		{
			deleteBTreeElements(tree);
			cout << "All elements were deleted!\n";
			system("pause");
		}
		else if (tempChoose == 3)
		{
			printElementsToConsole(tree);
			system("pause");
		}
		else if (tempChoose == 4)
		{
			int tempKey;
			cout << "Enter the key of sought element:\n";
			cin >> tempKey;
			system("cls");
			findElement(tree, tempKey);
			system("pause");
		}
		else if (tempChoose == 5)
		{
			int tempKey;
			cout << "Enter the key of the element, that you want to remove:\n";
			cin >> tempKey;
			system("cls");
			deleteElement(tree, tempKey);
			system("pause");
		}
		else if (tempChoose == 6)
		{
			int tempKey;
			string tempStr;
			cout << "Enter the key of the element, that you want to edit:\n";
			cin >> tempKey;
			cout << "\nEnter the new value of the element:\n";
			cin >> tempStr;
			editElement(tree, tempKey, tempStr);
		}
	} while (tempChoose != 7);
}
