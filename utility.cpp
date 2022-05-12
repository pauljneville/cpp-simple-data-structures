#include "utility.h"


/** Returns minimum of two ints
 *
 * @param x an integer
 * @param y an integer
 * @return the smaller integer either x or y
 */
int min(int x, int y)
{
	if (x < y)
		return x;
	else
		return y;
}

/** Returns minimum of three ints
 *
 * @param x an integer
 * @param y an integer
 * @param z an integer
 * @return the smaller integer either x, y or z
 */
int min(int x, int y, int z)
{
	return min(min(x, y), z);
}

/** Returns maximum of two ints
 *
 * @param x an integer
 * @param y an integer
 * @return the larger integer either x, y
 */
int max(int x, int y)
{
	if (x > y)
		return x;
	else
		return y;
}

/** Calculates the edit distance of two strings
 *
 * @param s1 a string
 * @param s2 a string
 * @return the value representing the  minimum number of operations
 * 		   (swap, delete, insert) of characters to match the strings
 */
int editDistance(const std::string& s1, const std::string& s2)
{
	if (s1.size() == 0)
		return s2.size();
	if (s2.size() == 0)
		return s1.size();
	
	const int rowLen = s1.size() + 1;
	const int colLen = s2.size() + 1;
	
	// edit distance value matrix
	std::vector<std::vector<int>> editDist(colLen, std::vector<int>(rowLen));

	editDist[0][0] = 0;
	for (int i = 1; i < rowLen; ++i)
	{
		editDist[0][i] = i;
	}
	for (int i = 1; i < colLen; ++i)
	{
		editDist[i][0] = i;
	}

	for (int i = 1; i < colLen; ++i)
	{
		for (int j = 1; j < rowLen; ++j)
		{
			if (s1[j-1] == s2[i-1])
				editDist[i][j] = editDist[i-1][j-1];
			else
			{
				editDist[i][j] = 1 + min(editDist[i][j-1], // insert
										 editDist[i-1][j], // remove
										 editDist[i-1][j-1]); // replace
			}
		}
	}
	
	/*cout << endl;
	cout << ' ' << ' ' << '0' << ' ';
	for (int i = 0; i < rowLen; ++i)
	{
		cout << s1[i] << ' ';
	}
	cout << endl;
	cout << '0' << ' ';
	for (int i = 0; i < rowLen; ++i)
	{
		cout << editDist[0][i] << ' ';
	}
	cout << endl;
	// print edit distance matrix
	for (int i = 1; i < colLen; ++i)
	{
		cout << s2[i-1];
		for (int j = 0; j < rowLen; ++j)
		{
			cout << ' ' << editDist[i][j];
		}
		cout << endl;
	}*/
	
	return editDist[colLen-1][rowLen-1];
}



	
	
	
	


























