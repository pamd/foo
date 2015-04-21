/* Leetcode OJ: You are given an n x n 2D matrix representing an image,
 * rotate the image by 90 degrees (clockwise).
 * Follow up: Could you do this in-place?
 */

// 28ms for large dataset
class Solution {
public:
  void rotate(vector<vector<int> > &matrix) {
    size_t row = matrix.size();
    if (row == 0)
      return;

    size_t col = matrix[0].size();
    if (col == 0)
      return;
        
    for (size_t i = 0; i < row; i++) {
      for (size_t j = 0; j < i; j++) {
	swap(matrix[i][j], matrix[j][i]);
      }
    }

    for (size_t i = 0; i < row; i++) {
      for (size_t j = 0; j < col / 2; j++) 
	swap(matrix[i][j], matrix[i][col - 1 - j]);
    }
  }

};

// Dropbox solution: rotate by layers (also refer to CareerCup book)

/*
**  Explanation of First solution:
**
**  1   2   3   4
**  5   6   7   8
**  9   10  11  12
**  13  14  15  16
**
**  The layers mean the square cycles from outer to inner.
**  1,2,3,4,8,12,16,15,14,13,9,5 is one layer, 6,7,11,10 is another layer
**  To rotate the matrix, is just to rotate the layers
**  
**  The rule for rotating is easy to fiqure out:
**  regard: 
**      2 -> 8 -> 15 -> 9 -> 2
**  it is:
**      a[i][j] -> a[m-j][i] -> a[m-i][m-j] -> a[j][m-i] -> a[i][j]
**  where m is max index of row/col, which begin at 0
*/ 
void RotateMatrix(vector<vector<int> > &matrix) {
  size_t m = matrix.size() - 1;

  if (m <= 0) 
    return;

  for (int i = 0; i <= m / 2; ++i) {  // go over each layer
    for (int j = i; j < m - i; ++j) { // rotate the layer
      int tmp = matrix[i][j];
      matrix[i][j] = matrix[m-j][i];
      matrix[m-j][i] = matrix[m-i][m-j];
      matrix[m-i][m-j] = matrix[j][m-i];
      matrix[j][m-i] = tmp;
    }
  }
}

// dhu version that rotates by layers: with better variable names
void rotate2(vector<vector<int> > &matrix) {
  size_t dim = matrix.size();

  if (dim <= 1) 
    return;

  for (int i = 0; i < dim / 2; ++i) {  // go over each layer
    for (int j = i; j < dim - 1 - i; ++j) { // rotate the layer
      int tmp = matrix[i][j];
      matrix[i][j] = matrix[dim-1-j][i];
      matrix[dim-1-j][i] = matrix[dim-1-i][dim-1-j];
      matrix[dim-1-i][dim-1-j] = matrix[j][dim-1-i];
      matrix[j][dim-1-i] = tmp;
    }
  }
}
