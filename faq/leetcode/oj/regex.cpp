/* Leetcode OJ: Implement regular expression with support for '.' and '*'.
 * '.' Matches any single character.
 * '*' Matches zero or more of the preceding element.
 * The matching should cover the entire input string (not partial).
 * The function prototype should be:
 * bool isMatch(const char *s, const char *p)
 *
 * Some examples:
 * isMatch("aa","a") is false
 * isMatch("aa","aa") is true
 * isMatch("aaa","aa") is false
 * isMatch("aa", "a*") is true
 * isMatch("aa", ".*") is true
 * isMatch("ab", ".*") is true
 * isMatch("aab", "c*a*b") is true
 */

#include <iostream>
#include <cassert>

using namespace std;

// 88ms for large dataset
class Solution {
public:
  bool isMatch(const char *s, const char *p) {
    if (!s && !p)
      return true;

    if (!s || !p)
      return false;

    if (!*s && !*p)
      return true;

    // Blank string should match "<c>* or <c1>*<c2>*", etc
    if (!*s && *(p + 1) == '*')
      return isMatch(s, p + 2);

    if (!*s || !*p)
      return false;

    char cp = *p;
    char cs = *s;
    if (cp == '.') {
      if (*(p + 1) == '*')
	return matchDotStar(s, p + 2);      
      return isMatch(s + 1, p + 1);
    }
    
    if (*(p + 1) == '*') 
      return matchStar(s, p + 2, cp);
    
    if (cp != cs)
      return false;
    
    return isMatch(s + 1, p + 1);
  }

  // Match ".*" 
  bool matchDotStar(const char* s, const char* p) {
    while (*s) {
      if (isMatch(s, p))
	return true;
      s++;
    }

    return isMatch(s, p);
  }

  // Match "c*", in which 'c' is any character other than '.'
  bool matchStar(const char* s, const char* p, char pre_star) {
    // Zero occurences of pre_star
    if (isMatch(s, p))
      return true;
    
    while (*s) {
      if (*s != pre_star)
	return false;
      if (isMatch(s + 1, p))
	return true;
      s++;
    }

    return isMatch(s, p);
  }
};

// anson627: similar idea, but much more compact implementation
class Solution_anson {
public:
  bool isMatch(const char *s, const char *p) {
    assert(s && p);

    if (*p == '\0') 
      return *s == '\0';    

    // If p[1] is not '*'
    if (*(p+1) != '*') {
      // Assume that '*' will be always preceded by at least one regular char
      assert(*p != '*');
      return ((*p == *s) || (*p == '.' && *s != '\0')) && isMatch(s+1, p+1);
    }

    // If p[1] is '*'.
    // Suppose pattern is "a*bc" and text is "aabc", the following 
    // "while" loop will match "aabc" with "bc", and "abc" with "bc".
    // and the final "return isMatch(s, p + 2);" will match "bc" with "bc".
    //
    // On the other hand, if pattern is "a*bc" and text is "bc", the "while" 
    // loop won't be executed at all, the code will immediately match "bc" 
    // with "bc" immediately.
    while ((*p == *s) || (*p == '.' && *s != '\0')) {
      if (isMatch(s, p + 2))  // isMatch(s + 1, p + 2) will NOT work!
	return true;
      s++;
    }
    return isMatch(s, p + 2); 
  }

};

// DP solution: Let D[i][j] denotes whether the sub pattern p[0..j] 
// can cover the first i characters of s?
// Use a boolean vector to record D[0...n,j], repeatedly update it as j 
// increments. 
// Or you can use a set to save all the i's such that D[i,j] == true 
// in each iteration.
//
// Note that in the following implementation, the DP table is actually 
// converted into one dimension to save space.
// Ref:
// http://discuss.leetcode.com/questions/175/regular-expression-matching
class Solution_DP1 {
public:
  vector<bool> covered;
  int size_s, size_p;

  // Get length of input string
  int get_size(const char *c) {
    int n = 0;
    while (c[n]){
      n++;
    }

    return n;
  }

  // Match single char in string and pattern
  inline bool single_char_match(char s, char p) {
    return p == '.' || p == s;
  }

