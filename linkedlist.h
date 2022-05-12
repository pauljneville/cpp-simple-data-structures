#ifndef _CUSTOM_LINKED_LIST_
#define _CUSTOM_LINKED_LIST_

#include <iostream>
#include <string>
#include <memory>

#include "container.h"

/** Singly linked list
 */
class LinkedList : public Container
{
	class Node
	{
	public:
		std::string data;
		std::unique_ptr<Node> next;
		
		Node(std::string data_) : data{data_}, next{nullptr} {}
		friend class LinkedList;
	};
	class Iterator : public ContainerIter
	{
		Node* iterator;
	public:
		Iterator(Node* iter) : iterator{iter} {}
		std::string getData() const { return iterator != nullptr ? iterator->data : "INVALID ITERATOR"; }

		void operator++() { if (iterator != nullptr) iterator = iterator->next.get(); }
		bool operator==(const LinkedList::Iterator& b) const { return (*this).iterator == b.iterator; }
		bool operator!=(const LinkedList::Iterator& b) const { return !((*this) == b); }
	};
	
	std::unique_ptr<Node> head;
	int size;
	
	Iterator iterator;
	
public:
	LinkedList() : head{nullptr}, size{0}, iterator{nullptr} {}
	void insert(std::string data);
	bool search(std::string data) const;
	void print() const;
	
	void resetIter() { iterator = LinkedList::begin(); }
	bool validIter() const { return iterator != LinkedList::end(); }
	std::string getIterData() const { return iterator.getData(); }
	void incrIter() { ++iterator; }
	
	LinkedList::Iterator begin() const { return Iterator(head.get()); }
	LinkedList::Iterator end() const { return nullptr; }
	
	~LinkedList() {}
};

#endif
		
		
		
