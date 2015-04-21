/* Leetcode OJ: Write an efficient algorithm that searches for a value in an m x n matrix. 
 * This matrix has the following properties:
 * (1) Integers in each row are sorted from left to right.
 * (2) The first integer of each row is greater than the last integer of the previous row.
 * For example, consider the following matrix:
 *
 *  [1,   3,  5,  7],
 *  [10, 11, 16, 20],
 *  [23, 30, 34, 50]
 * Given target = 3, return true.
 */

// 56ms for large dataset
class Solution {
public:
  bool searchMatrix(vector<vector<int> > &matrix, int target) {
    size_t row = matrix.size();
    if (row == 0)
      return false;

    size_t col = matrix[0].size;
    if (col == 0)
      return false;

    int left = 0;
    int right = row * col - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      int r = mid / col;
      int c = mid % col;
      if (matrix[r][c] == target)
	return true;

      if (matrix[r][c] > target) 
	right = mid - 1;
      else
	left = mid + 1;
    }

    retun false;        
  }
};
