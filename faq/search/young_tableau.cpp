/* This program implements functions related to Young tableau.
 * Code is based on:
 * http://lyle.smu.edu/~saad/courses/cse3358/ps5/problemset5sol.pdf
 */

#include <climits>
#include <iostream>
#include <vector>

using namespace std;

// Helper function
void swap(int& v1, int& v2) {
  int tmp = v1;
  v1 = v2;
  v2 = tmp;
}

// Class definition
class YoungTab {
public:
  YoungTab(int row_in, int col_in);
  int popMin();
  void youngify_up2bottom(size_t row_idx, size_t col_idx);
  void youngify_bottom2up(size_t row_idx, size_t col_idx);
  void insert(int);

  //  void insert2(int);
  void decrease_key(int);

  void print() const;

private:
  size_t row, col;
  vector<vector<int> > data;
};

// Ctor initializes all elements to INT_MAX 
YoungTab::YoungTab(int row_in, int col_in) {
  row = row_in;
  col = col_in;
  for (size_t i = 0; i < row; i++) {
    vector<int> tmp(col_in, INT_MAX);
    data.push_back(tmp);
  }
}

/* Extract the element on upper left corner, then youngify the whole table
 * from up to bottom. 
 */
int YoungTab::popMin()
{
  int ret = data[0][0];
  data[0][0] = INT_MAX;
  youngify_up2bottom(0, 0);
  return ret;
}

// Youngify the table from up to bottom
void YoungTab::youngify_up2bottom(size_t r, size_t c) {
  size_t r2 = r;
  size_t c2 = c;
  if (r + 1 < row && data[r][c] > data[r+1][c]) 
    r2 = r + 1;
  if (c + 1 < col && data[r2][c2] > data[r][c+1]) {
    r2 = r;
    c2 = c + 1;
  }

  if (r2 == r && c2 == c)
    return;

  swap(data[r][c], data[r2][c2]);
  youngify_up2bottom(r2, c2);

}

/* Insert a new element into the lower right corner of the table,
 * then youngify the table from bottom to up. */
void YoungTab::insert(int val) {
  data[row-1][col-1] = val;
  youngify_bottom2up(row - 1, col - 1);
}

// Youngify the table from up to bottom. 
void YoungTab::youngify_bottom2up(size_t r, size_t c) {
  size_t r2 = r;
  size_t c2 = c;
  if (r > 0 && data[r][c] < data[r-1][c])
    r2 = r - 1;
  if (c > 0 && data[r2][c2] < data[r][c-1]) {
    r2 = r;
    c2 = c - 1;
  }

  if (r2 == r && c2 == c)
    return;

  swap(data[r][c], data[r2][c2]);
  youngify_bottom2up(r2, c2);
}

/* Another way to insert a new element is by calling decrease_key(), 
 * which is equivalent to insert() but is an iterative function. */
void YoungTab::decrease_key(int val) {
  // Make sure the current tableau is not full yet.
  if (data[row-1][col-1] <= val) {
    cout << "error" << endl;
    return;
  }

  // Iteratively youngify the table from bottom to up
  int r = row - 1;
  int c = col - 1;
  data[row-1][col-1] = val;
  int threshold = INT_MAX;
  int r2 = r;
  int c2 = c;
  while (r >= 0 && c >= 0 && data[r][c] < threshold) {
    swap(data[r][c], data[r2][c2]);
    r = r2;
    c = c2;
    if (r > 0 && data[r][c] < data[r-1][c]) {
      r2 = r - 1;
    }
    if (c > 0 && data[r2][c2] < data[r][c-1]) {
      r2 = r;
      c2 = c - 1;
    }
    threshold = data[r2][c2];
  }
}
 
// Print out elements in Young Tableau
void YoungTab::print() const {
  for (size_t i = 0; i < row; i++) {
    for (size_t j = 0; j < col; j++) {
      if (data[i][j] < INT_MAX)
	cout << data[i][j] << '\t';
      else
	cout << "INF\t";
    }
    cout << endl;
  }
}

// Test harness
int main() {
  // index:       0  1  2  3   4  5   6   7  8   9  10  11
  int arr[12] = { 5, 8, 2, -1, 4, 9, -23, 8, 12, 7, -2, 3 };  
  int len = sizeof(arr) / sizeof(int);
  YoungTab yt(3, 4);

  for (int i = 0; i < len; i++) {
    // We can insert new element by calling either insert() or decrese_key()
    // yt.insert(arr[i]);
    yt.decrease_key(arr[i]);
  }

  yt.print();
  cout << endl;
  for (int i = 0; i < len; i++)
    cout << yt.popMin() << " ";
  cout << endl;

}
