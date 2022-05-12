#ifndef _STD_VECTOR_
#define _STD_VECTOR_

#include <iostream>
#include <string>
#include <vector>

#include "container.h"

/** std::vector encapsulated in StdVector
 */
class StdVector : public Container
{
	std::vector<std::string> stdvect;
	std::vector<std::string>::iterator iter;
	
public:
	StdVector() : stdvect{}, iter{} {}
	void insert(std::string data) { if (!StdVector::search(data)) stdvect.push_back(data); }
	bool search(std::string data) const;
	void print() const;
	
	void resetIter() { iter = stdvect.begin(); }
	bool validIter() const { return iter != stdvect.end() ? true : false; }
	std::string getIterData() const { return iter != stdvect.end() ? *iter : "INVALID ITERATOR"; }
	void incrIter() { ++iter; }
	
	~StdVector() {}
};

#endif