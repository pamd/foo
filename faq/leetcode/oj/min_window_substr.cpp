/* Leetcode OJ: Given a string S and a string T, find the minimum window in S 
 * which will contain all the characters in T in complexity O(n).
 * For example, S = "ADOBECODEBANC", T = "ABC", minimum window is "BANC".
 * Note: If there is no such window in S that covers all characters in T, 
 * return the emtpy string "".
 * If there are multiple such windows, you are guaranteed that there will 
 * always be only one unique minimum window in S. */

#include <string>

using namespace std;

// 56ms for large dataset
class Solution {
public:
  string minWindow(string S, string T) { // S: source, T: target
    int hash_s[256];
    int hash_t[256];
    for (int i = 0; i < 256; i++) {
      hash_s[i] = 0;
      hash_t[i] = 0;
    }

    for (size_t i = 0; i < T.size(); i++) {
      int p = T[i];
      hash_t[p]++;
    }

    int start_min = -1;
    int end_min = -1;
    size_t tail = 0;
    int counter = 0;
    for (size_t i = 0; i < S.size(); i++) {
      int p = S[i];
      hash_s[p]++;
      if (hash_t[p] > 0 && hash_s[p] <= hash_t[p])
	counter++;
      if (counter == T.size()) {
	for (size_t j = tail; j <= i; j++) {
	  int p2 = S[j];
	  if (hash_s[p2] == hash_t[p2]) {
	    if (start_min == -1 || end_min - start_min > i - j) {
	      start_min = j;
	      end_min = i;
	    }
	    tail = j;
	    break;
	  }
	  else 
	    hash_s[p2]--;
	}
      }
    }

    if (start_min == -1)
      return string();
    return S.substr(start_min, end_min - start_min + 1);
  }
};
