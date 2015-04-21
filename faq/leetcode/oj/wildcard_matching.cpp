\ifx\CJKpreproc\undefined\def\CJKpreproc{cjk-enc}\RequirePackage{MULEenc}\fi /* Implement wildcard pattern matching with support for '?' and '*'.
 * '?' Matches any single character.
 * '*' Matches any sequence of characters (including the empty sequence).
 *
 * The matching should cover the entire input string (not partial).
 * The function prototype should be:
 * bool isMatch(const char *s, const char *p)
 *
 * Some examples:
 * isMatch("aa","a") => false
 * isMatch("aa","aa") => true
 * isMatch("aaa","aa") => false
 * isMatch("aa", "*") => true
 * isMatch("aa", "a*") => true
 * isMatch("ab", "?*") => true
 * isMatch("aab", "c*a*b") => false
 */

#include <string>
#include <iostream>
#include <map>

using namespace std;

class Solution {
public:
  bool isMatch(const char *s, const char *p) {
    string pattern;
    pattern.push_back(*p);
    p++;
    while (*p) {
      if (*p != '*' || *p != *(p - 1))
	pattern.push_back(*p);
      p++;
    }

    map<pair<int, int>, bool> dp;
    return isMatch_helper(s, 0, pattern.c_str(), 0, dp);
  }

  // Brute-force method: time limit exceeded for large dataset
  // s is input string, p is input pattern
  // This naive DP method won't pass large dataset either.
  bool isMatch_helper(const char *s, int s_idx, const char *p, int p_idx, 
		      map<pair<int, int>, bool>& dp) {
    pair<int, int> key(s_idx, p_idx);
    if (dp.find(key) != dp.end())
      return dp[key];

    if (!s && !p) {
      dp[key] = true;
      return true;
    }

    if (!s[s_idx] && !p[p_idx]) {
      dp[key] = true;
      return true;
    }

    while (p[p_idx]) {
      if (p[p_idx] == '?') {
	if (!s[s_idx]) {
	  dp[key] = false;
	  return false;
	}
	bool stat = isMatch_helper(s, s_idx + 1, p, p_idx + 1, dp);
	dp[key] = stat;
	return stat;
      }

      if (p[p_idx] == '*') {
	while (s[s_idx]) {
	  bool stat = isMatch_helper(s, s_idx, p, p_idx + 1, dp);
	  if (stat) {
	    dp[key] = true;
	    return true;
	  }
	  s_idx++;
	}

	bool stat = isMatch_helper(s, s_idx, p, p_idx + 1, dp);
	if (stat) {
	  dp[key] = true;
	  return true;
	}
	dp[key] = false;
	return false;
      }

      if (p[p_idx] == s[s_idx]) {
	dp[key] = isMatch_helper(s, s_idx + 1, p, p_idx + 1, dp);
	return dp[key];
      }

      dp[key] = false;
      return false;
    }

    dp[key] = false;
    return false;
  }

};

// anson627 solution
class Solution_anson {
public:
  bool isMatch(const char* s, const char* p) {
    return isMatch1(s, p);
  }

  // dhu: compact code, but time limit exceeded for large dataset
  bool isMatch1(const char* s, const char* p) {
    if (*s == '\0') {
      if (*p == '\0') 
	return true;

      if (*p == '*') 
	return isMatch(s, p+1);
      return false;
    }

    if (*p == '\0') 
      return false;

    if (*p == '?' || *p == *s) 
      return isMatch(s+1, p+1);

    if (*p =='*') 
      return isMatch(s+1,p) || isMatch(s, p+1);

    return false;
  }

  // 100ms for large dataset: using "goto" makes it harder to follow
  bool isMatch2(const char* s, const char* p) {
    const char *ps, *pp;
    bool star = false;
  loopStart:
    for (ps = s, pp = p; *ps; ++ps, ++pp) {
      switch (*pp) {
      case '?':
	break;

      case '*':
	star = true;
	s = ps, p = pp+1;
	if (!*p) 
	  return true;

	goto loopStart;

      default:
	if (*ps != *pp)
	  goto starCheck;
	break;
      }
    }

    while (*pp == '*') 
      ++pp;

    return (!*pp);

  starCheck:
    if (!star) 
      return false;

    s++;
    goto loopStart;
    return false;
  }
};

