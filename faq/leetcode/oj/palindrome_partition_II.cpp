/* Given a string s, partition s such that every substring of the partition 
 * is a palindrome. Return the minimum cuts needed for a palindrome partitioning 
 * of s. 
 * For example, given s = "aab", return 1 since the palindrome partitioning 
 * ["aa","b"] could be produced using 1 cut.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  int minCut(string s) {
    //return rec_helper(s, 0);
    return dp(s);  
  }

  // Recursive solution: time limit exceeded in large data set.
  int rec_helper(const string& str, size_t start) {
    if (start == str.size())
      return 0;

    if (isPalindrome(str, start, str.size() - 1))
      return 0;

    int min_cut = str.size() - start - 1;
    for (size_t i = start; i < str.size(); i++) {
      if (isPalindrome(str, start, i)) {
	min_cut = min(min_cut, 1 + rec_helper(str, i + 1)); 
      }
    }

    return min_cut;
  }

  // DP solution
  int dp(const string& str) {
    // Without building the following table, time limit exceeded 
    // for large dataset. With this table, 400ms for large dataset.
    vector<vector<bool>> table(str.size(), vector<bool>(str.size(), false));
    buildTable(str, table);

    vector<int> DP(str.size(), str.size());
    DP[0] = 0;
    for (size_t i = 0; i < str.size(); i++) {
      if (isPalindrome(table, 0, i))
	DP[i] = 0;
      else {
	for (int j = i; j >= 1; j--) {
	  if (isPalindrome(table, j, i)) 
	    DP[i] = min(DP[i], 1 + DP[j - 1]);
	}
      }
    }

    return DP.back();
  }

  // Manually check whether s[start:end] is a palindrome?
  bool isPalindrome(const string& s, int start, int end) {
    if (start > end)
      return false;

    while (start < end) {
      if (s[start] != s[end])
	return false;
      start++;
      end--;
    }

    return true;
  }

  // Build palindrome table
  void buildTable(const string& str, vector<vector<bool> >& table) {
    for (size_t offset = 0; offset < table.size(); offset++) {
      for (size_t r = 0; r + offset < table.size(); r++) {
	if (offset == 0)
	  table[r][r + offset] = true;
	else if (offset == 1) 
	  table[r][r + offset] = (str[r] == str[r + offset]);
	else 
	  table[r][r + offset] = (str[r] == str[r + offset] && table[r + 1][r + offset - 1]);
      }
    }
  }

  // Use the table to check whether str[start:end] is a palindorme
  bool isPalindrome(const vector<vector<bool>>&table, int start, int end) {
    return table[start][end];
  }

};

// anson627 solution: 352ms for large dataset
class Solution_anson {
public:
  int minCut(string s) {
    if (s.empty()) 
      return 0;

    int N = s.size();

    // dp1[i][j] tells whether s(i:j) is a palindrome or not
    vector<vector<bool> > dp1(N, vector<bool>(N, false));
    for (int i = N-1; i >= 0; i--) {
      for (int j = i; j < N; j++) {
	if (i == j) 
	  dp1[i][j] = true;
	else if (i + 1 == j) 
	  dp1[i][j] = (s[i] == s[j]);
	else 
	  dp1[i][j] = (s[i] == s[j] && dp1[i + 1][j - 1]);
      }
    }

    // dp2[i] is the min cut for s.substr(0, i)
    vector<int> dp2(N+1, 0);
    dp2[0] = -1;
    for (int i = 2; i <= N; i++) {
      dp2[i] = dp2[i - 1] + 1;
      for (int j = i - 2; j >= 0; j--)
	if (dp1[j][i - 1])
	  dp2[i] = min(dp2[i], 1 + dp2[j]);
    }
    
    return dp2[N];
  }

};

int main() {
  Solution foo;
  string s = "aab";
  cout << foo.minCut(s) << endl;

  return 0;
}

