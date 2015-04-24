/* dhu C++ code that solve 2D water trap problem. 
 * Algorithm is based on:
 * http://blog.sina.com.cn/s/blog_b9285de20101j9a7.html
 * (Google Drive "MITBBS Pearls" Q430.)
 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Cell {
  Cell(int r, int c, int h) : row(r), col(c), height(h) { }
 
  int row;
  int col;
  int height;

  // Used by priority_queue (always put minimum element on the top)
  bool operator<(const Cell& rhs) const {
    return height > rhs.height;
  }

};

/* Check the cell at (r, c). 
 * If its height is lower than the top element in priority queue, 
 * then the water trapped in it will be matrix[r][c] - pq.top().height, 
 * then push (r, c, pq.top().height) into pq;
 * If its height is equal to or larger than the top element in priority 
 * queue, no water could be trapped in this cell, so we simply push
 * (r, c, matrix[r][c]) into the priority queue. 
 *
 * The top element in pq can be popped out either before or after 
 * the above calculation. 
 */
void check_cell(const vector<vector<int> >& matrix, int r, int c, int lowest,
		priority_queue<Cell>& pq, int& water,
		vector<vector<bool> >& visited) {
  if (r <= 0 || r >= (int) matrix.size() - 1 
      || c <= 0 || c >= (int) matrix[0].size() - 1)
    return;
  
  if (visited[r][c])
    return;

  if (matrix[r][c] < lowest) {
    water += lowest - matrix[r][c];
    pq.push(Cell(r, c, lowest));
  }
  else { // matrix[r][c] >= lowest
    pq.push(Cell(r, c, matrix[r][c]));
  }

  visited[r][c] = true;
}

// Calculate the total amount of water trapped in input matrix.
int get_water_trap(const vector<vector<int> >& matrix) {
  priority_queue<Cell> pq;
  int row = matrix.size();
  int col = matrix[0].size();

  // Keep track of cells that either can never 
  // hold water or we have already visited.
  vector<vector<bool> > visited(row, vector<bool>(col, false));

  // Put cells on top and bottom borders into the priority queue
  for (int c = 0; c < col; c++) {
    pq.push(Cell(0, c, matrix[0][c]));
    visited[0][c] = true; // optional, because check_cell() will catch it.

    pq.push(Cell(row - 1, c, matrix[row - 1][c]));
    visited[row-1][c] = true; // optional, because check_cell() will catch it.
  }

  // Put cells on left and right borders into the priority queue
  for (int r = 1; r < row - 1; r++) {
    pq.push(Cell(r, 0, matrix[r][0]));
    visited[r][0] = true; // optional, because check_cell() will catch it.

    pq.push(Cell(r, col - 1, matrix[r][col - 1]));
    visited[r][col-1] = true; // optional, because check_cell() will catch it.
  }

  int water = 0;
  while (!pq.empty()) {
    Cell curr = pq.top(); 
    pq.pop();
    int r = curr.row;
    int c = curr.col;
    int lowest = curr.height;
    check_cell(matrix, r-1, c,   lowest, pq, water, visited);
    check_cell(matrix, r+1, c,   lowest, pq, water, visited);
    check_cell(matrix, r,   c-1, lowest, pq, water, visited);
    check_cell(matrix, r,   c+1, lowest, pq, water, visited);
  }

  return water;
}

// Test harness
int main() {
  vector<vector<int> > matrix;
  int r1[] = {5, 5, 5, 5};
  int r2[] = {5, 3, 2, 5};
  int r3[] = {5, 4, 4, 5};
  int r4[] = {5, 1, 5, 5};

  matrix.push_back(vector<int>(r1, r1 + 4));
  matrix.push_back(vector<int>(r2, r2 + 4));
  matrix.push_back(vector<int>(r3, r3 + 4));
  matrix.push_back(vector<int>(r4, r4 + 4));

  cout << "water: " << get_water_trap(matrix) << endl;

  return 0;
} 
