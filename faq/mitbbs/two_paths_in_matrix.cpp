/* Given a m*n matrix whose elements are positive int, negative int or 0.
 * Suppose the upper left corner of the matrix is Mat[0][0], and the
 * lower right corner is Mat[m-1][n-1]. A path is defined as starting from
 * [0][0] and ending at [m-1][n-1], and we are only allowed to move down 
 * or move right. Find two paths in the matrix whose sums of elements in 
 * the two paths are maximum. If an element is available in both paths,
 * the value should be counted only once.
 *
 * The DP idea is copied from:
 * http://blog.sina.com.cn/s/blog_b9285de20101ijil.html
 *
 */

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int get_two_path(const vector<vector<int> >& mat) {
  int row = mat.size();
  int col = mat[0].size();

  // DP idea: define DP[x][y][x'][y'] as the maximum value 
  // we can get from path #1 (that starts from [0][0] and 
  // ends at [x][y]) and path #2 that starts from [0][0] 
  // and ends at [x'][y']).
  int DP[row][col][row][col];
  // Initialize 4-dimension DP table
  for (int r1 = 0; r1 < row; r1++) {
    for (int c1 = 0; c1 < col; c1++) {
      for (int r2 = 0; r2 < row; r2++) {
	for (int c2 = 0; c2 < col; c2++) {
	  DP[r1][c1][r2][c2] = INT_MIN;
	}
      }
    }
  }

  DP[0][0][0][0] = mat[0][0]; // Initialize the starting point
  // Update by DP
  for (int r1 = 0; r1 < row; r1++) {
    for (int c1 = 0; c1 < col; c1++) {
      for (int r2 = 0; r2 < row; r2++) {
	for (int c2 = 0; c2 < col; c2++) {
	  if (!r1 && !c1 && !r2 && !c2) // Skip the starting point
	    continue;
	  if (r1 + c1 != r2 + c2)
	    continue;

	  // IMPORTANT: must extend the two paths concurrently,
	  // otherwise each element may be included more than once!
	  if (r1 > 0 && r2 > 0) 
	    DP[r1][c1][r2][c2] = max(DP[r1][c1][r2][c2], DP[r1-1][c1][r2-1][c2]);
	  if (r1 > 0 && c2 > 0) 
	    DP[r1][c1][r2][c2] = max(DP[r1][c1][r2][c2], DP[r1-1][c1][r2][c2-1]);
	  if (c1 > 0 && r2 > 0) 
	    DP[r1][c1][r2][c2] = max(DP[r1][c1][r2][c2], DP[r1][c1-1][r2-1][c2]);
	  if (c1 > 0 && c2 > 0) 
	    DP[r1][c1][r2][c2] = max(DP[r1][c1][r2][c2], DP[r1][c1-1][r2][c2-1]);
	  
	  if (r1 == r2 && c1 == c2)  // Same cell
	    DP[r1][c1][r2][c2] += mat[r1][c1];
	  else // Different cell
	    DP[r1][c1][r2][c2] += (mat[r1][c1] + mat[r2][c2]);
	}
      }
    }
  }

  return DP[row-1][col-1][row-1][col-1];
}

// Test harness
int main() {
  int row1[] = { 1,  1,  1,  1 };
  int row2[] = { 0,  6, -2, -1 };
  int row3[] = { 0, -1, -5,  4 };
  int row4[] = { 1,  0,  0,  2 };

  // This matrix is a counter example that shows that greedy approach 
  // can not give us optimal solution: 
  // The single optimal path is: { 1, 1, 6, -2, -1, 4, 2 }, whose sum 
  // is 11; then we set all those elements to 0, and find the 
  // second optimal path: { (1), (1), 1, 1, (-1), (4), (2) }, the 
  // overlapping elements are labeled by "()". So the sum of second path 
  // is 2, and the total sum is 11 + 2 = 13.
  // But if we select { 1, 1, 6, -1, 0, 0, 2 } in path #1, and 
  // { (1), (1), 1, 1, -1, 4, (2) } as path #2, the total sum is
  // 9 + 5 = 14, which is batter than the greedy appraoch.   

  vector<vector<int> > mat;
  mat.push_back(vector<int>(row1, row1 + sizeof(row1) / sizeof(int)));
  mat.push_back(vector<int>(row2, row2 + sizeof(row2) / sizeof(int)));
  mat.push_back(vector<int>(row3, row3 + sizeof(row3) / sizeof(int)));
  mat.push_back(vector<int>(row4, row4 + sizeof(row4) / sizeof(int)));

  int sum = get_two_path(mat);
  cout << "sum: " << sum << endl;

  return 0;
}


		
