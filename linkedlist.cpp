#include "linkedlist.h"

/** Inserts new node containing data argument if not already present
 * @param data, the value to insert into the list if not found
 */
void LinkedList::insert(std::string data)
{
	if (size == 0)
	{
		head = std::make_unique<Node>(data);
		iterator = head.get();
		++size;
		return;
	}
	
	// get the pointer held by the head unique_ptr
	Node* curNode = head.get();
	// check to see if data is already present
	for (int i = 0; i < size-1; ++i)
	{
		if (curNode->data.compare(data) == 0)
			return;
		
		curNode = curNode->next.get();
	}
	if (curNode->data.compare(data) == 0)
		return;
	
	curNode->next = std::make_unique<Node>(data);
	++size;
}

/** Returns true if data found in list, else false
 * @param data, a string to search for in list
 * @return true if found, false if not
 */
bool LinkedList::search(std::string data) const
{
	if (size == 0)
		return false;
	
	Node* curNode = head.get();
	for (int i = 0; i < size; ++i)
	{
		if (curNode->data.compare(data) == 0)
			return true;

		curNode = curNode->next.get();
	}

	return false;
}

/** Prints contents of LinkedList, start to finish
 */
void LinkedList::print() const
{
	Node* curNode = head.get();
	for (int i = 0; i < size; ++i)
	{
		std::cout << ":" << curNode->data << std::endl;
		curNode = curNode->next.get();
	}
	std::cout << "Number of elements: " << size << std::endl;
}