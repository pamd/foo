/* OJ question: 
 * Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
 * For example,
 * Given:
 * s1 = "aabcc",
 * s2 = "dbbca",
 *
 * When s3 = "aadbbcbcac", return true.
 * When s3 = "aadbbbaccc", return false.
 */

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

struct Triplet {
  Triplet(const string& str1, const string& str2, const string& str3) :
    s1(str1), s2(str2), s3(str3) { }

  // Defined for std::map approach, time limit exceeded in OJ
  bool operator<(const Triplet& rhs) const {
    if (s1 < rhs.s1)
      return true;
    else if (s1 == rhs.s1 && s2 < rhs.s2) 
      return true;
    else if (s1 == rhs.s1 && s2 == rhs.s2 && s3 < rhs.s3)
      return true;

    return false;
  }
  
  // Defined for std::unordered_map approach, compilable on g++@ajax,
  // but can NOT compile on OJ.
  bool operator==(const Triplet& rhs) const {
    return s1 == rhs.s1 && s2 == rhs.s2 && s3 == rhs.s3;
  }

  string s1, s2, s3;
};

// Defined for std::unordered_map approach, compilable on g++@ajax,
// but can NOT compile on OJ.
size_t dhu_hasher(const Triplet& combo) {
  return hash<string>()(combo.s1 + " " + combo.s2 + " " + combo.s3);
}

/* std::unordered_map approach, compilable on g++@ajax,
 * but can NOT compile on OJ. */
/*
class Solution {
public:
  // DP helper
  bool helper(const string& s1, const string& s2, const string& s3, 
	      unordered_map<Triplet, bool, decltype(dhu_hasher)*>& dp) {
    Triplet tmp(s1, s2, s3);
    auto it = dp.find(tmp);
    if (it != dp.end())
      return it->second;

    if (s3.size() != s1.size() + s2.size()) {
      //dp.insert(make_pair<Triplet, bool>(tmp, false));
      dp[tmp] = false;
      return false;
    }

    if (s3.size() == 0) {
      dp[tmp] = true;
      return true;
    }

    if (s1.size() == 0 && s2 == s3) {
      dp[tmp] = true;
      return true;
    }

    if (s2.size() == 0 && s1 == s3) {
      dp[tmp] = true;
      return true;
    }

    for (size_t i = 0; i < s3.size(); i++) {
      if (s3[i] == s1[0]) {
	if (s3.substr(0, i) == s2.substr(0, i)) {
	  string s1_sub = s1.substr(1);
	  string s2_sub = s2.substr(i);
	  string s3_sub = s3.substr(i + 1);
	  if (helper(s1_sub, s2_sub, s3_sub, dp)) {
	    dp[tmp] = true;
	    return true;
	  }
	}
      }
    }

    dp[tmp] = false;
    return false;
  }

  bool isInterleave(string s1, string s2, string s3) {
    unordered_map<Triplet, bool, decltype(dhu_hasher)*> dp(100, dhu_hasher);
    return helper(s1, s2, s3, dp);
  }
};
*/

/* 32ms for large dataset.
 * Instead of using traditional hashmap of a triplet string combinations, 
 * we convert the Triplet into a unique unsigned int.
 * It is a dirty trick, but it works.
 */
class Solution {
public:
  // DP helper
  bool helper(const string& s1, size_t i1, const string& s2, size_t i2, 
	      const string& s3, size_t i3, unordered_map<size_t, bool>& dp) {
    // A dirty trick that avoids comparing substrings of s1, s2 and s3.
    size_t key = i1 * s3.size() * s3.size() + i2 * s3.size() + i3;
    if (dp.find(key) != dp.end())
      return dp[key];

    string s1_sub = s1.substr(i1);
    string s2_sub = s2.substr(i2);
    string s3_sub = s3.substr(i3);

    if (s1.size() == i1 && s2_sub == s3_sub) {
      dp[key] = true;
      return true;
    }

    if (s2.size() == i2 && s1_sub == s3_sub) {
      dp[key] = true;
      return true;
    }

    for (size_t i = i3; i < s3.size(); i++) {
      if (s3[i] == s1[i1]) {
	if (s3.substr(i3, i - i3) == s2.substr(i2, i - i3)) {
	  if (helper(s1, i1 + 1, s2, i2 + i - i3, s3, i + 1, dp)) {
	    dp[key] = true;
	    return true;
	  }
	}
      }
    }

    dp[key] = false;
    return false;
  }

  bool isInterleave(string s1, string s2, string s3) {
    if (s3.size() != s1.size() + s2.size()) 
      return false;

    unordered_map<size_t, bool> dp;
    return helper(s1, 0, s2, 0, s3, 0, dp);
  }
};

// anson627 solution
class Solution_anson {
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
