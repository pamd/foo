/* Leetcode OJ: Given a m x n matrix, if an element is 0, 
 * set its entire row and column to 0. Do it in place.
 *
 * Follow up: Did you use extra space?
 * A straight forward solution using O(m*n) space is probably a bad idea.
 * A simple improvement uses O(m + n) space, but still not the best solution.
 * Could you devise a constant space solution?
 */

// 412ms for large dataset
class Solution {
public:
  void setZeroes(vector<vector<int> > &matrix) {
    bool row0_zero = false;
    bool col0_zero = false;
    for (size_t r = 0; r < matrix.size(); r++) {
      for (size_t c = 0; c < matrix[0].size(); c++) {
	if (matrix[r][c] == 0) {
	  if (r == 0)
	    row0_zero = true;
	  else
	    matrix[r][0] = 0;

	  if (c == 0)
	    col0_zero = true;
	  else 
	    matrix[0][c] = 0;
	}
      }
    }

    for (size_t r = 1; r < matrix.size(); r++) {
      for (size_t c = 1; c < matrix[0].size(); c++) {
        if (matrix[r][0] == 0 || matrix[0][c] == 0)
	  matrix[r][c] = 0;
      }
    }

    if (row0_zero) {
      for (size_t c = 0; c < matrix[0].size(); c++) 
	matrix[0][c] = 0;
    }

    if (col0_zero) {
      for (size_t r = 0; r < matrix.size(); r++) 
	matrix[r][0] = 0;
    }
  }

};

