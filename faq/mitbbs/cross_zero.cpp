/* Given a mtrix whose elements are either 0 or 1. Press element Mat[x][y]
 * will toggle elements on row x and column y. How to get a sequence of presses
 * which will eventually convert all elements in the matrix to 0? 
 * 
 * Solution copied from chenpp on:
 * http://www.mitbbs.com/article_t/JobHunting/32115115.html
 * 
 * According to longway2008, this solution has some bugs, because not all
 * matrixes can be converted to all-zero matrix, but it is still very amazing.
 * Time is O(M * N), space is O(M + N).
 */

#include <iostream>
#include <vector>

using namespace std;

const int N = 2;

// Solution from chenpp
void solve(int A[][N], int M) {
  int flag = (M+N) & 1;
  int xor_row[M], xor_col[N];
  // int S[M][N];

  // Initialize all elements in xor_row to 0
  for (int i = 0; i < M; i++) 
    xor_row[i] = 0;

  // Initialize all elements in xor_col to 0
  for (int i = 0; i < N; i++)
    xor_col[i] = 0;

  for (int x = 0; x < M; x++) {
    for (int y = 0; y < N; y++) {
      xor_row[x] ^= A[x][y]; 
      xor_col[y] ^= A[x][y];
    }
  }

  for (int x = 0; x < M; x++) {
    for (int y = 0; y < N; y++) {
      // S[x][y] = xor_row[x] ^ xor_col[y] ^ A[x][y] ^ flag;
      int foo = xor_row[x] ^ xor_col[y] ^ A[x][y] ^ flag;
      cout << foo << " ";
      // if(S[x][y])
      // print_pair(x,y);
    }
    cout << endl;
  }
}

/****************************************************
 * Brute force recursive solution from newbielisk
 ****************************************************/
// Helper function which determines whether elements 
// in input matrix are all zero.
bool isAllZero(int mat[][N], int M) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++)
      if (mat[i][j] == 1)
	return false;
  }

  return true;
}

// Helper function that toggles all elements on row and col
void press(int mat[][N], int M, int row, int col) {
  for (int i = 0; i < M; i++) 
    mat[i][col] = 1 ^ mat[i][col];

  for (int i = 0; i < N; i++) 
    mat[row][i] = 1 ^ mat[row][i];

  mat[row][col] = 1 ^ mat[row][col];
}

// Brute force function. seq will be passed in as a reference.
// At the end of the program, if a solution is found, seq will
// have the sequences of presses.
bool brute_force(int A[][N], int M, int row, int col, vector<pair<int, int> >& seq) 
{
  if (isAllZero(A, M))
    return true;

  if (row >= M || col >= N)
    return false;

  int next_row = row;
  int next_col = col + 1;
  // Set row and col of next element. Here the elements are
  // traversed by rows. We can also traverse by columns.
  if (next_col == N) {
    next_row = row + 1;
    next_col = 0;
  }

  if (brute_force(A, M, next_row, next_col, seq))
    // If we print solution here, it will be printed multiple times,
    // because this return value will be passed to parent recursion
    // various times!
    return true;

  // Press current element, then test whether we can find a solution.
  press(A, M, row, col);
  seq.push_back(make_pair<int, int>(row, col));
  if (brute_force(A, M, next_row, next_col, seq))
    // Once again, do not try to print out solution here!
    return true;

  // If no solution is found, press this element again to recover the
  // original matrix. If we do not call press() here, the solution will
  // be found eventually too, since all elements after current one will 
  // be recursively checked, but seq will include redundant presses.
  press(A, M, row, col);
  seq.pop_back();

  return false;
}

// Test harness
int main() {
    
  /*
    int A[4][4] = {
    { 1, 0, 0, 1 },
    { 1, 0, 0, 1 },
    { 1, 1, 1, 1 },
    { 0, 0, 1, 0 }
  };
  */

  /* For the matrix above, solution should be:

     0 1 0 0 
     0 1 0 0 
     0 0 1 0 
     0 0 0 0 
    
    Any element that is 1 means that this element in original matrix should 
    be pressed. 
  */

  //  solve(A, 4, 4);  

  int A[2][2] = { {1, 1}, {1, 0} };

  vector<pair<int, int> > seq;
  int ret = brute_force(A, 2, 0, 0, seq);
  // Solution can be printed out here
  if (ret) {
    for (size_t i = 0; i < seq.size(); i++) 
      cout << seq[i].first << ", " << seq[i].second << endl;
  }
  else 
    cout << "Solution not found" << endl;

}
