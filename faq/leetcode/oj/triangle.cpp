/* Given a triangle, find the minimum path sum from top to bottom. 
 * In each step you may move to adjacent numbers on the row below.
 * For example, given the following triangle
 *
 *    [2],
 *   [3,4],
 *  [6,5,7],
 * [4,1,8,3]
 *
 * The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
 * Bonus point if you are able to do this using only O(n) extra space, 
 * where n is the total number of rows in the triangle.
 */

// 36ms for large dataset
class Solution {
public:
  int minimumTotal(vector<vector<int> > &triangle) {
    vector<int> dp_prev;
    dp_prev.push_back(triangle[0][0]);
    size_t n = triangle.size();
    for (size_t i = 1; i < n; i++) {
      vector<int> dp_curr;
      dp_curr.push_back(dp_prev[0] + triangle[i][0]);
      for (size_t j = 1; j <= i - 1; j++) {
	int foo = min(dp_prev[j - 1], dp_prev[j]);
	dp_curr.push_back(foo + triangle[i][j]);
      }
      dp_curr.push_back(dp_prev.back() + triangle[i][i]);
      dp_prev = dp_curr;
    }

    int result = dp_prev[0];
    for (size_t i = 0; i < dp_prev.size(); i++)
      if (result > dp_prev[i])
	result = dp_prev[i];
    
    return result;
  }

};

// anson627 solution: In this approach, triangle is used as dp table, so
// space complexity is only O(1).
class Solution {
public:
  int minimumTotal(vector<vector<int> > &triangle) {
    if(triangle.empty()) 
      return 0;
      
    int M = triangle.size();
    for (int i = M-2; i >= 0; --i) {
      int N = triangle[i].size();
      for (int j = 0; j < N; ++j) {
	triangle[i][j] = min(triangle[i+1][j], triangle[i+1][j+1]);
      }
    }
    return triangle[0][0];
  }
};
