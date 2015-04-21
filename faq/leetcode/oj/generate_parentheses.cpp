/* Given n pairs of parentheses, write a function to generate 
 * all combinations of well-formed parentheses.
 *
 * For example, given n = 3, a solution set is:
 * "((()))", "(()())", "(())()", "()(())", "()()()"
 */

#include <iostream>
#include <vector>

using namespace std;

// dhu solution: 16ms for large dataset
class Solution {
public:
  void helper(vector<string>& ret, string str, int n, int left, int right) {
    if (left == n && right == n) {
      ret.push_back(str);
      return;
    }

    if (left < n) {
      str[left + right] = '(';
      helper(ret, str, n, left + 1, right);
    }

    if (right < left) {
      str[left + right] = ')';
      helper(ret, str, n, left, right + 1);
    }
  }

  vector<string> generateParenthesis(int n) {
    vector<string> ret;
    string str(2*n, '0');
    helper(ret, str, n, 0, 0);
    return ret;
  }
};

// dhu DP solution: 16ms for large dataset.
// The idea is based on the Catlan number's recursive formula:
// C(n) = C(0) * C(n - 1) + C(1) * C(n - 2) + ... + C(n - 1) * C(0)
// Since we need here is the exact strings, the implementation is
// a little more messy.
class Solution_dhu_DP {
public:
  vector<string> generateParenthesis(int n) {
    vector<vector<string> > DP(n + 1);
    DP[0] = vector<string>(1, "");
    if (n == 0)
      return DP[0];

    DP[1] = vector<string>(1, "()");
    for (int i = 2; i <= n; i++) {
      for (int j = 0; j < i; j++) {
	for (size_t k = 0; k < DP[j].size(); k++) {
	  string tmp = string("(") + DP[j][k] + string(")");
	  for (size_t m = 0; m < DP[i - 1 - j].size(); m++) 
	    DP[i].push_back(tmp + DP[i - 1 - j][m]);
	}
      }
    }

    return DP[n];
  }

};

/* Dropbox solution
 * ----------------
 * There are two solutions for this problem, one is simple Backtracing(Bt), 
 * the other is Dynamic Programming(DP). I was thinking the DP would be 
 * faster when the number of Parentheses becomes larger. However, when n >=15, 
 * backtracking is much faster than DP.
 * 
 * The reseaon may be because the result is not just one, it would take much 
 * more time to generate inner results (we see for loop with push_back in DP).
 *  
 * DP may be faster than backtracking, when we need results that are less than 
 * MAXNUM again and again. For this problem, we do not need to calculate again.
 */

/********************* Backtracing Solution *********************/
vector<string> result;

// In this function, left is the number of valid '(' that 
// can be added at current level; right is the number of valid ')' that can 
// be added at current level; level is the current position's index.
void GenerateParentheses(string& p, int left, int right, int level) {
  if (left == 0 && right == 0) {
    result.push_back(p);
    return;
  }
	
  // Append left parenthese
  if (left > 0) {
    p[level] = '(';
    GenerateParentheses(p, left-1, right+1, level+1);
  }
	
  // Append right parenthese
  if (right > 0) {
    p[level] = ')';
    GenerateParentheses(p, left, right-1, level+1);
  }
}

void GenerateParentheses(int n)
{
    //initialize length of string to 2*n 
    string parenthesis(n*2,'\0');
    result.clear();
    GenerateParentheses(parenthesis, n, 0, 0);
}

// Dynamic Programming Solution: 24ms for large dataset
#define MAXNUM 100

// Only half of the matrix will be used.
// dhu: dp[i][j] saves the strings that include 
// i PAIRED '(' and j UNPAIRED ')'. 
vector<string> dp[MAXNUM][MAXNUM];  

// Recursive function that saves intermiediate result into dp[][]
void GenerateParentheses(int left, int right) {
  if (left == 0 && right == 0) {
    dp[0][0].push_back("");
    return;
  }

  // Append left parenthese
  if (left > 0) {
    vector<string>& strs = dp[left-1][right+1];
    if (strs.size() == 0)
      GenerateParentheses(left-1, right+1);
    
    for (size_t i = 0; i < strs.size(); ++i)
      dp[left][right].push_back('(' + strs[i]);
  }
    
  // Append right parenthese
  if (right > 0) {
    vector<string>& strs = dp[left][right-1];
    if (strs.size() == 0)
      GenerateParentheses(left, right-1);
    
    for (size_t i = 0; i < strs.size(); ++i)
      dp[left][right].push_back(')' + strs[i]);
  }

  // dhu: strings added to dp[left][right] when left > 0  all start with '(',
  //      strings added to dp[left][right] when right > 0 all start with ')',
  // so this gurantees that there are no duplicates in dp[left][right].
}

// Wrapper function
vector<string>& GenerateParentheses_dp(int n) {
  if (dp[n][0].size() == 0 )
    GenerateParentheses(n, 0);

  return dp[n][0];
}

// Test harness
int main() {
  int n = 3;
  //Solution_dhu_DP foo;
  //vector<string> ret = foo.generateParenthesis(n);

  vector<string> ret = GenerateParentheses_dp(n);
  for (int i = 0; i <= 3; i++) {
    for (int j = 0; j <= 3; j++) {
      cout << "[" << i << ", " << j << "]: ";
      for (size_t k = 0; k < dp[i][j].size(); k++) 
	cout << dp[i][j][k] << "\t";
      cout << endl;
    }
  }

  //for (size_t i = 0; i < ret.size(); i++) 
  // cout << ret[i] << endl;
  
  return 0;
}
