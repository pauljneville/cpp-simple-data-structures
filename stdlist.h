#ifndef _STD_LIST_
#define _STD_LIST_

#include <list>
#include <string>
#include <iostream>

#include "container.h"

/** std::list encapsulated in StdList
 */
class StdList : public Container
{
	std::list<std::string> stdlist;
	std::list<std::string>::iterator iter;
	
public:
	StdList() : stdlist{}, iter{} {}
	void insert(std::string data) { if (!StdList::search(data)) stdlist.push_back(data); }
	bool search(std::string data) const;
	void print() const;
	
	void resetIter() { iter = stdlist.begin(); }
	bool validIter() const { return iter != stdlist.end() ? true : false; }
	std::string getIterData() const { return iter != stdlist.end() ? *iter : "INVALID ITERATOR"; }
	void incrIter() { ++iter; }
	
	~StdList() {}
};

#endif