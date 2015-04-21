//============================================================================
// Interleaving String
// Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
//
// For example,
// Given:
// s1 = "aabcc",
// s2 = "dbbca",
//
// When s3 = "aadbbcbcac", return true.
// When s3 = "aadbbbaccc", return false.
//============================================================================

#include <iostream>
using namespace std;

class Solution {
public:
  bool isInterleave(string s1, string s2, string s3) {
    // return isInterleave1(s1, s2, s3);
    return isInterleave2(s1, s2, s3);
  }

  // Wrapper of recursive solution
  bool isInterleave1(string s1, string s2, string s3) {
    return isInterleaveHelper1(s1.c_str(), s2.c_str(), s3.c_str());
  }

  // Recursive function: time limit exceeded for large dataset
  bool isInterleaveHelper1(const char *s1, const char *s2, const char *s3) {
    if(*s1 == '\0' && *s2 == '\0' && *s3 == '\0') 
      return true;

    if (*s3 == '\0') 
      return false;

    if (*s1 == '\0' && *s2 == '\0') 
      return false;

    return ((*s1 == *s3 && isInterleaveHelper1(s1 + 1, s2, s3 + 1)) ||
	    (*s2 == *s3 && isInterleaveHelper1(s1, s2 + 1, s3 + 1)));
  }

  // DP solution: 12ms for large dataset
  bool isInterleave2(string s1, string s2, string s3) {
    size_t M = s1.size();
    size_t N = s2.size();
    if (M + N != s3.size()) 
      return false;

    /* If dp[i][j] is true, it means that s3.substr(0, i + j) is 
     * an interleaving string of s1.substr(0, i) and s2.substr(0, j);
     * if dp[i][j] is false, then s3.substr(0, i + j) is not an interleaving
     * string of s1.substr(0, i) and s2.substr(0, j). */
    bool dp[M+1][N+1];
    dp[0][0] = true;
    for (size_t i = 1; i <= M; i++) {
      if (dp[i-1][0] && s1[i-1] == s3[i-1]) 
	dp[i][0] = true;
      else 
	dp[i][0] = false;
    }

    for (size_t j = 1; j <= N; j++) {
      if (dp[0][j-1] && s2[j-1] == s3[j-1]) 
	dp[0][j] = true;
      else 
	dp[0][j] = false;
    }

    for (size_t i = 1; i <= M; i++) {
      for (size_t j = 1; j <= N; j++) {
	if ((dp[i-1][j] && s1[i-1] == s3[i+j-1]) || (dp[i][j-1] && s2[j-1] == s3[i+j-1])) 
	  dp[i][j] = true;
	else 
	  dp[i][j] = false;
      }
    }

    return dp[M][N];
  }
};

int main() {
  Solution sol;
  cout << sol.isInterleave("aabcc", "dbbca", "aadbbcbcac") << endl;
  cout << sol.isInterleave("aabcc", "dbbca", "aadbbbaccc") << endl;
  return 0;
}
