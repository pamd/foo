/*******************************************************************
 * C++ implementation of Rabin-Karp algorithm, based on ALGS4
 * Java implementation: algs4_RabinKarp.java, which is copied from:
 *
 * http://algs4.cs.princeton.edu/53substring/RabinKarp.java.html
 *
 */

#include <string>
#include <cstring>
#include <iostream>

using namespace std;

// API designed for Leetcode OJ.
// 24ms for large dataset.
class Solution {
public:
  // Wrapper for leetcode OJ
  const char *strStr(const char *haystack, const char *needle) {
    if (!haystack)
      return 0;
    if (!needle || !needle[0])
      return haystack;
    
    int ret = search(haystack, needle);
    if (ret < 0)
      return 0;

    return haystack + ret;
  }

  // Preprocess input pattern and return the hash value
  long processPattern(const string& pat, int& RM, int R, int Q) {
    int M = pat.size();
    // precompute R^(M-1) % Q for use in removing leading digit
    for (int i = 1; i <= M - 1; i++)
      RM = (R * RM) % Q;

    return rk_hash(pat, M, R, Q);    
  } 

  // Compute hash for key[0..M-1]. 
  long rk_hash(const string& key, int M, int R, int Q) { 
    long h = 0; 
    for (int j = 0; j < M; j++) 
      h = (R * h + key[j]) % Q; 
    return h; 
  } 

  // Las Vegas version: does pat[] really match txt[i..i-M+1] ?
  bool check(const string& txt, const string& pat, int i) {
    int M = pat.size();
    for (int j = 0; j < M; j++) { 
      if (pat[j] != txt[i + j]) 
	return false; 
    }

    return true;
  }

  // check for exact match
  int search(const string& txt, const string& pat) { 
    int N = txt.size(); 
    int M = pat.size();
    if (N < M) 
      return -1;

    int R = 256;
    long Q = 997; // Arbitrary prime number, selected by dhu

    int RM = 1;
    long patHash = processPattern(pat, RM, R, Q);
    long txtHash = rk_hash(txt, M, R, Q); 
    // Check for match at offset 0
    if ((patHash == txtHash) && check(txt, pat, 0))
      return 0;

    // Check for hash match; if hash match, check for exact match
    for (int i = M; i < N; i++) {
      // Remove leading digit, add trailing digit, check for match. 
      txtHash = (txtHash + Q - RM * txt[i-M] % Q) % Q; 
      txtHash = (txtHash * R + txt[i]) % Q; 
      
      // match
      int offset = i - M + 1;
      if ((patHash == txtHash) && check(txt, pat, offset))
	return offset;
    }

    // no match
    return -1;
  }


};

// Test harness
int main() {
  const char* txt = "aaa";
  const char* pat = "aaaa";
  Solution foo;
  const char* ret = foo.strStr(txt, pat);
  if (ret)
    cout << ret << endl;
  else 
    cout << "not found" << endl;

  return 0;
}