// Dropbox solution: 80ms for large dataset
bool isMatch(const char *s, const char *p) {
  // When original string is empty, only empty pattern 
  // or pattern with only asterisks would match it. 
  if (!*s) {
    while (*p == '*') 
      ++p;

    return (*p == '\0') ? true : false;
  }

  // When orginal string is not empty, but patern is empty, NEVER match.
  if (!*p) 
    return false;

  // dhu note: the following flag is redundant.
  // bool hasAsterisk = false;

  while (*p && *p != '*' && *s) {
    if (*s == *p || *p == '?')
      ++s, ++p;

    /* If first char in pattern is not '*', and this char is
     * not found in input string, match will fail. */
    else 
      return false;
  }
    
  /* If '*' is found in the pattern, get each substring in the pattern 
   * that does NOT include '*', then compare it with input string. */ 
  while (*p) {
    // Consecutive '*' is equivalent to one single '*', so they are merged into one.
    if (*p == '*') {
      //hasAsterisk = true;  
      ++p;
      continue;
    }
        
    // Search current substring in the pattern that does not include '*'
    const char* ss = s;
    const char* sp = p;
    /* The following while loop guarantees that current non-* 
     * substring in the pattern will be matched completely. */
    while (*s && *p && *p != '*') {
      if (*s == *p || *p == '?')
	++s, ++p;
      else
	s = ++ss, p = sp;
    }
    /* At the end of this while loop, we must have been either reached the end 
     * of input string, or pattern string, or we found another '*' in pattern. */

    /* When input string is empty, we still need to check the rest of pattern, 
     * because if the pattern is empty or only contains '*', they will match too. */
    if (!*s)
      return isMatch(s, p);
  }

  /* Now we have reached the end of pattern string, if we have also reached 
   * the end of input string, they must match. */
  if (!*s)
    return true;

  /* If we have reached the end of pattern, but input string is not empty yet, 
   * match the last part of non-* substring in pattern from right to left. 
   * If they do not match, the pattern could not match the WHOLE string. */

  // dhu note: hasAsterisk seems to be redundant
  //if (!hasAsterisk)
  //  return false;
  
  if (*(--p) == '*') 
    return true;
  
  /* It may seem reasonable to return false here, but we have to compare 
   * the last section of non-* substring in pattern with the end of input string. 
   * Consider the test cases of input string "abcdd" and pattern "abc*d". */
  while (s[1]) 
    ++s;

  // Compare the last part from right side to left side
  while (*p != '*' && (*s == *p || *p == '?'))
    --s, --p;

  return (*p == '*') ? true : false;
}

// Solution based on regular expression problem.
// Time limit exceeded on large dataset.
class Solution_regex {
public:
  bool isMatch(const char* s, const char* p) {
    string pattern;
    while (*p) {
      if (*p == '?')
	pattern.push_back('.');
      else if (*p == '*')
	pattern += ".*";
      else
	pattern.push_back(*p);
      p++;
    }
    
    return regex(s, pattern.c_str());
  }

  // Solution of regular expression
  bool regex(const char *s, const char *p) {
    if (*p == '\0') 
      return *s == '\0';    

    if (*(p+1) != '*') {
      return ((*p == *s) || (*p == '.' && *s != '\0')) && regex(s+1, p+1);
    }

    while ((*p == *s) || (*p == '.' && *s != '\0')) {
      if (regex(s, p + 2))  // isMatch(s + 1, p + 2) will NOT work!
	return true;
      s++;
    }

    return regex(s, p + 2); 
  }

};

// Test harness
int main() { 
  Solution_regex foo;
  const char* txt = "aa";
  const char* pat = "a.*";
  
  if (foo.regex(txt, pat)) 
    cout << "match" << endl;
  else
    cout << "NOT match" << endl;

  return 0;
}

// longway2008: without using recursion.
// s: text, p: pattern
// http://www.mitbbs.com/article_t1/JobHunting/32258853_0_3.html
bool isMatch(const char *s, const char *p) {
  if (!p) 
    return !s;

   if (!s) 
     return !p;

   const char *star = 0; // position of the previous '*' in pattern
   const char *s_save = s; // position in text that we should go back to in mismatch 
   while (*s) { 
     if (*p == '*') {
        star = p++;
        s_save = s;
     } 
     else if ( *p != '?' && *s != *p) {  // mismatch
       if (!star) // previous '*' not found, return false
	 return false;

       // Previous '*' exists, so we go back to where '*' is found, and match again
       p = star + 1;
       s = ++s_save;
     } 
     else { // current char in s and p match, so we check the next position.
       s++;
       p++;
     }
   }

   // Remove all trailing '*' in pattern
   while (*p == '*')  
     p++; 

   // If we have reached the end of pattern string, 
   // then p and s match, otherwise they do not match.
   return !*p;  
}

// peking2: DP solution based on his Java code
/*
public boolean isMatch(const string& s, const string& p) {
  int n = s.length();
  int m = p.length();
        
  vector<vector<bool> > dp(2, vector<bool>(n + 1, false));
  dp[m % 2][n] = true;
  
  for(int i = m - 1; i >= 0; i--) {
    Arrays.fill(dp[i%2], false);
    dp[i%2][n]=p.charAt(i)=='*' && dp[(i+1)%2][n];
    
    for(int j=n-1;j>=0;j--) {   
      if(p.charAt(i)=='*')
	dp[i%2][j]=dp[(i+1)%2][j] || dp[i%2][j+1];
      else
	dp[i%2][j] = (p.charAt(i)==s.charAt(j) || p.charAt(i)=='?') && dp[(i+1)%2][j+1]; 
    }
  }

  return dp[0][0];
}
*/
