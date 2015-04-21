/* Leetcode OJ: Given an index k, return the kth row of the Pascal's triangle.
 * For example, given k = 3, return [1,3,3,1].
 * Note: Could you optimize your algorithm to use only O(k) extra space?
 */

// 16 ms for large dataset
class Solution {
public:
  vector<int> getRow(int rowIndex) {
    if (rowIndex < 0)
      return vector<int>();

    vector<int> prev(1, 1);
    for (int row = 1; row <= rowIndex; row++) {
      vector<int> curr(row + 1, 1);
      for (size_t i = 1; i <= row - 1; i++) 
	curr[i] = prev[i - 1] + prev[i];
      prev = curr;
    }

    return prev;
  }
};
