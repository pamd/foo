/* Leetcode OJ: Given a string S, find the longest palindromic substring in S. 
 * You may assume that the maximum length of S is 1000, and there exists one 
 * unique longest palindromic substring. */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* 152ms for large dataset, runtime complexity is O(n^2). 
 * See the following leetcode blogs for more efficient (and trickier) solution:
 * http://www.leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
 */
class Solution {
public:
  // Wrapper that calls two helper functions
  string longestPalindrome(string s) {
    if (s.size() == 0)
      return string();

    string even_str = find_even(s);
    string odd_str = find_odd(s);

    if (even_str.size() > odd_str.size())
      return even_str;

    return odd_str;
  }

  // Find longest palindrome whose length is an even number
  string find_even(const string& str) {
    int N = str.size();

    // Instead of keeping the longest palindrome substring so far,
    // we only keep the starting and ending indexes. Then we do not
    // need to call string::substr() to update the string. Updating
    // start and end should be faster, thus we save some time.
    int start = 0;
    int end = 0;
    for (int i = 0; i < N; i++) {
      for (int len = 0; len <= i && i + 1 + len < N; len++) {
	if (str[i - len] != str[i + 1 + len ])
	  break;
	if ((len + 1) * 2 > end - start + 1) {
	  start = i - len;
	  end = i + 1 + len;
	}
      }
    }

    return str.substr(start, end - start + 1);
  }

  // Find longest palindrome whose length is an odd number
  string find_odd(const string& str) {
    int N = str.size();

    // Instead of keeping the longest palindrome substring so far,
    // we only keep the starting and ending indexes. Then we do not
    // need to call string::substr() to update the string. Updating
    // start and end should be faster, thus we save some time.
    int start = 0; 
    int end = 0;
    for (int i = 0; i < N; i++) {
      for (int len = 1; len <= i && i + len < N; len++) {
	if (str[i - len] != str[i + len])
	  break;
	if (len * 2 + 1 > end - start + 1) {
	  start = i - len;
	  end = i + len;
	}
      }
    }

    return str.substr(start, end - start + 1);
  }

};

// Alternatively, we can build a DP table DP[i][j] which tells whether
// str[i:j] is a palindrome. The time complexity is also O(n^2), but 
// time limit is exceeded for large dataset.
class Solution_DP {
public:
  string longestPalindrome(string s) {
    int N = s.size();
    if (N == 0)
      return string();

    vector<vector<bool> > DP(N, vector<bool>(N, false));
    int start = 0;
    int end = 0;
    for (int offset = 0; offset < N; offset++) {
      for (int r = 0; r + offset < N; r++) {
	if (offset == 0)
	  DP[r][r + offset] = true;
	else if (offset == 1) 
	  DP[r][r + offset] = (s[r] == s[r + 1]);
	else 
	  DP[r][r + offset] = (s[r] == s[r + offset] && DP[r + 1][r + offset - 1]);

	if (DP[r][r + offset] && offset > end - start) {
	  start = r;
	  end = r + offset;
	}
      }
    }

    return s.substr(start, end - start + 1);
  }

};


/*****************************************************************************
 * Copied from:
 * http://www.leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
 *
 * 52ms for large dataset.
 *****************************************************************************/

// Transform S into T.
// For example, S = "abba", T = "^#a#b#b#a#$".
// ^ and $ signs are sentinels appended to each end to avoid bounds checking
string preProcess(string s) {
  int n = s.length();
  if (n == 0) return "^$";
  string ret = "^";
  for (int i = 0; i < n; i++)
    ret += "#" + s.substr(i, 1);
 
  ret += "#$";
  return ret;
}
 
string longestPalindrome(string s) {
  string T = preProcess(s);
  int n = T.length();
  int *P = new int[n];
  int C = 0, R = 0;
  for (int i = 1; i < n-1; i++) {
    int i_mirror = 2*C-i; // equals to i' = C - (i-C)
 
    P[i] = (R > i) ? min(R-i, P[i_mirror]) : 0;
 
    // Attempt to expand palindrome centered at i
    while (T[i + 1 + P[i]] == T[i - 1 - P[i]])
      P[i]++;
 
    // If palindrome centered at i expand past R,
    // adjust center based on expanded palindrome.
    if (i + P[i] > R) {
      C = i;
      R = i + P[i];
    }
  }
 
  // Find the maximum element in P.
  int maxLen = 0;
  int centerIndex = 0;
  for (int i = 1; i < n-1; i++) {
    if (P[i] > maxLen) {
      maxLen = P[i];
      centerIndex = i;
    }
  }
  delete[] P;
 
  return s.substr((centerIndex - 1 - maxLen)/2, maxLen);
}

int main() {
  string s("ccc");
  Solution_DP foo;
  cout << foo.longestPalindrome(s) << endl;

  return 0;
}
