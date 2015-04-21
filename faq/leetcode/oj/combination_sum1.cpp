/* Leetcode OJ: Given a set of candidate numbers (C) and a target number (T), 
 * find all unique combinations in C where the candidate numbers sums to T.
 * The same repeated number may be chosen from C unlimited number of times.
 * Note:
 * All numbers (including target) will be positive integers.
 * Elements in a combination (a1, a2, ... , ak) must be in non-descending order. 
 * (ie, a1 <= a2 <= ... <= ak).
 * The solution set must not contain duplicate combinations.
 * For example, given candidate set 2, 3, 6, 7 and target 7, a solution set is: 
 * [7] 
 * [2, 2, 3] 
 */

#include <iostream>
#include <vector>

using namespace std;

// dhu: This is actually the coin change problem
class Solution {
public:
  vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
    vector<vector<int> > result;
    /*
    for (size_t level = 0; level < candidates.size(); level++) {
      size_t max = target / candidates[level];
      for (size_t i = 0; i <= max; i++) {
	vector<int> curr(i, candidates[level]);
	helper(result, curr, candidates, level + 1, target - i * candidates[level]);
      }
    }
    */

    vector<int> curr;
    helper(result, curr, candidates, 0, target);
    return result;
  }

  void helper(vector<vector<int> >& result, vector<int> curr, 
	      const vector<int>& candidates, size_t level, int target) {
    //cout << "target: " << target << endl;
    if (target == 0) {
      result.push_back(curr);
      return;
    }

    if (target < 0)
      return;

    for (size_t i = level; i < candidates.size(); i++) {
      size_t max = target / candidates[i];
      for (size_t j = 0; j <= max; j++) {
	vector<int> curr2 = curr;
	for (size_t k = 0; k < j; k++) 
	  curr2.push_back(candidates[i]);
	helper(result, curr2, candidates, i + 1, target - j * candidates[i]);
      }
    }
  }
    
};

// Coin change problem
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

  int target = 2;
  
  /*  
  Solution foo;
  vector<vector<int> > ret = foo.combinationSum(candidates, target);
  for (size_t i = 0; i < ret.size(); i++) {
    for (size_t j = 0; j < ret[i].size(); j++)
      cout << ret[i][j] << " ";
    cout << endl;
  }
  */

  cout << combo(candidates, target, 0) << endl;

}
