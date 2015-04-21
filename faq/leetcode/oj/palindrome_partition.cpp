/* Given a string s, partition s such that every substring of the partition 
 * is a palindrome. Return all possible palindrome partitioning of s.
 * For example, given s = "aab", return
 *
 *   ["aa","b"],
 *   ["a","a","b"]
 */

#include <vector>
#include <string>
#include <iostream>

using namespace std;

// ~188ms for large dataset
class Solution {
public:
  vector<vector<string>> partition(string s) {
    // DP[i] saves all possible palindrome partitions for str(0:i).
    // This idea is very close to the DP in "word breaking" problem.
    vector<vector<vector<string> > > DP(s.size());
    for (int i = 0; i < (int) s.size(); i++) {
      if (isPalindrome(s, 0, i)) 
	DP[i].push_back(vector<string>(1, s.substr(0, i + 1)));
      for (int j = i; j >= 1; j--) {
        if (isPalindrome(s, j, i)) {
	  for (size_t k = 0; k < DP[j - 1].size(); k++) {
	    vector<string> tmp = DP[j - 1][k];
	    tmp.push_back(s.substr(j, i - j + 1));
	    DP[i].push_back(tmp);
	  }
	}
      }
    }

    return DP.back();
  }

  // Is str[start:end] a palindrome?
  bool isPalindrome(const string& str, int start, int end) {
    if (start > end || end >= (int) str.size())
      return false;

    while (start < end) {
      if (str[start] != str[end]) 
	return false;
      start++;
      end--;
    }
    return true;
  }

};

// anson627, recursive solution, 132ms for large dataset 
class Solution_anson {
public:
  vector<vector<string>> partition(string s) {
    vector<vector<string> > res;
    vector<string> sub;
    partitionHelper(s, 0, sub, res);
    return res;
  }

  // Recursive helper
  void partitionHelper(string const & s, size_t i, vector<string> sub, 
		       vector<vector<string> > & res) {
    if (i == s.size()) {
      res.push_back(sub);
      return;
    }

    for (size_t j = i; j < s.size(); j++) {
      if (isPalindrome(s, i, j)) {
	sub.push_back(s.substr(i, j-i+1));
	partitionHelper(s, j+1, sub, res);
	sub.pop_back();
      }
    }
  }

  bool isPalindrome(string const & s, size_t i, size_t j) {
    while (i < j) {
      if (s[i++] != s[j--])
	return false;
    }

    return true;
  }
};
