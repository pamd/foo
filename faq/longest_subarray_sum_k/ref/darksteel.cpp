/* Given an array A of integers, find the maximum of j-i in which A[i] < A[j].
 * Ref:
 * http://www.leetcode.com/2011/05/a-distance-maximizing-problem.html#comment-1122
 * http://www.mitbbs.com/article_t/JobHunting/31875095.html
 *
 *                      dhu note: 
 * ----------------------------------------------------------------------
 * The "for" loop in darksteel implementation is not intuitive. 
 * Improved in dhu().       
 * 
 * This problem is actually a specific case of a more general problem. 
 * See various implementatiosn in: 
 *    faq/epi/12_meta_algorithm/07_Longest_subarray_k.cpp
 *
 */

#include <iostream>
#include <vector>

using namespace std;

// Algorithm by darksteel, time and space complexity: O(n).
pair<int, int> darksteel(const vector<int> A) {
  vector<int> vi;
  vi.push_back(0);

  // Scan from left to right, and keep track of 
  // indexes of elements that are decreasing.
  for (size_t i = 1; i < A.size(); i++) {
    if (A[i] < A[vi.back()]) 
      vi.push_back(i);
  }
  // Now arr[vi[0]], arr[vi[1]], ... are sorted in reverse order

  pair<int, int> ans(0, 0);
  int curr_end = A.size() - 1;
  // Try each element in vi[] as a starting point, from right side to left side 
  for (int i = vi.size() - 1; i >= 0; i--) {
    int curr_start = vi[i];
    while (curr_end > curr_start) {
      // If curr_end is a valid ending index, we will update optimal result,
      // then get out of curnet "while" loop and try the next element in 
      // vi[] as the new starting point.
      if (A[curr_end] > A[curr_start]) {
	if (curr_end - curr_start > ans.second - ans.first) {
	  ans.first = curr_start;
	  ans.second = curr_end;
	}
	break;
      }

      // If curr_end is not a valid ending index, 
      // try curr_end-1 as the new ending index.
      curr_end--;
    }
  }

  return ans;
}

// dhu alternative solution: scan the input array from right to left.
// Time and space complexity is also O(n).
// After building the stack, because we try each element as a possible 
// starting point of the range, the result returned in this function 
// may be different from the one in darksteel(), but the length of
// range should be equal to each other.
pair<int, int> dhu(const vector<int>& A) {
  // Use std::vector to simulate a stack, which holds 
  // all indexes that may be used as the ending point.
  vector<int> ends; 
  ends.push_back(A.size() - 1); 

  // Scan input array from right to left, and keep track of indexes 
  // of those elements that are increasing. Suppose an element x is 
  // less than an element on its right side, then x will never be 
  // the ending point of the pair that we are looking for. 
  for (int i = A.size() - 2; i >= 0; i--) {
    if (A[i] > A[ends.back()])
      ends.push_back(i);
  }
  // Now arr[ends[0]], arr[ends[1]], ... are reversely sorted

  // Scan input array from left to right, try each element as the 
  // starting point of a pair in which A[end] > A[start]. 
  pair<int, int> result(0, 0);
  int start_idx = 0;
  while (start_idx < (int) A.size() && ends.size()) {
    int end_idx = ends.back();
    // If start_idx >= end_idx, pop out the top element in stack.  
    if (start_idx >= end_idx) {
      ends.pop_back();
    }
    else if (A[end_idx] > A[start_idx]) { 
      if (result.second - result.first < end_idx - start_idx) {
	result.first = start_idx;
	result.second = end_idx;
      }
      ends.pop_back();
    }
    // If A[end_idx] <= A[start_idx], then because all elements 
    // after end_idx are less than A[end_idx], we can never find 
    // a valid pair from start_idx, so we increment start_idx.
    else {  
      start_idx++;
    }
  }

  return result;
}

// dhu brute force O(n^2) method to confirm the answer. 
// Time complexity: O(n^2), space complexity: O(1).
// Because we try each element from left to right as the starting 
// point, the result will be always identical to the one from dhu(). 
pair<int, int> brute(const vector<int>& A) {
  pair<int, int> result(0, 0);
  for (int i = 0; i < (int) A.size(); i++) {
    for (int j = i + 1; j < (int) A.size(); j++) {
      if (A[j] > A[i] && j - i > result.second - result.first) {
	result.first = i;
	result.second = j;
      }
    }
  }

  return result;
}

// Test harness
int main() {
  srand(time(nullptr)); 
  int n = 500; // Length of input vector
  int range = 100; // Each element is in [-(range-1), range-1].  

  int iteration = 100;
  for (int times = 0; times < iteration; ++times) {
    vector<int> A;
    for (int i = 0; i < n; ++i) 
      A.emplace_back(((rand() & 1) ? -1 : 1) * rand() % range);

    pair<int, int> dark_ans = darksteel(A);
    //pair<int, int> dhu_ans = dhu(A);
    pair<int, int> brute_ans = brute(A);
    
    if (dark_ans.second - dark_ans.first == brute_ans.second - brute_ans.first) {
      //cout << "dhu check passed" << endl << endl;
    }
    else {
      cout << "check failed" << endl;
      cout << "A: ";
      for (size_t i = 0; i < A.size(); i++) 
	cout << A[i] << ' ';
      cout << endl;

      cout << "dark: " << dark_ans.first << ' ' << dark_ans.second << endl;
      cout << "ans: " << brute_ans.first << ' ' << brute_ans.second << endl;
      cout << endl;
    }

  }


  /* 
  //dhu individual test 
  //            0  1  2  3  4  5  6  7
  //int arr[] = { 4, 3, 5, 2, 1, 3, 2, 3 };

  //           0   1   2   3   4   5   6  7   8   9
  int arr[] = {34, 26, 26, 32, 33, 24, 5, 23, 12, 23};

  int len = sizeof(arr) / sizeof(int);

  vector<int> A(arr, arr + len);

  pair<int, int> dark_ans = darksteel(A);
  cout << "darksteel: " << dark_ans.first << " " << dark_ans.second << endl;

  pair<int, int> dhu_ans = dhu(A);
  cout << "dhu_ans: " << dhu_ans.first << " " << dhu_ans.second << endl;

  pair<int, int> brute_ans = brute(A);
  cout << "Brute force: " << brute_ans.first << " " << brute_ans.second << endl;
  */


  return 0;
}
