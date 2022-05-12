#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>

#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

#include "container.h"

using namespace std;

/** Utility methods used for edit distance calculations
 */
int min(int x, int y);
int min(int x, int y, int z);
int max(int x, int y);
int editDistance(const std::string& s1, const std::string& s2);

