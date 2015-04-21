/* Follow up for "Unique Paths":
 * Now consider if some obstacles are added to the grids. How many unique paths would there be?
 * An obstacle and empty space is marked as 1 and 0 respectively in the grid.
 * For example, there is one obstacle in the middle of a 3x3 grid as illustrated below.
 *
 * [0,0,0],
 * [0,1,0],
 * [0,0,0]
 *
 * The total number of unique paths is 2.
 * Note: m and n will be at most 100.
 */

// 20ms for large dataset, same idea as the original problem
class Solution {
public:
  int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
    int row = obstacleGrid.size();
    int col = obstacleGrid[0].size();
    if (!row || !col || obstacleGrid[0][0] == 1)
      return 0;

    int dp[row][col];
    dp[0][0] = 1;
    for (int i = 1; i < row; i++) {
      if (obstacleGrid[i][0] == 1)
	dp[i][0] = 0;
      else
	dp[i][0] = dp[i-1][0];
    }

    for (int j = 1; j < col; j++) {
      if (obstacleGrid[0][j] == 1)
	dp[0][j] = 0;
      else
	dp[0][j] = dp[0][j-1];
    }

    for (int i = 1; i < row; i++) {
      for (int j = 1; j < col; j++) {
	if (obstacleGrid[i][j] == 1)
	  dp[i][j] = 0;
	else
	  dp[i][j] = dp[i-1][j] + dp[i][j-1];
      }
    }
    return dp[row-1][col-1];
  }

};

// Dropbox and anson627 use the same idea.
