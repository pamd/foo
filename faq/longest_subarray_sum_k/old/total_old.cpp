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
 * See: faq/leetcode_blog/max_distance_leetcode.cpp.
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
pair<int, int> dhu_longest_less_equal(const vector<int> &A, int k) {
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

// MITBBS O(n) solution based on the code by iverson1407 (idea from vimabc):
// http://www.mitbbs.com/article_t/JobHunting/32150635.html
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

// dhu_less_equal_O_n: based on idea from MITBBS
pair<int, int> dhu_less_equal_O_n1(const vector<int>& A, int k) {
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

// Alternative O(n) solution: 
// First get all possible starting points by scanning from left to right.
pair<int, int> dhu_less_equal_O_n2(const vector<int>& A, int k) {
  vector<int> prefix_sum;
  partial_sum(A.begin(), A.end(), back_inserter(prefix_sum));

  int length = A.size();

  // Find all possible ending points by scanning from right to left
  // and keeping track of indexes of decreasing elements in prefix sum.
  // NOTE that here we keep track of INDEXES instead of values of 
  // decreasing elements.
  vector<int> starts;
  starts.push_back(0);
  pair<int, int> ret(0, -1);
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

// Brute force method to get the longest subarray whose sum is <= k.
// Scan array from left to right.
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
pair<int, int> dhu_longest_larger_equal1(const vector<int>& A, int k) {
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

// Solution #2 to "Finding the longest subarray whose sum 
// is larger than or equal to a given value k". 
// See second part of comments before dhu_longest_larger_equal1() 
// for details on why this idea works.
pair<int, int> dhu_longest_larger_equal2(const vector<int>& A, int k) {
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

// dhu O(n) solution to find longest subarray whose sum is >= k
pair<int, int> dhu_larger_equal_O_n1(const vector<int>& A, int k) {
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

// Alternative dhu O(n) solution to find longest subarray whose sum is >= k.
// The code is (sort of) symmetric to dhu_larger_equal_O_n2.
pair<int, int> dhu_larger_equal_O_n2(const vector<int>& A, int k) {
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

// Test harness
int main(int argc, char *argv[]) {
  srand(time(nullptr));

  // All elements in input vector will be in this range: [-(range-1), range-1]
  int range = 200; 
  int iteration = 10000;  // Number of random test cases
  int n = 100;          // Number of elements in input vector

  for (int times = 0; times < iteration; ++times) {
    int k = rand() % 20;
    vector<int> A;
    for (int i = 0; i < n; ++i) 
      A.emplace_back(((rand() & 1) ? -1 : 1) * rand() % range);

    //pair<int, int> epi = epi_longest_less_equal(A, k);
    //epi_check_less_equal(A, epi, k);
    //cout << "EPI check passed" << endl;

    //pair<int, int> dhu = dhu_longest_less_equal(A, k);

    pair<int, int> foo = dhu_larger_equal_O_n2(A, k);
    pair<int, int> brute = brute_larger_equal(A, k);

    //pair<int, int> dhu = dhu_longest_larger_equal2(A, k);
    //pair<int, int> brute = brute_larger_equal(A, k);

    assert(foo.second - foo.first == brute.second - brute.first);

    if (foo == brute) {
      //cout << "Check passed: " << brute.first << " " << brute.second << endl << endl;
    }
    else {
      /*
      cout << "Check failed" << endl;
      cout << "A: ";
      for (size_t i = 0; i < A.size(); i++) 
	cout << A[i] << ' ';
      cout << endl;

      cout << "k: " << k << endl;
      cout << "foo: " << foo.first << ' ' << foo.second << endl;
      cout << "ans: " << brute.first << ' ' << brute.second << endl;
      cout << endl;
      */
    }

  }
  

  /*
  // dhu individual test cases
  // int a[] = { 0, 0, 1, 3, 6 };
  // int k = 4;

  //int a[] = { 3, -4, -6, 7, 2 }; 
  // k = 5;

  int a[] = { 6, 1, -5, -6, 9 };
  int k = 11;

  vector<int> A(a, a + sizeof(a) / sizeof(int));
  pair<int, int> foo = dhu_less_equal_O_n(A, k);
  pair<int, int> brute = brute_less_equal(A, k);

  if (foo != brute) {
    cout << "foo: " << foo.first << ' ' << foo.second << endl;
    cout << "ans: " << brute.first << ' ' << brute.second << endl;
  }
  */

  return 0;
}
