/* Find the LONGEST subarray whose sum is larger than or equal to k.
 * Time and space complexity: O(n).
 */

#include <iostream>
#include <numeric>
#include <cassert>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

// Approach #1: Find all possible ending indexes, 
// then try each prefix sum element as the starting point.
pair<int, int> larger_equal_n_1(const vector<int>& A, int k) {
  // Build the prefix sum according to A
  vector<int> prefix_sum;
  partial_sum(A.begin(), A.end(), back_inserter(prefix_sum));

  pair<int, int> ret(0, -1);
  // If the last element >= k, we are done.
  if (prefix_sum.back() >= k) {
    ret.second = A.size() - 1;
    return ret;
  }

  // Scan prefix_sum from right to left, keep track of INDEXes of 
  // consecutively increaing elements, which are possible ending points.
  vector<int> ends;
  ends.push_back(prefix_sum.size() - 1);
  for (int i = prefix_sum.size() - 2; i >= 0; i--) {
    if (prefix_sum[i] > prefix_sum[ends.back()])
      ends.push_back(i);
    
    if (prefix_sum[i] >= k && ret.second == -1)
      ret.second = i;
  }

  // Now scan prefix_sum from left to right, try each element as 
  // the starting point so that the subarray sum >= k.
  int start_idx = 0;
  while (start_idx < (int) prefix_sum.size() && ends.size()) {
    int end_idx = ends.back();
    if (end_idx <= start_idx)
      ends.pop_back();
    else if (prefix_sum[end_idx] - prefix_sum[start_idx] >= k) {
      if (end_idx - start_idx - 1 > ret.second - ret.first) {
	ret.first = start_idx + 1;
	ret.second = end_idx;
      }
      ends.pop_back();
    }
    else { // if (prefix_sum[ends_idx] - prefix_sum[start_idx] < k)
      start_idx++;
    }
  }

  return ret;
}

// Approach #2: Find all possible starting indexes, 
// then try each prefix sum element as the ending point.
pair<int, int> larger_equal_n_2(const vector<int>& A, int k) {
  // Build the prefix sum according to A
  vector<int> prefix_sum;
  partial_sum(A.begin(), A.end(), back_inserter(prefix_sum));

  pair<int, int> ret(0, -1);
  // If A[0] >= k, update ret.
  if (A[0] >= k) {
    ret.second = 0;
  }

  // Scan prefix_sum from left to right, keep track of INDEXes of 
  // consecutively decreasing elements, which are possible starting points.
  vector<int> starts;
  starts.push_back(0);
  for (int i = 0; i < (int) prefix_sum.size(); i++) {
    if (prefix_sum[i] < prefix_sum[starts.back()])
      starts.push_back(i);
    
    if (prefix_sum[i] >= k)
      ret.second = i;
  }

  // Now scan prefix_sum from right to left, try each element as 
  // the ending point so that the subarray sum >= k.
  int end_idx = prefix_sum.size() - 1;
  while (end_idx >= 0 && starts.size()) {
    int start_idx = starts.back();
    if (end_idx <= start_idx)
      starts.pop_back();
    else if (prefix_sum[end_idx] - prefix_sum[start_idx] >= k) {
      if (end_idx - start_idx - 1 > ret.second - ret.first) {
	ret.first = start_idx + 1;
	ret.second = end_idx;
      }
      starts.pop_back();
    }
    else { // if (prefix_sum[ends_idx] - prefix_sum[start_idx] < k)
      end_idx--;
    }
  }

  return ret;
}

