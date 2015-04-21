/* Source:
 * http://www.1point3acres.com/bbs/thread-13146-1-1.html
 * This program is buggy when there are duplicate elements in input matrix. 
 */

#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <queue>

using namespace std;

/* Helper function: returns the number of elements
 * that is less than input value in input matrix. */
int GetOrder(const vector<vector<int> >& matrix, int value) {
  int row = matrix.size();
  int col = matrix[0].size();
  
  // Starting from upper right corner of the matrix
  int r = 0;
  int c = col - 1;
  
  int le_num = 0; // Number of elements that are >= value 
  while (r < row && c >= 0) {
    if (matrix[r][c] >= value) {
      le_num +=  row - r;
      c--;
    }
    else 
      r++;
  }
  
  return row * col - le_num;
}

// Main function
int FindKth(const vector<vector<int> >& matrix, int k) {
  int row = matrix.size();
  int col = matrix[0].size();
  
  int min = matrix[0][0];
  int max = matrix[row - 1][col - 1];
  int mid = 0;
  int rank = 0;  
  int prev_rank = -1;
  // Binary search to find a value that is larger than k elements in input matrix
  do {
    mid = min + (max - min) / 2;
    rank = GetOrder(matrix, mid);
    if (rank == prev_rank) 
      break;

    prev_rank = rank;
    if (rank < k)
      min = mid;
    else
      max = mid;
  } while (rank != k);

  cout << "Input k: " << k << "; rank: " << rank << "; mid: " << mid << endl;

  /* Now mid is set to the value that is larger than k elements in the matrix,  
   * so we visit the matrix from its upper right corner to find the first element
   * that is equal to or larger than mid. */
  int r = 0;
  int c = col - 1;
  int answer = 0;
  bool found = false;

  /* Incorrect when rank != k, do NOT know how to fix it.
  // If rank is < k, find the first element that is larger than mid

  if (rank < k) { 
    while (r < row && c >= 0) {
      if (matrix[r][c] > mid) {
	if (!found) {
	  answer = matrix[r][c];
	  found = true;
	}
	else if (answer > matrix[r][c])
	  answer = matrix[r][c];
	c--;
      }
    else
      r++;
    }
  }

  // If rank is larger than k, find the first element that is < mid 
  else if (rank > k) {
    while (r < row && c >= 0) {
      if (matrix[r][c] >= mid) {
	c--;
      }
      else {
	if (!found) {
	  answer = matrix[r][c];
	  found = true;
	}
	else if (answer > matrix[r][c])
	  answer = matrix[r][c];
	r++;
      }
    }
  }
  */

  // If rank is < k, find the first element that is >= mid 
  if (rank == k) {
    while (r < row && c >= 0) {
      if (matrix[r][c] >= mid) {
	if (!found) {
	  answer = matrix[r][c];
	  found = true;
	}
	else if (answer > matrix[r][c])
	  answer = matrix[r][c];
	c--;
      }
    else
      r++;
    }
  }

  return answer;
}

/* dhu idea: use a heap (priority queue) to keep track of minimum,
 * use two accessory bool vectors to keep track of which rows and columns
 * the elements in the heap have taken.
 */

// Element in the heap: includes the value and its position in the matrix
struct Element {
  Element(int v, size_t r, size_t c) : val(v), row(r), col(c) { }

  int val;
  size_t row;
  size_t col;
};

// Comparison class: defined for the minimum heap
class CmpElement {
public:
  bool operator()(const Element& e1, const Element& e2) {
    return e1.val > e2.val;
  }
};

/* Algorithm: By keeping track of which rows and columns have been 
 * taken by elements in the heap, we can maintain the size of heap 
 * to be max(row, col). So suppose N = max(row, col), the time complexity
 * of this algorithm is O(klogN), and space complexity is O(row + col).
 */
int dhu_findKth(const vector<vector<int> >& matrix, size_t k) {
  size_t row = matrix.size();
  size_t col = matrix[0].size();
  vector<bool> rows_taken(row, false);
  vector<bool> cols_taken(col, false);
  priority_queue<Element, vector<Element>, CmpElement> heap;
  heap.push(Element(matrix[0][0], 0, 0));
  rows_taken[0] = true;
  cols_taken[0] = true;
  int answer = matrix[0][0];
  for (size_t i = 0; i <= k; i++) {
    Element tmp = heap.top();
    heap.pop();
    answer = tmp.val;
    rows_taken[tmp.row] = false;
    cols_taken[tmp.col] = false;
    if (tmp.row + 1 < row && rows_taken[tmp.row + 1] == false) {
      heap.push(Element(matrix[tmp.row + 1][tmp.col], tmp.row + 1, tmp.col));
      rows_taken[tmp.row + 1] = true;
      cols_taken[tmp.col] = true;
    }

    if (tmp.col + 1 < col && cols_taken[tmp.col + 1] == false) {
      heap.push(Element(matrix[tmp.row][tmp.col + 1], tmp.row, tmp.col + 1));
      rows_taken[tmp.row] = true;
      cols_taken[tmp.col + 1] = true;
    }
  }

  return answer;
}

// Test harness
int main() {
  int a1[] = { 1, 3, 5, 10 };
  int a2[] = { 4, 7, 8, 9 };

  //int a1[] = { 10, 20, 30, 40 };
  //int a2[] = { 1, 2, 3, 4 };

  vector<vector<int> > matrix(4, vector<int>(4));
  vector<int> sorted;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix[i][j] = a1[i] + a2[j];
      sorted.push_back(a1[i] + a2[j]);
      cout << a1[i] + a2[j] << "\t";
    }
    cout << endl;
  }
  cout << endl;
  
  sort(sorted.begin(), sorted.end());
  for (int i = 0; i < 16; i++) {
    int ret = dhu_findKth(matrix, i);
    if (ret == sorted[i])
      continue;

    cout << i << ": " << ret << "; ans: " << sorted[i] << endl;
  }
  

}
  


