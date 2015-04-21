/* Leetcode OJ: Follow up for N-Queens problem.
 * Now, instead outputting board configurations, 
 * return the total number of distinct solutions. */

#include <vector>
#include <iostream>
#include <string>

using namespace std;

// 1800ms for large dataset
class Solution {
public:
  int totalNQueens(int n) {
    int counter = 0;
    vector<size_t> tmp(n);
    size_t level = 0;
    helper(n, level, tmp, counter);

    return counter;
  }

  // Check whether a new Queen can be put at a certain position of the board
  // Have to use the compact version to pass OJ on large dataset. Weird.
  bool check(const vector<size_t>& conf, size_t row, size_t col) {
    for (size_t r = 0; r < row; r++) {
      if (conf[r] == col || abs((int) col - (int) conf[r]) == row - r)
	return false;
      /*
      size_t r_offset = row - r;
      size_t c_offset;
      if (col > conf[r])
	c_offset = col - conf[r];
      else
	c_offset = conf[r] - col;
      if (r_offset == c_offset)
	return false;
      */ 
   }

    return true;
  }

  // Recursive helper function 
  void helper(size_t n, size_t level, vector<size_t>& tmp, int& counter) {
    if (level == n) {
      counter++;
      return;
    }

    for (int i = 0; i < n; i++) {
      if (check(tmp, level, i)) {
	tmp[level] = i;
	helper(n, level + 1, tmp, counter);
      }
    }
  }

};

