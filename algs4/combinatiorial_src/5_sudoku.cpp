/* Fill 9-by-9 Sudokuso that every row, column, and box 
 * contains each of the digits 1 through 9.
 * 
 * The following C++ code is based on java code on slide #29.
 * It is incomplete because canBacktrack(int) is not found on booksite.
 */

#include <iostream>
#include <vector>

using namespace std;

vector<int> a(81);

// Print out Sudoku solution
void process() {
  for (int i = 0; i < 81; i++) {
    if (i % 9 == 0)
      cout << endl;
    cout << a[i] << " ";
  }
}

// Check whether current value of a[k] violates Sudoku constraint or not;
// Return true if it does, false otehrwise.
bool canBacktrack(int k) {
  // Implementation not found on booksite
  // ...............
}

// Solve Sudoku recursively 
void solve(int k) {
  if (k == 81) { // found a solution
    process(); 
    return;
  }

  // If cell k is initially filled in, recur on next cell
  if (a[k] != 0) { 
    solve(k + 1); 
    return;
  }

  // Try 9 possible digits for cell k
  for (int r = 1; r <= 9; r++) {
    a[k] = r;

    // If "a[k] = r" does not violate Sudoku constraint, keep going 
    if (!canBacktrack(k)) 
      solve(k + 1);

    // If "a[k] = r" violates Sudoku constraint, try the next possible value
  }

  a[k] = 0; // Clean up
}

// Sudoku wrapper
void sudoku_wrapper() {
  // Initialize input Sudoku
  // ... ...

  solve();
}

// Test harness
int main() {
  sudoku_wrapper();

  return 0;
}
