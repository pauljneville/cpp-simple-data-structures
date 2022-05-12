#ifndef _CONTAINER_
#define _CONTAINER_

/** abstract Container class for use of polymorphism in data structure functions
 */
class Container
{
public:
	virtual void insert(std::string data) = 0;
	virtual bool search(std::string data) const = 0;
	virtual void print() const = 0;
	
	virtual void resetIter() = 0;
	virtual bool validIter() const = 0;
	virtual std::string getIterData() const = 0;
	virtual void incrIter() = 0;
	
	virtual ~Container() {}
};

class ContainerIter
{
	std::string getData() const { return "INVALID ITERATOR"; }
	
	void operator++() { }
	bool operator==(const ContainerIter& b) const { return true; }
	bool operator!=(const ContainerIter& b) const { return false; }
};

#endif