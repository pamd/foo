/* Given n, how many structurally unique BST's (binary search trees) that store values 1...n?
 * For example, given n = 3, there are a total of 5 unique BST's.
 */

class Solution {
public:
  // Brute force, 68ms for large dataset
  int numTrees_brute_foce(int n) {
    if (n <= 1)
      return 1;

    int result = 0;
    for (int i = 0; i < n; i++) 
      result += numTrees(i) * numTrees(n - 1 - i);

    return result;
  }

  // DP approach: 4ms for large dataset
  int numTrees(int n) {
    vector<int> dp(n + 1, 1);
    for (int i = 2; i <= n; i++) {
      int sum = 0;
      for (int j = 0; j < i; j++) {
        sum += dp[j] * dp[i - j - 1];
      }
      dp[i] = sum;
    }
    return dp[n];
  }

};
