/* Given two integers n and k, return all possible combinations 
 * of k numbers out of 1 ... n.
 * For example, if n = 4 and k = 2, a solution is:
 *   [2,4],
 *   [3,4],
 *   [2,3],
 *   [1,2],
 *   [1,3],
 *   [1,4],
 *
 * OJ result: 72ms for large dataset.
 */

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
  vector<vector<int> > combine(int n, int k) {
    vector<vector<int> > result;
    vector<int> curr;
    helper(n, k, result, curr, 1);
    return result;
  }

  void helper(int n, int k, vector<vector<int> >& result, 
	     vector<int> curr, int level) {
    if (k > n)
      return;

    if ((int) curr.size() == k) {
      result.push_back(curr);
      return;
    }

    if (level > n)
      return;

    for (int i = level; i <= n; i++) {
      curr.push_back(i);
      helper(n, k, result, curr, i + 1);
      curr.pop_back();
    }
  }
};

int main() {
  int n = 4, k = 2;
  Solution foo;
  vector<vector<int> > ret = foo.combine(n, k);
  for (size_t i = 0; i < ret.size(); i++) {
    for (size_t j = 0; j < ret[i].size(); j++)
      cout << ret[i][j] << " ";
    cout << endl;
  }

  return 0;
}
