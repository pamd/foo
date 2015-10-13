// Given a two dimensional array whose elements are either 0 or 1.
// Can we find a rectangle in this 2-D array whose 4 corners are all 1's.
// Return true if yes, false otherwise.
//
// http://www.mitbbs.com/article_t1/JobHunting/32673693_0_4.html

#include <vector>
#include <iostream>

using namespace std;

// Solution based on the pseudo code of blaze:
// O(n^2) time, the inner loop amortizes to O(1) time,
// becase every cell in map[][] will be set at most twice.
bool search(const vector<vector<int> >& A) {
   int row = A.size();
   int col = A[0].size();

   // Records whether row i and row j have two positions overlapping as 1's
   vector<vector<int> > map(row, vector<int>(row, 0));
   for (int c = 0; c < col; ++c) { // Scan by columns.
      vector<int> rows_with_1;     // Row numbers on c-th column where '1' is found.
      for (int r = 0; r < row; ++r) {
         if (A[r][c] == 1) {
            for (int k = 0; k < rows_with_1.size(); ++k) { // inner loop!
               int x = rows_with_1[k];
               ++map[x][r];
               if (map[x][r] == 2) { // Found it!
                  return true;
               }
            }
            rows_with_1.push_back(r);
         }
      }
   }

   return false;
}

// Test
int main() {
   vector<vector<int> > A(8, vector<int>(8, 0));
   A[2][3] = 1;
   A[2][5] = 1;
   A[2][7] = 1;

   A[5][3] = 1;
   A[5][7] = 1;

   bool ret = search(A);
   if (ret) {
      cout << "yes" << endl;
   }
   else {
      cout << "no" << endl;
   }

   return 0;
}
