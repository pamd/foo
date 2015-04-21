/* Leetcode OJ: Given an integer n, generate a square matrix 
 * filled with elements from 1 to n2 in spiral order.
 * For example, given n = 3, you should return the following matrix:
 *
 *  1, 2, 3 
 *  8, 9, 4 
 *  7, 6, 5 
 *
 */

// 16 ms for large dataset
class Solution {
public:
  vector<vector<int> > generateMatrix(int n) {
    if (n <= 0)
      return vector<vector<int> >();

    vector<vector<int> > mat(n, vector<int>(n));
    int x = 1;
    for (int i = 0; i < (n + 1) / 2; i++) {
      for (int j = i; j < n - i; j++)
	mat[i][j] = x++;
      for (int j = i + 1; j < n - i; j++)
	mat[j][n - 1 - i] = x++;
      for (int j = n - 2 - i; j >= i; j--)
	mat[n - 1 - i][j] = x++;
      for (int j = n - 2 - i; j > i; j--)
	mat[j][i] = x++;
    }
      
    return mat;
  }

};

// Dropbox solution: almost identical to dhu solution
vector<vector<int> > SpiralMatrix(int m) {
  // Initialize a n*n vector<vector<int> >
  vector<vector<int> > r(m, vector<int>(m, 0));
  int k = 0;
  int n = m - 1; // max index in vector, which starts at 0
  // Generate spiral matrix layer by layer
  for(int layer = 0; layer <= n / 2; ++layer) {
    // top
    for (int j = layer; j <= n - layer; ++j)
      r[layer][j] = ++k;

    // right
    for (int i = layer + 1; i <= n - layer; ++i)
      r[i][n-layer] = ++k;
    
    // bottom
    for (int j = n - layer - 1; j >= layer; --j)
      r[n-layer][j] = ++k;

    // left
    for (int i = n - layer - 1; i >= layer + 1; --i)
      r[i][layer] = ++k;
  }

  return r;
}

// Once again, anson627 uses recursion
class Solution {
public:
  void generateMatrixHelper(vector<vector<int> > &res, int x, int n, int k) {
    if (n <= 0) 
      return;

    if (n == 1) {
      res[k+n-1][k+n-1] = x++;
      return;
    }

    int i = 0, j = 0;
    for (; j < n-1; j++) 
      res[k+i][k+j] = x++;

    for (; i < n-1; i++) res[k+i][k+j] = x++;

    for (; j > 0; j--) 
      res[k+i][k+j] = x++;

    for (; i > 0; i--) 
      res[k+i][k+j] = x++;
    
    generateMatrixHelper(res, x, n-2, k+1);
  }

  vector<vector<int> > generateMatrix(int n) {
    vector<vector<int> > res;
    for (int i = 0; i < n; i++) {
      res.push_back(vector<int>(n, 0));
    }

    generateMatrixHelper(res, 1, n, 0);
    return res;
  }
};
