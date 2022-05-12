#ifndef _STD_MULTISET_
#define _STD_MULTISET_

#include <iostream>
#include <string>
#include <set>

#include "container.h"

/** std::multiset encapsulated in StdMultiset
 */
class StdMultiset : public Container
{
	std::multiset<std::string> stdmultiset;
	std::multiset<std::string>::iterator iter;
	
public:
	StdMultiset() : stdmultiset{}, iter{} {}
	void insert(std::string data) { if (!StdMultiset::search(data)) stdmultiset.insert(data); }
	bool search(std::string data) const;
	void print() const;
	
	void resetIter() { iter = stdmultiset.begin(); }
	bool validIter() const { return iter != stdmultiset.end() ? true : false; }
	std::string getIterData() const { return iter != stdmultiset.end() ? *iter : "INVALID ITERATOR"; }
	void incrIter() { ++iter; }
	
	~StdMultiset() {}
};

#endif