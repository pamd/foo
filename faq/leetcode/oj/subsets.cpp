/* Leetcode OJ: Given a set of distinct integers, S, return all possible subsets.
 * Note:
 * Elements in a subset must be in non-descending order.
 * The solution set must not contain duplicate subsets.
 */

// 40ms for large dataset: idea comes from PIE book
class Solution {
public:
  vector<vector<int> > subsets(vector<int> &S) {
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
      tmp.push_back(S[i]);
      helper(S, result, tmp, i + 1); // the last parameter is "i + 1", NEVER use "level + 1"
      tmp.pop_back();
    }
  }

};

// Dropbox solution: very confusing
vector<vector<int> > Subsets(vector<int> s) {
  int n = s.size();
  sort(s.begin(), s.end());
    
  vector<vector<int> > subs;
  queue<vector<int> > vQueue;
  subs.push_back(vector<int>()); // Empty subset
  for (int i = 0; i < n; ++i)
    vQueue.push(vector<int>(1, i));

  while(!vQueue.empty()) {
    vector<int>& subIndics = vQueue.front();
    subs.push_back(vector<int>());
    vector<int>& v = subs.back();

    for (int i = 0; i < subIndics.size(); ++i)
      v.push_back(s[subIndics[i]]);
        
    int next = subIndics.back() + 1;
    subIndics.push_back(0);
    for (int i = next; i < n; ++i) {
      subIndics.back() = i;
      vQueue.push(subIndics);
    }

    vQueue.pop();
  }

  return subs;
}

