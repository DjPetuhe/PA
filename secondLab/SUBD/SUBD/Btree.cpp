#include "Btree.h"
#include "Alghoritms.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

Btree::Btree(int newT)
{
	root = nullptr;
	t = newT;
}

void Btree::dfsTraverse(bool toFile)
{
	if (root != nullptr)
	{
		root->dfsTraverse(toFile);
	}
}

pair<int, string> Btree::bTreeSearch(int key)
{
	if (root == nullptr)
	{
		return pair<int,string>();
	}
	else
	{
		return root->bTreeSearch(key);
	}
}

void Btree::bTreeInsert(pair<int, string> newValue)
{
	if (root == nullptr)
	{
		root = new Node(t, true);
		root->values[0] = newValue;
		root->realSize = 1;
	}
	else
	{
		if (root->realSize == 2 * t - 1)
		{
			Node* temp = new Node(t, false);
			temp->childs[0] = root;
			temp->bTreeSplitChild(0, root);
			int i = 0;
			if (temp->values[0].first < newValue.first)
			{
				i++;
			}
			temp->childs[i]->bTreeInsertNonfull(newValue);
			root = temp;
		}
		else
		{
			root->bTreeInsertNonfull(newValue);
		}
	}
}

Btree::Node::Node(int newT, bool newLeaf)
{
	t = newT;
	leaf = newLeaf;
	childs.resize(2 * t);
	values.resize(2 * t - 1);
	realSize = 0;
}	

void Btree::Node::bTreeSplitChild(int i, Node* y)
{
	Node* z = new Node(y->t, y->leaf);
	z->realSize = this->t - 1;
	for (int j = 0; j < this->t - 1; j++)
	{
		z->values[j] = y->values[j + t];
	}
	if (y->leaf == false)
	{
		for (int j = 0; j < t; j++)
		{
			z->childs[j] = y->childs[j + t];
		}
	}
	y->realSize = t - 1;
	for (int j = this->realSize; j >= i + 1; j--)
	{
		this->childs[j + 1] = this->childs[j];
	}
	this->childs[i + 1] = z;
	for (int j = this->realSize - 1; j >= i; j--)
	{
		this->values[j + 1] = this->values[j];
	}
	values[i] = y->values[t - 1];
	this->realSize += 1;
}

void Btree::Node::bTreeInsertNonfull(std::pair<int, std::string> newValue)
{
	int i = this->realSize - 1;
	if (leaf == true)
	{
		while (i >= 0 && this->values[i].first > newValue.first)
		{
			this->values[i + 1] = values[i];
			i--;
		}
		this->values[i + 1] = newValue;
		this->realSize += 1;
	}
	else
	{
		while (i >= 0 && this->values[i].first > newValue.first)
		{
			i--;
		}
		if (this->childs[i + 1]->realSize == 2 * t - 1)
		{
			bTreeSplitChild(i+1, this->childs[i+1]);
			if (this->values[i + 1].first < newValue.first)
			{
				i++;
			}
		}
		this->childs[i + 1]->bTreeInsertNonfull(newValue);
	}
}

void Btree::Node::dfsTraverse(bool toFile)
{
	int i;
	for (i = 0; i < this->realSize; i++)
	{
		if (this->leaf == false)
		{
			this->childs[i]->dfsTraverse(toFile);
		}
		if (toFile)
		{
			ofstream file("database.txt", ios::app);
			if (file.is_open())
			{
				string temp = to_string(this->values[i].first) + " " + this->values[i].second + '\n';
				file << temp;
			}
			file.close();
		}
		else
		{
			cout << "key: " << setw(5) << this->values[i].first << " value: " << this->values[i].second << '\n';
		}
	}
	if (this->leaf == false)
	{
		this->childs[i]->dfsTraverse(toFile);
	}
}

pair<int,string> Btree::Node::bTreeSearch(int key)
{
	pair<int, string> returnment = Alghoritms::sharrSearch(this->values, this->realSize, key);
	if (returnment.first == -1)
	{
		if (leaf == true)
		{
			return pair<int, string>(-1, "");
		}
		else
		{
			if (values[stoi(returnment.second) - 1].first > key)
			{
				return this->childs[stoi(returnment.second) - 1]->bTreeSearch(key);
			}
			else
			{
				return this->childs[stoi(returnment.second)]->bTreeSearch(key);
			}
		}

	}
	else
	{
		return returnment;
	}
}
