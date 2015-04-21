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

// MITBBS O(n) solution based on the code by iverson1407 (idea from vimabc):
// http://www.mitbbs.com/article_t/JobHunting/32150635.html
// See ref/mitbbs.cpp.
//
// It uses two accessory vectors, one holds all possible starting points,
// the other holds all possible ending points. 
pair<int, int> mitbbs_less_equal(vector<int>& A, int k) {
  int length = A.size();
  vector<int> prefix_sum(length + 1, 0);
  for(int i = 1; i <= length; i++)
    prefix_sum[i] = prefix_sum[i - 1] + A[i - 1];

  // Find all possible starting points by scanning from left to right
  // and keeping track of increasing elements in prefix sum.
  vector<int> starts(length + 1);
  starts[0] = 0;
  for (int i = 1; i < length + 1; i++) {
    starts[i] = max(starts[i - 1], prefix_sum[i]);
  }

  // Find all possible ending points by scanning from right to left
  // and keeping track of decreasing elements in prefix sum.
  vector<int> ends(length + 1);
  ends[length] = prefix_sum[length];
  for (int i = length - 1 ; i >= 0; i--) {
    ends[i] = min(ends[i + 1], prefix_sum[i]);
  }

  int start_idx = 0;
  int end_idx = 0;
  pair<int, int> ret(0, -1);
  while (start_idx != length + 1 && end_idx != length + 1) {
    if (ends[end_idx] - starts[start_idx] <= k) {
      // Keep optimal result updated
      if (end_idx - 1 - start_idx > ret.second - ret.first) {
	ret.first = start_idx;
	ret.second = end_idx - 1;
      }
      end_idx++;
    }
    else
      start_idx++;        
  }

  return ret;
}

// dhu approach #1: less_equal in O(n) time, based on idea from MITBBS.
// Only find possible ENDING points by scanning from right to left.
pair<int, int> less_equal_n_1(const vector<int>& A, int k) {
  vector<int> prefix_sum;
  partial_sum(A.begin(), A.end(), back_inserter(prefix_sum));

  int length = A.size();

  // Find all possible ending points by scanning from right to left
  // and keeping track of indexes of decreasing elements in prefix sum.
  // NOTE that here we keep track of INDEXES instead of values of 
  // decreasing elements.
  vector<int> ends;
  ends.push_back(length - 1);
  pair<int, int> ret(0, -1);
  if (prefix_sum.back() <= k) {
    ret.second = length - 1;
    return ret;
  }

  for (int i = length - 2; i >= 0; i--) {
    if (prefix_sum[i] < prefix_sum[ends.back()])
      ends.push_back(i);

    // Get the longest subarray that starts from A[0] and whose sum <= k.
    if (prefix_sum[i] <= k && ret.second == -1)
      ret.second = i;
  }

  // Now scan prefix_sum from left to right. Try each element as the starting point,
  // then find the right-most ending point so that the subarray's sum <= k.
  int start_idx = 0;
  while (start_idx < length && ends.size()) {
    int end_idx = ends.back();
    if (start_idx >= end_idx)
      ends.pop_back();
    else if (prefix_sum[end_idx] - prefix_sum[start_idx] <= k) {
      if (end_idx - start_idx - 1 > ret.second - ret.first) {
	ret.first = start_idx + 1;
	ret.second = end_idx;
      }
      ends.pop_back();
    }
    else {
      start_idx++;
    }
  }

  return ret;
}

// dhu approach #2 with O(n) time. 
// Find all possible STARTING points by scanning from left to right.
pair<int, int> less_equal_n_2(const vector<int>& A, int k) {
  vector<int> prefix_sum;
  partial_sum(A.begin(), A.end(), back_inserter(prefix_sum));

  int length = A.size();

  // Find all possible starting points by scanning prefix sum from left to right,
  // and keeping track of indexes of increasing elements in prefix sum.
  // NOTE that here we keep track of INDEXES instead of values of 
  // increasing elements.
  vector<int> starts;
  starts.push_back(0);
  pair<int, int> ret(0, -1);
  if (A[0] <= k)
    ret.second = 0;
  for (int i = 1; i < length; i++) {
    if (prefix_sum[i] > prefix_sum[starts.back()])
      starts.push_back(i);

    // Get the longest subarray that starts from A[0] and whose sum <= k.
    if (prefix_sum[i] <= k)
      ret.second = i;
  }

  // Now scan prefix_sum from right to left. Try each element as the ending point,
  // then find the left-most starting point so that the subarray's sum <= k.
  int end_idx = length - 1;
  while (end_idx >= 0 && starts.size()) {
    int start_idx = starts.back();
    if (start_idx >= end_idx)
      starts.pop_back();
    else if (prefix_sum[end_idx] - prefix_sum[start_idx] <= k) {
      if (end_idx - start_idx - 1 > ret.second - ret.first) {
	ret.first = start_idx + 1;
	ret.second = end_idx;
      }
      starts.pop_back();
    }
    else { // if (prefix_sum[end_idx] - prefix_sum[start_idx] > k) 
      end_idx--;
    }
  }

  return ret;
}

