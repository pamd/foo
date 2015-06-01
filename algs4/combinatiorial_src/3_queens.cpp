/*************************************************************************
 * How many ways are there to place N queens on an N-by-N board so that
 * no queen can attack any other?
 *
 * C++ code is based on slides #18 and #19. It uses the idea of 
 * permutation (see permutation.cpp) to simplify backtracking.
 */

#include <vector>
#include <iostream>

using namespace std;

const int N = 5;
vector<int> a(N);

// Print out a[]
void process() {
  for (int i = 0; i < N; i++) 
    cout << a[i] << " ";
  cout << endl;
}

// Does a Queen that is placed at row k and column a[k]
// cause diagonal violation with any previous placement(s)?
// Return true if yes; return false otherwise. 
//
// Because addQueen() only considers permutations of a[], 
// the Queens we add will never cause row or column violation.
// This makes the validation easier.
bool canBacktrack(int k) {
  for (int i = 0; i < k; i++) {
    if ((a[i] - a[k]) == (k - i)) 
      return true;
    if ((a[k] - a[i]) == (k - i)) 
      return true;
  }

  return false;
}

// Recursive function that places N-k Queens in a[k] to a[N-1]
void addQueen(int k) {
  if (k == N) { 
    process(); 
    return; 
  }

  for (int i = k; i < N; i++) {
    swap(a[k], a[i]);

    // If adding Queen k leads to a diagonal violation, 
    // recover the configuration and try the next permutation
    if (!canBacktrack(k)) 
      addQueen(k + 1);

    swap(a[i], a[k]);
  }

}

// Wrapper that calls addQueen()
void wrapper() {
  // Initialize elements in a[]  
  for (int i = 0; i < N; i++) 
    a[i] = i;

  addQueen(0);
}

// Test harness
int main() {
  wrapper();

  return 0;
}
