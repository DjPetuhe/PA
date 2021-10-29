#pragma once
#include <string>
#include "Btree.h"

class ConsoleMenu
{
	static int amountOfElements;
	static void addToBTree(int amount, Btree &tree);
	static void deleteBTreeElements(Btree &tree);
	static void printElementsToConsole(Btree &tree);
	static void findElement(Btree& tree, int key);
	static void deleteElement(Btree& tree, int key);
	static void editElement(Btree& tree, int key, std::string);
	static Btree readFile();
public:
	static void startMenu();
};

