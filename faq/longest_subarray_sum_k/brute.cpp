/* Brute force method. Time complexity: O(n^3).
 */

#include <iostream>
#include <numeric>
#include <cassert>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

// Brute force method to get the longest subarray whose sum is <= k.
pair<int, int> brute_less_equal(const vector<int>& A, int k) {
  pair<int, int> result(0, -1);
  for (int i = 0; i < (int) A.size(); i++) {
    for (int j = i; j < (int) A.size(); j++) {
      int sum = accumulate(A.begin() + i, A.begin() + j + 1, 0);
      if (sum <= k && j - i > result.second - result.first) {
	result.first = i;
	result.second = j;
      }
    }
  }

  return result;
}

// Brute force method to get the longest subarray whose sum is >= k
pair<int, int> brute_larger_equal(const vector<int>& A, int k) {
  pair<int, int> result(0, -1);
  for (int i = 0; i < (int) A.size(); i++) {
    for (int j = i; j < (int) A.size(); j++) {
      int sum = accumulate(A.begin() + i, A.begin() + j + 1, 0);
      if (sum >= k && j - i > result.second - result.first) {
	result.first = i;
	result.second = j;
      }
    }
  }

  return result;
}

// Check whether an input less_equal answer "ans" 
// is consistent with input longest length "max_len". 
bool check_less_equal(const vector<int>& A, int max_len, int k, pair<int, int> ans) {
  if (max_len < 0 && ans.second - ans.first < 0)
    return true;

  if (max_len != ans.second - ans.first)
    return false;

  int sum = accumulate(A.begin() + ans.first, A.begin() + ans.second + 1, 0);
  return sum <= k;
}

// Check whether an input less_equal answer "ans" 
// is consistent with input longest length "max_len". 
bool check_larger_equal(const vector<int>& A, int max_len, int k, pair<int, int> ans) {
  if (max_len < 0 && ans.second - ans.first < 0)
    return true;

  if (max_len != ans.second - ans.first)
    return false;

  int sum = accumulate(A.begin() + ans.first, A.begin() + ans.second + 1, 0);
  return sum >= k;
}
