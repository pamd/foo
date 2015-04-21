/* Leetcode OJ: Given numRows, generate the first numRows of Pascal's triangle.
 * For example, given numRows = 5, return:
 *
 *     [1],
 *    [1,1],
 *   [1,2,1],
 *  [1,3,3,1],
 * [1,4,6,4,1]
 *
 */

// 12 ms for large dataset
class Solution {
public:
  vector<vector<int> > generate(int numRows) {
    vector<vector<int> > result;
    if (numRows <= 0)
      return result;
  
    result.push_back(vector<int>(1, 1));
    for (int row = 2; row <= numRows; row++) {
      vector<int> tmp(row, 1);
      for (size_t i = 1; i < row - 1; i++)
	tmp[i] = result.back()[i - 1] + result.back()[i];
      result.push_back(tmp);
    }

    return result;
  }
};
