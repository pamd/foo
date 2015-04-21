// Extension problem: Given an input array A, find the longest subarray 
// whose sum is euqal to or larger than a given k.
// 
// Solution #1:
// Suppose x1 and x2 are two elements in prefix_sum, and x1 is on the left
// side of x2, when x2 - x1 >= k, we have x2 >= x1 + k. If x3 is an element 
// between x1 and x2, and x3 <= x2, then we will never consider x3 as the 
// ending point of a candidate subarray, because if x3 - x1 >= k, then
// we must have x2 - x1 >= k, and the distance between x1 and x2 is always
// longer than the distance between x1 and x3. This is exactly why we can 
// scan the prefix_sum from right to left and build a sorted prefix2 array.
//
// Solution #2:
// Alternatively, since x2 - x1 >= k, we will get: x1 <= x2 - k. 
// Suppose x3 is an element between x1 and x2, and x3 >= x1, then we will
// never consider x3 as the starting point of a candidate subarray, because
// if x2 - x3 >= k, then we must have x2 - x1 >= k, and the distance between 
// x1 and x2 is always longer than the distance between x3 and x2. This is
// the reason why we can build a sorted prefix2 array by scanning prefix_sum 
// from left to right. This idea is implemented in dhu_longest_larger_equal2().
//

#include <iostream>
#include <numeric>
#include <cassert>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

// Helper function for dhu_longest_larger_equal().
// It returns the index of the right-most element in an reversely sorted 
// input vector v whose value is equal to or larger than input target k.
// Return -1 if no such element exists in v.
int bsearch_last_larger_equal(const vector<int>& v, int k) {
  int left = 0;
  int right = v.size() - 1;
  int result = -1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (v[mid] >= k) {
      result = mid;
      left = mid + 1;
    }
    else {
      right = mid - 1;
    }
  }

  return result;
}

// Solution #1    
pair<int, int> larger_equal_nlgn_1(const vector<int>& A, int k) {
  // Build the prefix sum according to A
  vector<int> prefix_sum;
  partial_sum(A.begin(), A.end(), back_inserter(prefix_sum));

  vector<int> prefix2(prefix_sum);
  // Scan from right to left to build reverly sorted max prefix array
  for (int i = prefix2.size() - 2; i >= 0; --i) 
    prefix2[i] = max(prefix2[i], prefix2[i + 1]);

  // Left to right: min prefix. THIS IS NOT CORRECT!
  //for (int i = 1; i < (int) prefix2.size(); ++i) 
  // prefix2[i] = min(prefix2[i], prefix2[i - 1]);

  // Now elements in prefix2 are sorted in reverse order. 
   
  pair<int, int> arr_idx(0, -1);
  int tmp = bsearch_last_larger_equal(prefix2, k);
  arr_idx.second = tmp;
  for (int i = 0; i < (int) prefix2.size(); i++) {
    tmp = bsearch_last_larger_equal(prefix2, prefix_sum[i] + k);
    if (tmp - i - 1 > arr_idx.second - arr_idx.first) {
      arr_idx.first = i + 1;
      arr_idx.second = tmp;
    }
  }

  return arr_idx; 
}

// Binary search function written for dhu_longest_larger_equal2().
// It returns the index of the left-most element in an input reversely
// sorted array v whose value is less than or equal to input target k.
// Return -1 if no such element exists in v.
int bsearch_first_less_equal(const vector<int>& v, int k) {
  int result = -1;
  int left = 0;
  int right = v.size() - 1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (v[mid] <= k) {
      result = mid;
      right = mid - 1;
    }
    else 
      left = mid + 1;
  }

  return result;
}

// Solution #2
pair<int, int> larger_equal_nlgn_2(const vector<int>& A, int k) {
  // Build the prefix sum according to A
  vector<int> prefix_sum;
  partial_sum(A.begin(), A.end(), back_inserter(prefix_sum));

  // Scan from left to right to build a reversely sorted min prefix array
  // The following loop also sets arr_idx to the longest range of subarray 
  // that starts from the first element and whose sum >= k.  
  vector<int> prefix2(prefix_sum);
  pair<int, int> arr_idx(0, -1);
  for (int i = 0; i < (int) prefix2.size(); ++i) {
    if (i > 0) {
      prefix2[i] = min(prefix2[i], prefix2[i - 1]);
    }

    if (prefix_sum[i] >= k) { // Set ending point of arr_idx.
      arr_idx.second = i;
    }
  }

  // Now elements in prefix2 are sorted in reverse order. 
   
  // Consider each i as the ending point of subarray, find the 
  // starting point index tmp so that prefix_sum[i] - prefix_sum[tmp] >= k.
  for (int i = 1; i < (int) prefix2.size(); i++) {
    int tmp = bsearch_first_less_equal(prefix2, prefix_sum[i] - k);
    if (tmp != -1 && i - tmp - 1 > arr_idx.second - arr_idx.first) {
      arr_idx.first = tmp + 1;
      arr_idx.second = i;
    }
  }

  return arr_idx; 
}