  bool match(const char *s, const char *p, int i) {
    bool ret = false;       
    if (i == size_p-1 || p[i+1] != '*'){
      covered[size_s]=false;
      for(int j = size_s-1; j>=0; --j){
	if(covered[j]){
	  if(single_char_match(s[j],p[i])){
	    covered[j+1] = true;
	    ret = true;
	  }
	  covered[j] = false;
	}
      }
    }
    else {
      ret = covered[size_s];
      for (int j = 0; j < size_s; ++j){ 
	if(covered[j]){
	  ret = true;
	  if( single_char_match(s[j],p[i]) ){
	    covered[j+1] = true;
	  }
	}
      }
    }
    return ret;
  }

  // Main function call
  bool isMatch(const char *s, const char *p) {
    if (!*s && !*p) 
      return true;
    
    if (!*p) 
      return false;
   
    size_s = get_size(s);
    size_p = get_size(p);
    covered.assign(size_s+1, false);

    int i = 0;
    // Pattern has only one char, or its second char is not '*'
    if (size_p < 2 || p[1] != '*') {
      if (single_char_match(s[0], p[0])){
	covered[1] = true;
	i = 1;
      }
      else 
	return false;
    }

    // Pattern length is at least 2, AND its second char is '*'
    else {
      int c = 0;
      do {
	covered[c] = true;
	c++;
      } while (single_char_match(s[c-1], p[0]) && c <= size_s);
      i=2;
    }

    for(; i < size_p; ++i){
      if (p[i]!='*'){
	if(!match(s,p,i)) 
	  return false;
      }
    }

    return covered[size_s];
  }

};

// DP idea #2: easier to understand
class Solution_DP2 {
public:
  bool isMatch(const char *s, const char *p) {
    if (!s || !p) 
      return false;
    
    int slen = strlen(s);
    int plen = strlen(p);

    // dp[i][j] denotes whether the first i characters in pattern 
    // can match the first j characters in string. 
    // That is why it has plen+1 rows and slen+1 columns.
    vector<bool> dp[plen+1];
    for (int i = 0; i <= plen; i++)
      dp[i] = vector<bool> (slen+1, false);

    dp[0][0] = true;
    for (int i = 1; i <= plen; i++) { // i is the number of leading chars in pattern
      switch(p[i-1]) {
	// Case #1: current char in pattern is '*'
      case '*': 
	if (i == 1) {
	  dp[i][0] = false;
	  continue;
	}

	dp[i][0] = dp[i-2][0];

	if (p[i-2] != '.') { // "[a-zA-Z]*" in pattern
	  for (int j = 1; j <= slen; j++) { // j is the number of leading char in string
	    if (dp[i-1][j] // "x*" denotes "x" 
		|| (i >= 2 && dp[i-2][j]) // "x*" denotes null
		|| (j >= 2 && dp[i][j-1] && s[j-1] == s[j-2] && s[j-2] == p[i-2])) 
	           // "x*" denotes "xx", "xxx", etc 
	      dp[i][j] = true;
	  }
	}
	else { // ".*" in pattern
	  int j = 1;
	  // Find the shortest prefix of string so that the first i-2 or i-1 
	  // chars in pattern matches this prefix. 
	  while (!dp[i-2][j] && j <= slen && !dp[i-1][j]) 
	    j++;

	  // Let ".*" consume all characters in string thereafter
	  for (; j <= slen; j++) {
	    dp[i][j] = true;
	  }
	}
	break;
    
	// Case #2: current char in pattern is a regular char
      default: 
	for (int j = 1; j <= slen; j++) {
	  if (dp[i-1][j-1] && (p[i-1] == s[j-1] || p[i-1] == '.'))
	    dp[i][j] = true;
	}
	break;
      }
    }
    
    return dp[plen][slen];
  }

};

// Test harness
int main() {
  Solution_anson foo;
  const char* txt = "aa";
  const char* pat = "a.*";

  if (foo.isMatch(txt, pat))
    cout << "yes" << endl;
  else
    cout << "no" << endl;
}

// "bbbba", ".*a*a" true
