/* Leetcode OJ: Given a m x n matrix, if an element is 0, set its entire row and column to 0. 
 * Do it in place with CONSTANT space. */

// Online solution
#include <iostream>
#include <vector>

using namespace std;

void SetZeroes(vector<vector<int> > &matrix) {
    if (matrix.size() <= 0)return;
    int row = matrix.size();
    int col = matrix[0].size();

    bool setFirstRowZero = false;
    bool setFirstColZero = false;

    //check if any element in first row is 0, 
    //i.e. first row need to set to 0s
    for (int j = 0; j < col; ++j)
      if (matrix[0][j] == 0) {
	setFirstRowZero = true;
	break;
      }
    
    //check if any element in first column is 0, 
    //i.e. first column need to set to 0s
    for (int i = 0; i < row; ++i)
      if (matrix[i][0] == 0) {
	setFirstColZero = true;
	break;
      }

    //set first row and column as marker
    for (int i = 1; i < row; ++i)
      for (int j = 1; j < col; ++j) {
	if (matrix[i][j] == 0) {
	  //mark associated first row/column to 0
	  matrix[0][j] = 0;
	  matrix[i][0] = 0;
	}
      }

    //set all elements in marked rows/columns to 0
    for (int i = 1; i < row; ++i)
      for (int j = 1; j < col; ++j)
	if (matrix[i][0] == 0 || matrix[0][j] == 0)
	  matrix[i][j] = 0;

    //set first row to 0s. if necessary
    if (setFirstRowZero)
      for (int j = 0; j < col; ++j)
	matrix[0][j] = 0;

    //set first column to 0s. if necessary
    if (setFirstColZero)
      for (int i = 0; i < row; ++i)
	matrix[i][0] = 0;
}

// Test harness
int main(int argc, char** argv) {
  
  return 0;
}
