/* Leetcode OJ: Given a string, find the length of the longest substring 
 * without repeating characters. 
 * For example, the longest substring without repeating letters for 
 * "abcabcbb" is "abc", whose length is 3. 
 * For "bbbbb" the longest substring is "b", whose length is 1.
 */

#include <iostream>
#include <string>

using namespace std;

// 48ms for large dataset
class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    if (s.size() == 0)
      return 0;

    int positions[256];
    for (int i = 0; i < 256; i++) 
      positions[i] = -1; 
    
    int c = s[0];
    positions[c] = 0;
    int start = 0;
    int length = 1;
    for (int i = 1; i < (int) s.size(); i++) {
      c = s[i];
      // c is not found between start and i - 1 in s
      if (positions[c] < 0) {  
	if (i - start + 1 > length)
	  length = i - start + 1;
      }
      // c is found between start and i - 1 in s
      else {
	for (int j = start; j < positions[c]; j++) {
	  int j2 = s[j];
	  positions[j2] = -1;
	}
	start = positions[c] + 1;
      }
      positions[c] = i;
    }

    return length;
  }

};

/* An earlier solution by dhu: 40ms for large dataset.
 * It also records the starting and ending indices of the longest 
 * substring that has unique characters. */
int get_len(const string& str, int& start_idx, int& end_idx)
{
  int position[256];
  for (int i = 0; i < 256; i++) 
    position[i] = -1;
  
  int max_len = 0;
  int start = 0;
  for (size_t i = 0; i < str.size(); i++) {
    int c = str[i];
    // A new non-repeated character is found!
    if (position[c] < start) { // key reason why this algorithm is faster!!!
      position[c] = i;
      int tmp = i - start + 1;
      if (tmp > max_len) {
	max_len = tmp;
	start_idx = start;
	end_idx = i;
      }
    }
    else {
      start = position[c] + 1;
      position[c] = i;
    }
  }

  return max_len;
}

/* Leetcode implementation: 40ms.
 * Copied from:
 * http://www.leetcode.com/2011/05/longest-substring-without-repeating-characters.html
 */
int leetcode(string s) {
  int n = s.length();
  int i = 0, j = 0;
  int maxLen = 0;
  bool exist[256] = { false };
  while (j < n) {
    if (exist[s[j]]) {
      maxLen = max(maxLen, j - i);
      while (s[i] != s[j]) {
        exist[s[i]] = false;
        i++;
      }
      i++;
      j++;
    } 
    else {
      exist[s[j]] = true;
      j++;
    }
  }

  maxLen = max(maxLen, n-i);
  return maxLen;
}

// Test harness
int main() {
  Solution foo;
  cout << foo.lengthOfLongestSubstring("abcabcbb") << endl;

  return 0;
}
