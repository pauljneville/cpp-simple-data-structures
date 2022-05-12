#ifndef _CUSTOM_TREE_
#define _CUSTOM_TREE_

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <stack>
#include <random>

#include "container.h"

using namespace std;

/** Treap, min heap binary search tree
 * Heap value randomized on input, high probability of
 * producing near balanced tree on any insertion
 */
class Tree : public Container
{
	class Node
	{
		
	public:
		int treap;
		std::string data;
		int count;
		std::unique_ptr<Node> left;
		std::unique_ptr<Node> right;
		
		Node(std::string data_) : data{data_}, count{1}, left{nullptr}, right{nullptr} 
		{ 
			treap = getRandomTreapValue();
		}
		friend class Tree;
	};
	
	std::unique_ptr<Node> root;
	
	// used by iterator functions to perform dfs traversal
	std::vector<Node*> iterVector;
	
	// random number generator for treap values
	static int getRandomTreapValue()
	{
		int low = 1;
		int high = std::numeric_limits<int>::max();
		
		static std::default_random_engine re {};
		using std_UID = std::uniform_int_distribution<int>;
		static  std_UID uniformIntDistr{};
		return uniformIntDistr(re, std_UID::param_type{low, high});
	}
	
public:
	Tree() : root{nullptr}, iterVector{} { }
	void insert(std::string data);
	bool search(std::string data) const;
	void print() const;
	
	void resetIter() { iterVector.clear(); iterVector.push_back(root.get()); }
	bool validIter() const { return !iterVector.empty(); }
	std::string getIterData() const;
	void incrIter();
	
	void rotateLeft(std::unique_ptr<Node>& node);
	void rotateRight(std::unique_ptr<Node>& node);
	
	~Tree() {}
};

#endif