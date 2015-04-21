/* Boyer-Moore substring search (mismatched character heuristic).
 * Based on the Java code on "Algorithms" 4th edition, page 772, 
 * by Robert Sedgewick.
 *
 * 28ms for Leetcode OJ large dataset.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int R = 256;

// Set up bad character shift table
void get_bad_char(const string& needle, vector<int>& bad_char) {
  int m = needle.size();
  for (int j = 0; j < m; j++) { // Can be optimized to "j < m - 1"
    int idx = needle[j];
    bad_char[idx] = j;
  }
}

// Search needle string in haystack string, 28ms for Leetcode OJ large dataset.
int search_algs(const string& haystack, const string& needle) {
  vector<int> bad_char(R, -1);
  get_bad_char(needle, bad_char);

  int N = haystack.size();
  int M = needle.size();
  int skip;
  // i: index of starting point of a possible match in haystack string
  // The following two "for" loops are awkward. 
  for (int i = 0; i <=  N - M; i += skip) {
    skip = 0;
    // j: index of needle char that is being matched
    for (int j = M - 1; j >= 0; j--) {
      if (haystack[i + j] == needle[j]) 
	continue;

      skip = j - bad_char[(int) haystack[i + j]];
      if (skip < 1) 
	skip = 1;
      break;
    }

    if (skip == 0) // found
      return i;    
  }

  return -1; // not found.
}

// dhu version: rewrote the two "for" loops in search()
// 20ms for Leetcode OJ large dataset.
int search_dhu(const string& haystack, const string& needle) {
  vector<int> bad_char(R, -1);
  get_bad_char(needle, bad_char);

  int n = haystack.size();
  int m = needle.size();
  int i = 0;     // index of haystack string
  int j = m - 1; // index of needle string
  while (i <= n - m) {
    if (haystack[i + j] == needle[j]) {  // Compare haystack[i + j] with needle[j]
      --j;
      if (j < 0)
	return i;
    }
    else {
      int idx = haystack[i + j];
      int skip = j - bad_char[idx];
      if (skip <= 0) 
	skip = 1;
      i += skip;
      j = m - 1;
    }
  }

  return -1; // not found.
}

// Test harness
int main() {
  string haystack("abdanpanmaneret");
  string needle("anpanman");

  cout << search_dhu(haystack, needle) << endl;

  return 0;
}