// dhu approach #3: Use two vectors, one holds INDEXes of all starting elements,
// the other holds INDEXes of all possible ending elements. 
// Then we start scanning the two vectors from the left side to find the target.
// This approach is similar to the mitbbs version, but the two vectors have less elements.
pair<int, int> less_equal_n_3(const vector<int>& A, int k) {
  vector<int> prefix_sum;
  partial_sum(A.begin(), A.end(), back_inserter(prefix_sum));

  int length = A.size();
  // Find all possible starting points by scanning prefix_sum from left to right.
  vector<int> starts;
  starts.push_back(0);
  for (int i = 1; i < length; i++) {
    if (prefix_sum[i] > prefix_sum[starts.back()])
      starts.push_back(i);
  }

  // Find all possible ending points by scanning prefix sum from right to left,
  vector<int> ends;
  ends.push_back(length - 1);
  pair<int, int> ret(0, -1);
  if (prefix_sum.back() <= k) {
    ret.second = length - 1;
    return ret;
  }

  for (int i = length - 2; i >= 0; i--) {
    if (prefix_sum[i] < prefix_sum[ends.back()])
      ends.push_back(i);

    // Get the longest subarray that starts from A[0] and whose sum <= k.
    if (prefix_sum[i] <= k && ret.second == -1)
      ret.second = i;
  }

  // Reverse the elements in ends so that prefix_sum[ends[0]], 
  // prefix_sum[ends[1]], ... are increasing. 
  // NOTE THAT we do NOT have to reverse it, but personally I feel
  // that this operation makes the code easier to write and understand.
  reverse(ends.begin(), ends.end());

  // Scan both starts and ends from LEFT side, 
  // and try each pair as a subarray range.
  size_t si = 0;
  size_t ei = 0;
  while (si < starts.size() && ei < ends.size()) {
    int start_idx = starts[si];
    int end_idx = ends[ei];
    if (end_idx <= start_idx) {
      ei++;
    }
    else if (prefix_sum[end_idx] - prefix_sum[start_idx] <= k) {
      if (ret.second - ret.first < end_idx - start_idx - 1) {
	ret.first = start_idx + 1;
	ret.second = end_idx;
      }
      ei++;
    }
    else {
      si++;
    }
  }

  return ret;
}

// dhu approach #4: Use two vectors, one holds INDEXes of all starting elements,
// the other holds INDEXes of all possible ending elements. 
// But this time we start scanning the two vectors from the end to find the target.
// This approach is identical to approach #3 until the scanning of "starts" and "ends".
pair<int, int> less_equal_n_4(const vector<int>& A, int k) {
  vector<int> prefix_sum;
  partial_sum(A.begin(), A.end(), back_inserter(prefix_sum));

  int length = A.size();
  // Find all possible starting points by scanning prefix_sum from left to right.
  vector<int> starts;
  starts.push_back(0);
  for (int i = 1; i < length; i++) {
    if (prefix_sum[i] > prefix_sum[starts.back()])
      starts.push_back(i);
  }

  // Find all possible ending points by scanning prefix sum from right to left,
  vector<int> ends;
  ends.push_back(length - 1);
  pair<int, int> ret(0, -1);
  if (prefix_sum.back() <= k) {
    ret.second = length - 1;
    return ret;
  }

  for (int i = length - 2; i >= 0; i--) {
    if (prefix_sum[i] < prefix_sum[ends.back()])
      ends.push_back(i);

    // Get the longest subarray that starts from A[0] and whose sum <= k.
    if (prefix_sum[i] <= k && ret.second == -1)
      ret.second = i;
  }

  // Reverse the elements in ends so that prefix_sum[ends[0]], 
  // prefix_sum[ends[1]], ... are increasing. 
  reverse(ends.begin(), ends.end());

  // Scan both starts and ends from RIGHT side, 
  // and try each pair as a subarray range.
  int si = starts.size() - 1;
  int ei = ends.size() - 1;
  while (si >= 0 && ei >= 0) {
    int start_idx = starts[si];
    int end_idx = ends[ei];
    if (end_idx <= start_idx) {
      si--;
    }
    else if (prefix_sum[end_idx] - prefix_sum[start_idx] <= k) {
      if (ret.second - ret.first < end_idx - start_idx - 1) {
	ret.first = start_idx + 1;
	ret.second = end_idx;
      }
      si--;
    }
    else {
      ei--;
    }
  }

  return ret;
}
