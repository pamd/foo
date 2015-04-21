/* Leetcode OJ: Given a collection of numbers, return all possible permutations.
 * For example, [1,2,3] have the following permutations:
 * [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].
 */

// 84ms for large dataset
class Solution {
public:
  vector<vector<int> > permute(vector<int> &num) {
    vector<vector<int> > result;
    vector<bool> used(num.size(), false);
    vector<int> tmp(num);
    size_t level = 0;
    helper(num, tmp, result, level, used);
    return result;
  }

  // Recursive helper function
  void helper(const vector<int>& num, vector<int> &tmp, vector<vector<int> >& result, 
	      size_t level, vector<bool>& used) {
    if (level == num.size()) {
      result.push_back(tmp);
      return;
    }

    for (size_t i = 0; i < used.size(); i++) {
      if (used[i] == false) {
	tmp[level] = num[i];
	used[i] = true;
	helper(num, tmp, result, level + 1, used);
	used[i] = false;
      }	
    }
  }
};
