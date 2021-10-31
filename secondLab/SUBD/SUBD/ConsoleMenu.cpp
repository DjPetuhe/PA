#include <iostream>
#include <fstream>
#include "ConsoleMenu.h"
#include "Alghoritms.h"
using namespace std;

void ConsoleMenu::addToBTree(int amount, Btree &tree)
{
	vector<pair<int, string>> elements = Alghoritms::generateRandomElements(amount, amountOfElements, lastNumber);
	vector<int> order = Alghoritms::ShuffleOrder(amount);
	for (int i = 0; i < amount; i++)
	{
		tree.bTreeInsert(elements[order[i]]);
	}
	ofstream file("database.txt", ofstream::out | ofstream::trunc);
	file.close();
	tree.dfsTraverse(true);
}

void ConsoleMenu::deleteBTreeElements(Btree &tree)
{
	Btree newTree(10);
	tree = newTree;
	ofstream file("database.txt", ofstream::out | ofstream::trunc);
	file.close();
	amountOfElements = 0;
	lastNumber = 0;
}

void ConsoleMenu::printElementsToConsole(Btree &tree)
{
	tree.dfsTraverse(false);
}

void ConsoleMenu::findElement(Btree& tree, int key)
{
	string buf;
	int comparisons = 0;
	pair<int, string> searchedElement = tree.bTreeSearch(key, buf, comparisons);
	if (searchedElement.first == -1)
	{
		cout << "Searched element wasnt found!\n";
		cout << "Amount of comparisons: " << comparisons << endl;
	}
	else
	{
		cout << "Searched element:\nkey: " << searchedElement.first << " value: " << searchedElement.second << endl;
		cout << "Amount of comparisons: " << comparisons << endl;
	}
}

void ConsoleMenu::deleteElement(Btree& tree, int key)
{
	bool deleted = tree.bTreeDelete(key);
	if (!deleted)
	{
		cout << "There is no element with such key!" << endl;
	}
	else
	{
		cout << "Element has been succesefully deleted!" << endl;
		amountOfElements--;
		ofstream file("database.txt", ofstream::out | ofstream::trunc);
		file.close();
		tree.dfsTraverse(true);
	}
}

void ConsoleMenu::editElement(Btree& tree, int key, string newValue)
{
	int buf = 0;
	pair<int, string> editedElement = tree.bTreeSearch(key, newValue, buf);
	if (editedElement.first == -1)
	{
		cout << "The element you wanted to edit wasnt found!\n";
	}
	else
	{
		cout << "Element was edited:\nkey: " << editedElement.first << " new value: " << editedElement.second << endl;
		ofstream file("database.txt", ofstream::out | ofstream::trunc);
		file.close();
		tree.dfsTraverse(true);
	}
}

Btree ConsoleMenu::readFile()
{
	Btree tree(10);
	ifstream file("database.txt");
	int tempKey = 0;
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
	if (tempKey != 0)
	{
		lastNumber = tempKey;
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
			system("cls");
			editElement(tree, tempKey, tempStr);
			system("pause");
		}
	} while (tempChoose != 7);
}
