/* Leetcode OJ: Given a matrix of m x n elements (m rows, n columns), 
 * return all elements of the matrix in spiral order.
 * For example, given the following matrix:
 * 
 *  1, 2, 3
 *  4, 5, 6 
 *  7, 8, 9 
 * 
 * You should return [1,2,3,6,9,8,7,4,5].
 */

#include <iostream>
#include <vector>

using namespace std;

// This problem is tricky because the input matrix may not be a square matrix.
// 8ms for large dataset.
class Solution {
public:
  vector<int> spiralOrder(vector<vector<int> > &matrix) {
    vector<int> result;
    int row = matrix.size();
    if (row == 0)
      return result;

    int col = matrix[0].size();
    if (col == 0)
      return result;

    int r2 = row;
    int c2 = col;
    for (int i = 0; i < (col + 1) / 2; i++) {
      // Top edge (from left to right): including upper-left and upper-right coners
      for (int j = i; j < col - i; j++)
	result.push_back(matrix[i][j]);
      if (--r2 == 0)
	break;

      // right edge (from top to bottom): including lower-right corner
      for (int j = i + 1; j < row - i; j++)
	result.push_back(matrix[j][col - 1 - i]);
      if (--c2 == 0)
	break;

      // Bottom edge (from right to left): including lower-left corner
      for (int j = col - 2 - i; j >= i; j--) 
	result.push_back(matrix[row - 1 - i][j]);
      if (--r2 == 0)
	break;

      // Left edge (from bottom to top): without any corner
      for (int j = row - 2 - i; j > i; j--)
	result.push_back(matrix[j][i]);
      if (--c2 == 0)
	break;
    }
    
    return result;
  }
};

// Dropbox solution
vector<int> SpiralOrder(vector<vector<int> > &matrix) {
  if (matrix.size() <= 0)
    return vector<int>();

  int row = matrix.size();
  int col = matrix[0].size(); 
  vector<int> r;
  r.reserve(row*col);

  int top = 0;
  int bottom = row - 1;
  int left = 0;
  int right = col - 1;
	
  while (top < bottom && left < right) {
    for (int j = left; j <= right; ++j)
      r.push_back(matrix[top][j]);
    ++top;
		
    for (int i = top; i <= bottom; ++i)
      r.push_back(matrix[i][right]);
    --right;
		
    for (int j = right; j >= left; --j)
      r.push_back(matrix[bottom][j]);
    --bottom;
		
    for (int i = bottom; i >= top; --i)
      r.push_back(matrix[i][left]);
    ++left;
  }

  // for odd fat matrix	
  if (left < right && top == bottom) { 
    for (int j = left; j <= right; ++j)
      r.push_back(matrix[top][j]);
  }

  // for odd lean matrix
  if (top < bottom && left == right) { 
    for (int i = top; i <= bottom; ++i)
      r.push_back(matrix[i][right]);
  }  

  // for odd sqaure matrix
  if (top == bottom && left == right) 
    r.push_back(matrix[top][left]);
	
  return r;
}

// anson627 solution: uses a recursive helper function,
// not as intuitive as dropbox solution
class Solution {
public:
  // Recursive helper function
  void spiralOrderHelper(vector<vector<int> > &matrix, int M, int N, int k, vector<int> &res) {
    if (M <= 0 || N <= 0) 
      return;

    if (M == 1) {
      for (int j = 0; j < N; j++) 
	res.push_back(matrix[k][k+j]);
      return;
    }

    if (N == 1) {
      for (int i = 0; i < M; i++) 
	res.push_back(matrix[k+i][k]);
      return;
    }

    int i = 0, j = 0;
    for (; j < N-1; j++) 
      res.push_back(matrix[k+i][k+j]);

    for (; i < M-1; i++) 
      res.push_back(matrix[k+i][k+j]);

    for (; j > 0; j--) 
      res.push_back(matrix[k+i][k+j]);

    for (; i > 0; i--) 
      res.push_back(matrix[k+i][k+j]);

    spiralOrderHelper(matrix, M-2, N-2, k+1, res);
  }

  // Wrapper function
  vector<int> spiralOrder(vector<vector<int> > &matrix) {
    vector<int> res;
    int M = matrix.size();
    if (M == 0) 
      return res;

    int N = matrix[0].size();
    if (N == 0) 
      return res;
   
    spiralOrderHelper(matrix, M, N, 0, res);
    return res;
  }
};
