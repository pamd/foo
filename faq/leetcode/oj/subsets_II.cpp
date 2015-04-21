/* Leetcode OJ: Given a collection of integers that might contain duplicates, 
 * return all possible subsets.
 * Note:
 * Elements in a subset must be in non-descending order.
 * The solution set must not contain duplicate subsets.
 * For example,
 * If S = [1,2,2], a solution is:
 * [2], [1], [1,2,2], [2,2], [1,2], []
 */

// 56ms for large dataset
class Solution {
public:
  vector<vector<int> > subsetsWithDup(vector<int> &S) {
    vector<vector<int> > result;

    sort(S.begin(), S.end());
    vector<int> tmp;
    helper(S, result, tmp, 0);
    return result;
  }

  // Recursive helper function
  void helper(const vector<int>& S, vector<vector<int> >& result,
	      vector<int>& tmp, size_t level) {
    result.push_back(tmp);
    for (size_t i = level; i < S.size(); i++) {
      if (i > level && S[i] == S[i - 1])
	continue;
      tmp.push_back(S[i]);
      helper(S, result, tmp, i + 1); // the last parameter is "i + 1", NEVER use "level + 1"
      tmp.pop_back();
    }
  }

};

// Dropbox solution
vector<vector<int> > SubsetsWithDup(vector<int> &S) 
{
  map<int, int> counter;
  for (int i = 0; i < S.size(); ++i)
    counter[S[i]]++;
    
  map<int, int>::iterator beg = counter.begin();
  map<int, int>::iterator end = counter.end();
  vector<vector<int> > results;
  results.push_back(vector<int>());

  // Append new number to each of previous subset to generate new subsets
  while (beg != end) {
    int count = (*beg).second;
    int num = (*beg).first;
    int size = results.size();
    int base = 0;
    while (count-- > 0) {
      for (int i = 0; i < size; ++i) {
	results.push_back(results[base + i]);
	results.back().push_back(num);
      }
      base += size;
    }
    
    ++beg;
  }
  
  return results;
}

