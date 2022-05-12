#include "stdmultiset.h"

/** Returns true if data found in StdMultiset, else false
 *
 * @param data, a string to search
 * @return true if found, false if not
 */
bool StdMultiset::search(std::string data) const
{
	for (auto x : stdmultiset)
	{
		if (x.compare(data) == 0)
			return true;
	}
	return false;
}

/** Prints contents of StdMultiset, start to finish
 */
void StdMultiset::print() const
{
	for (auto x : stdmultiset)
		std::cout << ":" << x << std::endl;
}