// Approach #3: Find all possible starting indexes AND all possible 
// ending indexes, then scan the two vectors from left side.
pair<int, int> larger_equal_n_3(const vector<int>& A, int k) {
  // Build the prefix sum according to A
  vector<int> prefix_sum;
  partial_sum(A.begin(), A.end(), back_inserter(prefix_sum));

  pair<int, int> ret(0, -1);
  // If the last element >= k, we are done.
  if (prefix_sum.back() >= k) {
    ret.second = A.size() - 1;
    return ret;
  }

  // Find all possible starting indexes.
  vector<int> starts;
  starts.push_back(0);
  for (int i = 0; i < (int) prefix_sum.size(); i++) {
    if (prefix_sum[i] < prefix_sum[starts.back()])
      starts.push_back(i);
  }

  // Find all possible ending indexes.
  vector<int> ends;
  ends.push_back(prefix_sum.size() - 1);
  for (int i = prefix_sum.size() - 2; i >= 0; i--) {
    if (prefix_sum[i] > prefix_sum[ends.back()])
      ends.push_back(i);
    
    if (prefix_sum[i] >= k && ret.second == -1)
      ret.second = i;
  }

  // Reverse elements in ends so that prefix_sum[ends[0]],
  // prefix_sum[ends[1]], ... are decreasing.
  // Note that we do NOT have to reverse it, but I find that 
  // reversing it makes the code easier to write and understand.
  reverse(ends.begin(), ends.end());

  // Now scan starts and ends from left side, try each pair 
  // as the range of target subarray range. 
  size_t si = 0;
  size_t ei = 0;
  while (si < starts.size() && ei < ends.size()) {
    int start_idx = starts[si];
    int end_idx = ends[ei];
    if (end_idx <= start_idx)
      ei++;
    else if (prefix_sum[end_idx] - prefix_sum[start_idx] >= k) {
      if (end_idx - start_idx - 1 > ret.second - ret.first) {
	ret.first = start_idx + 1;
	ret.second = end_idx;
      }
      ei++;
    }
    else
      si++;
  }

  return ret;
}

// Approach #4: Find all possible starting indexes AND all possible 
// ending indexes, then scan the two vectors from left side.
// This approach is identical to #3 until scanning "starts" and "ends".
pair<int, int> larger_equal_n_4(const vector<int>& A, int k) {
  // Build the prefix sum according to A
  vector<int> prefix_sum;
  partial_sum(A.begin(), A.end(), back_inserter(prefix_sum));

  pair<int, int> ret(0, -1);
  // If the last element >= k, we are done.
  if (prefix_sum.back() >= k) {
    ret.second = A.size() - 1;
    return ret;
  }

  // Find all possible starting indexes.
  vector<int> starts;
  starts.push_back(0);
  for (int i = 0; i < (int) prefix_sum.size(); i++) {
    if (prefix_sum[i] < prefix_sum[starts.back()])
      starts.push_back(i);
  }

  // Find all possible ending indexes.
  vector<int> ends;
  ends.push_back(prefix_sum.size() - 1);
  for (int i = prefix_sum.size() - 2; i >= 0; i--) {
    if (prefix_sum[i] > prefix_sum[ends.back()])
      ends.push_back(i);
    
    if (prefix_sum[i] >= k && ret.second == -1)
      ret.second = i;
  }

  // Reverse elements in ends so that prefix_sum[ends[0]],
  // prefix_sum[ends[1]], ... are decreasing.
  // Note that we do NOT have to reverse it, but I find that 
  // reversing it makes the code easier to write and understand.
  reverse(ends.begin(), ends.end());

  // Now scan starts and ends from RIGHT side, try each pair 
  // as the range of target subarray range. 
  int si = starts.size() - 1;
  int ei = ends.size() - 1;
  while (si >= 0 && ei >= 0) {
    int start_idx = starts[si];
    int end_idx = ends[ei];
    if (end_idx <= start_idx)
      si--;
    else if (prefix_sum[end_idx] - prefix_sum[start_idx] >= k) {
      if (end_idx - start_idx - 1 > ret.second - ret.first) {
	ret.first = start_idx + 1;
	ret.second = end_idx;
      }
      si--;
    }
    else
      ei--;
  }

  return ret;
}
