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
		std::pair<int, std::string> bTreeSearch(int key);
	};
	Node* root;
	int t;
public:
	Btree(int newT);
	void dfsTraverse(bool toFile);
	std::pair<int,std::string> bTreeSearch(int key);
	void bTreeInsert(std::pair<int, std::string> newValue);
};

