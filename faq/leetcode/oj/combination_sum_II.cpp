/* Leetcode: Given a collection of candidate numbers (C) and a target number (T), 
 * find all unique combinations in C where the candidate numbers sums to T.
 * Each number in C may only be used once in the combination.
 *
 * Note:
 * All numbers (including target) will be positive integers.
 * Elements in a combination (a1, a2, ..., ak) must be in non-descending order. 
 * (ie, a1 <= a2 <= ... <= ak).
 * The solution set must not contain duplicate combinations.
 * For example, given candidate set { 10, 1, 2, 7, 6, 1, 5 } and target 8, 
 * the solution set is: 
 * [1, 7] 
 * [1, 2, 5] 
 * [2, 6] 
 * [1, 1, 6] 
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 136ms for large dataset. 
class Solution {
public:
  vector<vector<int> > combinationSum2(vector<int> &num, int target) {
    sort(num.begin(), num.end());
    vector<vector<int> > result;
    vector<int> curr;
    helper(num, result, curr, target, 0);
    return result;
  }
  
  void helper(const vector<int>& num, vector<vector<int> >& result, 
	      vector<int> current, int target, size_t level) {
    if (target == 0) {
      result.push_back(current);
      return;
    }

    if (target < 0 || level == num.size())
      return;

    for (size_t i = level; i < num.size(); i++) { 
      /* Avoid duplicate combinations. 
       * This is exactly the same trick that is used in subset_dup.cpp
       * to generate subsets when input has duplicate elements. */
      if (i != level && num[i] == num[i - 1])
	continue;
      current.push_back(num[i]);
      helper(num, result, current, target - num[i], i + 1);
      current.pop_back();
    }

    // The following approach will only give combinations whose 
    // elements are unique. In the example given, the combination
    // of [1, 1, 6] will be skipped.
    /*
    helper(num, result, current, target, level + 1);
    if (level > 0 && num[level] == num[level - 1])
      return;

    current.push_back(num[level]);
    helper(num, result, current, target - num[level], level + 1);
    */


    // The following approach will give duplicate combinations
    /*
    helper(num, result, current, target, level + 1);
    current.push_back(num[level]);
    helper(num, result, current, target - num[level], level + 1);
    */
  }
};

int main() {
  int arr[] = { 10, 1, 2, 7, 6, 1, 5 };
  vector<int> num(arr, arr + sizeof(arr) / sizeof(int));
  int target = 8;

  Solution foo;
  vector<vector<int> > ret = foo.combinationSum2(num, target);
  for (size_t i = 0; i < ret.size(); i++) {
    for (size_t j = 0; j < ret[i].size(); j++) 
      cout << ret[i][j] << " ";
    cout << endl;
  }

  return 0;
}
