/* A robot is located at the top-left corner of a m x n grid.
 * The robot can only move either down or right at any point in time. 
 * The robot is trying to reach the bottom-right corner of the grid.
 * How many possible unique paths are there?
 * Note: m and n will be at most 100.
 */

class Solution {
public:
  int uniquePaths(int m, int n) {
    //return helper_brute_force(1, 1, m, n);

    // DP method
    int dp[m][n];
    dp[0][0] = 1; // dp[0][0]should be 1, NOT 0.
    for (int i = 1; i < m; i++) 
      dp[i][0] = 1;
    for (int j = 1; j < n; j++)
      dp[0][j] = 1;

    for (int i = 1; i < m; i++) {
      for (int j = 1; j < n; j++)
	dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
    }

    return dp[m-1][n-1];
  }

  // Brute-force method: time limit exceeded for large dataset
  int helper_brute_force(int curr_m, int curr_n, int m, int n) {
    if (curr_x == m && curr_n == n)
      return 1;

    int result = 0;
    if (curr_m < m)
      result += helper(curr_m + 1, curr_n, m, n);
    if (curr_n < n) 
      result += helper(curr_m, curr_n + 1, m , n);
    return result;
  }
};

// Dropbox solution and anson627 solution are identical to my DP version
