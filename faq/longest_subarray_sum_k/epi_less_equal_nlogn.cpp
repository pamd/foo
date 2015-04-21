/* Find the LONGEST subarray whose sum is less than or equal to k.
 * Note that this problem is TOTALLY DIFFERENT from "Finding a subarray 
 * whose sum is closest to k" problem.
 * In this problem, once the subarray's sum <= k, we care more about 
 * the length of subarray; in the latter problem, we only care 
 * how close the subarray's sum is from k. 
 *
 * After we get prefix sum array, this problem becomes a generation of the 
 * following problem in mitbbs, in which k = 0.
 *
 * "Given an unsorted array, find the longest distance between two elements 
 * x1 and x2 in the array so that x1 is on left side of x2, and x1 < x2."  
 *
 * See: ref/darksteel.cpp.
 */

#include <iostream>
#include <numeric>
#include <cassert>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

// O(n*logn) solution in EPI book.
//
// dhu note: Suppose x1 and x2 are two elements in prefix_sum, and x2 is on 
// right side of x1, we try to find the maximum distance between x2 and x1 so 
// that x2 - x1 <= k, aka. x2 <= x1 + k. Now suppose x3 is an element between x1 
// and x2, and x3 > x2, we will never need to consider x3 as the ending point of 
// a candidate subarray, because if x3 can be the ending point, aka. x3 - x1 <= k, 
// then we must have x2 - x1 <= k too, and the distance between x1 and x2 is longer 
// than the distance between x1 and x3. This is exactly why we can build a sorted 
// minimum prefix array by scanning prefix_sum from right to left.   
//
// Alternatively, since x2 - x1 <= k, we can get: x1 >= x2 - k.
// Now suppose x3 is another element between x1 and x2, and x3 < x1, then we will 
// never need to consider x3 as the starting point of a candidate subarray, because
// if x2 - x3 <= k, then we must have x2 - x1 <= k, and the distance between x1 and x2 
// is longer than the distance between x3 and x2. This is exactly why we can build the 
// sorted max_prefix by scanning prefix_sum from left to right. 
// This idea is implemented in: dhu_longest_less_equal() function.
//
pair<int, int> epi_longest_less_equal(const vector<int> &A, int k) {
  // Build the prefix sum according to A.
  vector<int> prefix_sum;
  partial_sum(A.begin(), A.end(), back_inserter(prefix_sum));

  // Scan from right to left to build sorted min prefix
  vector<int> min_prefix(prefix_sum);
  for (int i = min_prefix.size() - 2; i >= 0; --i) 
    min_prefix[i] = min(min_prefix[i], min_prefix[i + 1]);
  // Now elements in min_prefix are non-decreasing from left to right.    

  pair<int, int> arr_idx(0, 0);
  // Now set arr_idx as the index range of the subarray that starts from 
  // the first element and whose sum is less than or equal to k.

  // std::upper_bound() returns min element in min_prefix that is larger than k.
  vector<int>::iterator upper = upper_bound(min_prefix.begin(), min_prefix.end(), k);

  // Note that if upper is min_prefix.end(), then arr_idx.second will be -1, 
  // but this does not invalidate the program's result.
  arr_idx.second = upper - min_prefix.begin() - 1;

  // For each i, check whether A[i+1] can be the starting point 
  // of a subarray whose sum is less than or equal to k. 
  // The ending point of the subarray will be found by std::upper_bound().  
  for (int i = 0; i < (int) prefix_sum.size(); ++i) {
    upper = upper_bound(min_prefix.begin(), min_prefix.end(), k + prefix_sum[i]);
    int idx = upper - min_prefix.begin() - 1;
    if (idx - i - 1 > arr_idx.second - arr_idx.first) 
      arr_idx = {i + 1, idx};
  }

  return arr_idx;
}

// O(n^2) checking answer
void epi_check_less_equal(const vector<int>& A, const pair<int, int>& ans, int k) {
  vector<int> sum(A.size() + 1, 0);
  sum[0] = 0;
  for (size_t i = 0; i < A.size(); ++i) 
    sum[i + 1] = sum[i] + A[i];
  
  // If the index range in ans is valid 
  if (ans.first != -1 && ans.second != -1) {
    int s = 0;
    // s is the sum of subarray determined by ans
    for (int i = ans.first; i <= ans.second; ++i) 
      s += A[i];
    
    // Make sure s <= k
    assert(s <= k);

    // Make sure that any possible subarray of A whose sum is 
    // less than or equal to k is not longer than ans.  
    for (size_t i = 0; i < sum.size(); ++i) {
      for (size_t j = i + 1; j < sum.size(); ++j) {
        if (sum[j] - sum[i] <= k) 
          assert((int) (j - i) <= (ans.second - ans.first + 1));
      }
    }
  } 

  // If the index range in ans is invalid, make sure that 
  // all subarrays of A have sums larger than k.
  else {
    for (size_t i = 0; i < sum.size(); ++i) {
      for (size_t j = i + 1; j < sum.size(); ++j) 
        assert(sum[j] - sum[i] > k);
    }
  }

}

// dhu solution: Use max_prefix which is built by scanning prefix_sum 
// from left to right, then use std::lower_bound() to find starting index.
// See second part of comments before epi_longest_less_equal() for details
// on why this idea will work. 
pair<int, int> longest_less_equal_nlgn(const vector<int> &A, int k) {
  // Build the prefix sum according to A.
  vector<int> prefix_sum;
  partial_sum(A.begin(), A.end(), back_inserter(prefix_sum));

  // Scan from left to right to build sorted max prefix
  vector<int> max_prefix(prefix_sum);
  pair<int, int> arr_idx(0, -1);
  // Unlike EPI solution, the following loop not only initializes max_prefix, 
  // but also sets arr_idx as the index range of the subarray that starts 
  // from the first element and whose sum is less than or equal to k.
  for (size_t i = 0; i < prefix_sum.size(); ++i) {
    if (i > 0) {
      max_prefix[i] = max(max_prefix[i], max_prefix[i - 1]);
    }

    if (prefix_sum[i] <= k) {  // Set ending point of arr_idx 
      arr_idx.second = i;
    }
  }

  // Now elements in max_prefix are non-decreasing from left to right.    

  // For each i from 1 to the end, check whether A[i] can be the ending point 
  // of a subarray whose sum is less than or equal to k. 
  // The starting point of the subarray will be found by std::lower_bound().  
  vector<int>::iterator lower;
  for (int i = 1; i < (int) prefix_sum.size(); ++i) {
    lower = lower_bound(max_prefix.begin(), max_prefix.begin() + i, prefix_sum[i] - k);
    int idx = lower - max_prefix.begin() + 1;
    if (i - idx > arr_idx.second - arr_idx.first) 
      arr_idx = {idx, i};
  }

  return arr_idx;
}

