// Print matrix element clockwise

#include <iostream>

using namespace std;

int main()
{
  int row = 10;
  int col = 10;
  int mat[row][col];
  int counter = 0;
  for (int i = 0; i < row; i++) 
    for (int j = 0; j < col; j++)
      mat[i][j] = ++counter;

  cout << "Original matrix: " << endl;
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) 
      printf("%4d ", mat[i][j]);
    cout << endl;
  }
  cout << endl;

  cout << "Clockwise printout: " << endl;
  int offset = 0;
  for (int i = 0; i < row - offset; offset++, i++) {
    for (int j = i; j < col - offset; j++) {
      cout << mat[i][j] << endl;
    }
    for (int j = offset + 1; j < row - offset; j++) {
      cout << mat[j][col-1-offset] << endl;
    }
    for (int j = col-2-offset; j >= offset; j--) {  // note that it is col-2, not col-1
      cout << mat[row-1-offset][j] << endl;
    }
    for (int j = row-2-offset; j >= offset + 1; j--) { // note that it is row-2, not row-1
      cout << mat[j][offset] << endl;
    }
    cout << endl;
  }

  return 0;
}

