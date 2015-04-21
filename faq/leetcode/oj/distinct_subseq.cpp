/* OJ question: 
 * Given a string S and a string T, count the number of distinct subsequences of T in S.
 * A subsequence of a string is a new string which is formed from the original string by 
 * deleting some (can be none) of the characters without disturbing the relative positions 
 * of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).
 *
 * Here is an example:
 * S = "rabbbit", T = "rabbit"
 * Return 3.
 */

#include <vector>
#include <string>
#include <iostream>

using namespace std;

// 284ms for large dataset
class Solution {
public:
  int numDistinct(string S, string T) {
    vector<vector<int> > dp(S.size() + 1);
    for (size_t i = 0; i < dp.size(); i++)
      dp[i] = vector<int>(T.size() + 1, -1);

    return helper(0, 0, dp, S, T);
  }

  int helper(size_t x, size_t y, vector<vector<int> >& dp, 
	     const string& src, const string& seq) {
    if (src.size() - x < seq.size() - y) 
      return 0;

    if (y == seq.size())
      return 1;

    if (x == src.size())
      return 0;

    if (dp[x][y] != -1)
      return dp[x][y];

    int ret = 0;
    for (size_t i = x; i < src.size(); i++) {
      if (src[i] == seq[y])
	ret += helper(i + 1, y + 1, dp, src, seq);
    }
    dp[x][y] = ret;
    return ret;
  }
  
};

// anson627 solution: only takes 40ms and is more intuitive.
class Solution_anson {
public:
  int numDistinct(string S, string T) {
    size_t ns = S.size();
    size_t nt = T.size();

    /* dp[i][j] is the number of distinct subsequences of 
     * T.substr(0, j) that is found in S.substr(0, i). 
     * With this DP table, the problem looks like a variant 
     * of edit distance or LCS (longest common subsequence). */
    int dp[ns + 1][nt + 1];
    dp[0][0] = 1;

    // Set first column of dp table
    for (size_t i = 1; i <= ns; i++) 
      dp[i][0] = 1;
    // Set first row of dp table
    for (size_t i = 1; i <= nt; i++) 
      dp[0][i] = 0;

    // Populate the table
    for (size_t i = 1; i <= ns; i++) {
      for (size_t j = 1; j <= nt; j++) {
	dp[i][j] = dp[i - 1][j];
	if (S[i - 1] == T[j - 1])
	  dp[i][j] += dp[i - 1][j - 1];
      }
    }

    return dp[ns][nt];
  }
};

int main() {
  string S("rabbbit");
  string T("rabbit");
  Solution foo;
  cout << foo.numDistinct(S, T) << endl;
}
