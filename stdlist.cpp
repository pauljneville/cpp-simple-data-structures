#include "stdlist.h"

/** Returns true if data found in StdList, else false
 *
 * @param data, a string
 * @return true if found, false if not
 */
bool StdList::search(std::string data) const
{
	for (auto x : stdlist)
	{
		if (x.compare(data) == 0)
			return true;
	}
	return false;
}

/** Prints contents of StdList, start to finish
 */
void StdList::print() const
{
	for (auto x : stdlist)
		std::cout << ":" << x << std::endl;
}




