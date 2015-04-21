/* Leetcode OJ: Write a function to find the longest common 
 * prefix string amongst an array of strings. */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 32ms for large dataset
class Solution {
public:
  string longestCommonPrefix(vector<string> &strs) {
    string ret;
    if (!strs.size())
      return ret;

    if (strs.size() == 1)
      return strs[0];

    string foo = strs[0];
    for (size_t i = 0; i < foo.size(); i++) {
      char c = foo[i];
      for (size_t j = 1; j < strs.size(); j++) {
	if (strs[j].size() == i || c != strs[j][i])
	  return ret;
      }
      ret.push_back(c);
    }

    return ret;
  }

};
