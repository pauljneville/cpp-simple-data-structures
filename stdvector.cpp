#include "stdvector.h"

/** Returns true if data found in StdVector, else false
 *
 * @param data, a string
 * @return true if found, false if not
 */
bool StdVector::search(std::string data) const
{
	for (auto x : stdvect)
	{
		if (x.compare(data) == 0)
			return true;
	}
	return false;
}

/** Prints contents of StdVector, start to finish
 */
void StdVector::print() const
{
	for (auto x : stdvect)
		std::cout << ":" << x << std::endl;
}