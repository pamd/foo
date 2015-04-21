/* Leetcode OJ: Given a set of candidate numbers (C) and a target number (T), 
 * find all unique combinations in C where the candidate numbers sums to T.
 * The same repeated number may be chosen from C unlimited number of times.
 * 
 * Note: All numbers (including target) will be positive integers.
 * Elements in a combination (a1, a2, ... ,ak) must be in non-descending order. 
 * (ie, a1 <= a2 <= ... <= ak).
 * The solution set must not contain duplicate combinations.
 * For example, given candidate set 2, 3, 6, 7 and target 7, a solution set is: 
 * [7] 
 * [2, 2, 3] 
 * 
 * OJ result: 688ms for large dataset.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// dhu: This is actually the coin change problem
class Solution {
public:
  vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int> > result;
    vector<int> curr;
    helper(result, curr, candidates, 0, target);
    return result;
  }

  void helper(vector<vector<int> >& result, vector<int> curr, 
	      const vector<int>& candidates, size_t level, int target) {
    if (target == 0) {
      result.push_back(curr);
      return;
    }

    if (target < 0)
      return;

    if (level == candidates.size())
      return;

    size_t max = target / candidates[level];
    for (size_t j = 0; j <= max; j++) {
      if (j != 0)
	curr.push_back(candidates[level]);
      helper(result, curr, candidates, level + 1, target - j * candidates[level]);
    }

  }
    
};

// Classic coin change problem
int combo(const vector<int>& candidates, int target, size_t level) 
{
  if (target == 0)
    return 1;

  if (target < 0)
    return 0;

  if (level == candidates.size())
    return 0;

  size_t max = target / candidates[level];
  int count = 0;
  for (size_t i = 0; i <= max; i++) {
    count += combo(candidates, target - i * candidates[level], level + 1);
  }

  return count;
}


int main() {
  vector<int> candidates;
  candidates.push_back(2);
  candidates.push_back(3);
  candidates.push_back(5);
  candidates.push_back(7);

  int target = 7;
  
  Solution foo;
  vector<vector<int> > ret = foo.combinationSum(candidates, target);
  for (size_t i = 0; i < ret.size(); i++) {
    for (size_t j = 0; j < ret[i].size(); j++)
      cout << ret[i][j] << " ";
    cout << endl;
  }
  

  //cout << combo(candidates, target, 0) << endl;

}
