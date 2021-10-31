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

pair<int, string> Btree::bTreeSearch(int key, string& newValue, int& comparisons)
{
	if (root == nullptr)
	{
		return pair<int,string>(-1, "");
	}
	else
	{
		return root->bTreeSearch(key, newValue, comparisons);
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

bool Btree::bTreeDelete(int key)
{
	if (!root)
	{
		return false;
	}
	bool deleted = root->bTreeDelete(key);
	if (root->realSize == 0)
	{
		Node* temp = root;
		if (root->leaf)
		{
			root = NULL;
		}
		else
		{
			root = root->childs[0];
		}
		delete temp;
	}
	return deleted;
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
	if (!y->leaf)
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
	this->values[i] = y->values[t - 1];
	this->realSize += 1;
}

void Btree::Node::bTreeInsertNonfull(pair<int, string> newValue)
{
	int i = this->realSize - 1;
	if (this->leaf)
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
		if (!this->leaf)
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
	if (!this->leaf)
	{
		this->childs[i]->dfsTraverse(toFile);
	}
}

pair<int,string> Btree::Node::bTreeSearch(int key, string& newValue, int& comparisons)
{
	int index;
	pair<int, string> returnment = Alghoritms::sharrSearch(this->values, this->realSize, key, index, comparisons);
	if (returnment.first == -1)
	{
		if (this->leaf)
		{
			return pair<int, string>(-1, "");
		}
		else
		{
			if (this->values[stoi(returnment.second) - 1].first > key)
			{
				return this->childs[stoi(returnment.second) - 1]->bTreeSearch(key, newValue, comparisons);
			}
			else
			{
				return this->childs[stoi(returnment.second)]->bTreeSearch(key, newValue, comparisons);
			}
		}

	}
	else
	{
		if (newValue.empty())
		{
			return returnment;
		}
		else
		{
			returnment.second = newValue;
			this->values[index] = returnment;
			return returnment;
		}
	}
}

bool Btree::Node::bTreeDelete(int key)
{
	int index;
	int buf = 0;
	pair<int, string> returnment = Alghoritms::sharrSearch(this->values, this->realSize, key, index, buf);
	if (returnment.first != -1)
	{
		if (this->leaf)
		{
			bTreeRemoveFromLeaf(index);
		}
		else
		{
			bTreeRemoveFromNonLeaf(index);
		}

	}
	else
	{
		if (this->leaf)
		{
			return false;
		}
		bool last = false;
		if (index == this->realSize)
		{
			last = true;
		}
		if (this->childs[index]->realSize < t)
		{
			fill(index);
		}
		if (last && index > this->realSize)
		{
			this->childs[index - 1]->bTreeDelete(key);
		}
		else
		{
			this->childs[index]->bTreeDelete(key);
		}
	}
	return true;
}

void Btree::Node::bTreeRemoveFromLeaf(int index)
{
	for (int i = index + 1; i < this->realSize; i++)
	{
		this->values[i - 1] = this->values[i];
	}
	realSize--;
}

void Btree::Node::bTreeRemoveFromNonLeaf(int index)
{
	int key = this->values[index].first;
	if (this->childs[index]->realSize >= t)
	{
		pair<int,string> predecessor = getPredecessor(index);
		this->values[index] = predecessor;
		this->childs[index]->bTreeDelete(predecessor.first);
	}
	else if (this->childs[index + 1]->realSize >= t)
	{
		pair<int,string> successor = getSuccessor(index);
		this->values[index] = successor;
		this->childs[index + 1]->bTreeDelete(successor.first);
	}
	else
	{
		merge(index);
		this->childs[index]->bTreeDelete(key);
	}
}

void Btree::Node::fill(int index)
{
	if (index != 0 && this->childs[index - 1]->realSize >= t)
	{
		borrowFromPrevious(index);
	}
	else if (index != this->realSize && this->childs[index + 1]->realSize >= t)
	{
		borrowFromNext(index);
	}
	else
	{
		if (index != this->realSize)
		{
			merge(index);
		}
		else
		{
			merge(index - 1);
		}
	}
}

pair<int, string> Btree::Node::getPredecessor(int index)
{
	Node* current = this->childs[index];
	while (!current->leaf)
	{
		current = current->childs[current->realSize];
	}
	return current->values[current->realSize - 1];
}

pair<int, string> Btree::Node::getSuccessor(int index)
{
	Node* current = childs[index + 1];
	while (!current->leaf)
	{
		current = current->childs[0];
	}
	return current->values[0];
}

void Btree::Node::borrowFromPrevious(int index)
{
	Node* child = this->childs[index];
	Node* sibling = this->childs[index - 1];
	for (int i = child->realSize - 1; i >= 0; --i)
	{
		child->values[i + 1] = child->values[i];
	}
	if (!child->leaf)
	{
		for (int i = child->realSize; i >= 0; --i)
		{
			child->childs[i + 1] = child->childs[i];
		}
	}
	child->values[0] = this->values[index - 1];
	if (!child->leaf)
	{
		child->childs[0] = sibling->childs[sibling->realSize];
	}
	this->values[index - 1] = sibling->values[sibling->realSize - 1];
	child->realSize += 1;
	sibling->realSize -= 1;
}

void Btree::Node::borrowFromNext(int index)
{
	Node* child = this->childs[index];
	Node* sibling = this->childs[index + 1];
	child->values[child->realSize] = this->values[index];
	if (!child->leaf)
	{
		child->childs[child->realSize + 1] = sibling->childs[0];
	}
	this->values[index] = sibling->values[0];
	for (int i = 1; i < sibling->realSize; ++i)
	{
		sibling->values[i - 1] = sibling->values[i];
	}
	if (!sibling->leaf)
	{
		for (int i = 1; i <= sibling->realSize; ++i)
		{
			sibling->childs[i - 1] = sibling->childs[i];
		}
	}
	child->realSize += 1;
	sibling->realSize -= 1;
}

void Btree::Node::merge(int index)
{
	Node* child = this->childs[index];
	Node* sibling = this->childs[index + 1];
	child->values[t - 1] = this->values[index];
	for (int i = 0; i < sibling->realSize; ++i)
	{
		child->values[i + t] = sibling->values[i];
	}
	if (!child->leaf)
	{
		for (int i = 0; i <= sibling->realSize; i++)
		{
			child->childs[i + t] = sibling->childs[i];
		}
	}
	for (int i = index + 1; i < this->realSize; ++i)
	{
		this->values[i - 1] = this->values[i];
	}
	for (int i = index + 2; i <= this->realSize; ++i)
	{
		this->childs[i - 1] = this->childs[i];
	}
	child->realSize += sibling->realSize + 1;
	realSize--;
	delete (sibling);
}
