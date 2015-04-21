/* Leetcode OJ: Given an integer n, return all distinct solutions to the n-queens puzzle. */

#include <vector>
#include <iostream>
#include <string>

using namespace std;

// 28ms for large dataset
class Solution {
public:
  vector<vector<string> > solveNQueens(int n) {
    vector<vector<string> > result;
    size_t level = 0;
    vector<size_t> tmp(n);
    helper(n, level, tmp, result);
        
    return result;
  }

  // Generate a vector of string from vector of int
  vector<string> mkStr(const vector<size_t>& vi) {
    string s(vi.size(), '.');
    vector<string> vs(vi.size(), s);
    for (size_t i = 0; i < vi.size(); i++) {
      size_t p = vi[i];
      vs[i][p] = 'Q';
    }
    return vs;
  }

  // Check whether a new Queen can be put at a certain position of the board
  bool check(const vector<size_t>& conf, size_t row, size_t col) {
    for (size_t r = 0; r < row; r++) {
      if (conf[r] == col)
	return false;
      size_t r_offset = row - r;
      size_t c_offset;
      if (col > conf[r])
	c_offset = col - conf[r];
      else
	c_offset = conf[r] - col;
      if (r_offset == c_offset)
	return false;
    }

    return true;
  }

  // Recursive helper function 
  void helper(size_t n, size_t level, vector<size_t>& tmp, vector<vector<string> >& result) {
    if (level == n) {
      result.push_back(mkStr(tmp));
      return;
    }

    for (int i = 0; i < n; i++) {
      if (check(tmp, level, i)) {
	tmp[level] = i;
	helper(n, level + 1, tmp, result);
      }
    }
  }

};
