/* Leetcode OJ: Given a m x n grid filled with non-negative numbers, 
 * find a path from top left to bottom right which minimizes the sum 
 * of all numbers along its path.
 * Note: You can only move either down or right at any point in time.
 */

// 64ms for large dataset
class Solution {
public:
  int minPathSum(vector<vector<int> > &grid) {
    if (grid.size() == 0)
      return 0;
    if (grid[0].size() == 0)
      return 0;

    size_t row = grid.size();
    size_t col = grid[0].size();
    int dp[row][col];
    dp[0][0] = grid[0][0];
    for (size_t c = 1; c < col; c++) 
      dp[0][c] = dp[0][c - 1] + grid[0][c];
    for (size_t r = 1; r < row; r++) 
      dp[r][0] = dp[r-1][0] + grid[r][0];

    for (size_t r = 1; r < row; r++) {
      for (size_t c = 1; c < col; c++) {
	if (dp[r][c - 1] < dp[r - 1][c])
	  dp[r][c] = grid[r][c] + dp[r][c - 1];
	else
	  dp[r][c] = grid[r][c] + dp[r - 1][c];
      }
    }
    
    return dp[row-1][col-1];
  }

};
