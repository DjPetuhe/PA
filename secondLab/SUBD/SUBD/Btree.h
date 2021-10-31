#pragma once
#include <vector>
#include <utility>
#include <string>

class Btree
{
	struct Node {
		std::vector<std::pair<int, std::string>> values;
		std::vector<Node*> childs;
		int t;
		int realSize;
		bool leaf;
		Node(int newT, bool newLeaf);
		void bTreeSplitChild(int i, Node* current);
		void bTreeInsertNonfull(std::pair<int, std::string> newValue);
		void dfsTraverse(bool toFile);
		std::pair<int, std::string> bTreeSearch(int key, std::string& newValue, int& comparisons);
		bool bTreeDelete(int key);
		void bTreeRemoveFromLeaf(int index);
		void bTreeRemoveFromNonLeaf(int index);
		void fill(int index);
		std::pair<int, std::string> getPredecessor(int index);
		std::pair<int, std::string> getSuccessor(int index);
		void borrowFromPrevious(int index);
		void borrowFromNext(int index);
		void merge(int index);
	};
	Node* root;
	int t;
public:
	Btree(int newT);
	void dfsTraverse(bool toFile);
	std::pair<int,std::string> bTreeSearch(int key, std::string& newValue, int& comparisons);
	void bTreeInsert(std::pair<int, std::string> newValue);
	bool bTreeDelete(int key);
};

