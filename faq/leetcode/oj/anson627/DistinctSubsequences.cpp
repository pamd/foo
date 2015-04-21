//============================================================================
// Distinct Subsequences
// Given a string S and a string T, count the number of distinct subsequences
// of T in S.
//
// A subsequence of a string is a new string which is formed from the original
// string by deleting some (can be none) of the characters without disturbing
// the relative positions of the remaining characters. (ie, "ACE" is a
// subsequence of "ABCDE" while "AEC" is not).
//
// Here is an example:
// S = "rabbbit", T = "rabbit"
//
// Return 3.
//============================================================================

#include <iostream>
using namespace std;

// 40ms for large dataset
class Solution {
public:
  // S is source string, T (target) is the subsequence string
  int numDistinct(string S, string T) {
    int s = S.size();
    int t = T.size();
    /* dp[i][j] is the number of distinct subsequences of 
     * T.substr(0, i) that can be found in S.substr(0, j). 
     * With this DP table, the problem looks like a variant 
     * of edit distance or LCS (longest common subsequence). */
    int dp[t+1][s+1];
    dp[0][0] = 1;
    for (int i = 1; i <= t; i++) 
      dp[i][0] = 0;

    for (int j = 1; j <= s; j++) 
      dp[0][j] = 1;

    for (int i = 1; i <= t; i++) {
      for (int j = 1; j <= s; j++) {
	if (T[i-1] == S[j-1]) 
	  dp[i][j] = dp[i-1][j-1] + dp[i][j-1];
	else 
	  dp[i][j] = dp[i][j-1];
      }
    }
    return dp[t][s];
  }
};

int main() {
  return 0;
}
