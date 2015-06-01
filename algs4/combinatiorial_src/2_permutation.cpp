/*********************************************************************
 * Recursive algorithm to enumerate all N! permutations of N elements.
 * Start with permutation a[0] to a[N-1].
 * For each value of i:
 * 1) Swap a[i] into position 0
 * 2) Enumerate all (N-1)! permutations of a[1] to a[N-1]
 * 3) Clean up (swap a[i] back to original position)
 *
 * C++ code based on ALGS4 slides #11 and #12.
 * dhu note: for input array of { 0, 1, 2 }, the order of permuations are:
 *          0 1 2 
 *          0 2 1 
 *          1 0 2 
 *          1 2 0 
 *          2 1 0 
 *          2 0 1 
 * This is not exactly in an increasing order. 
 * So if order is required, this approach is not exactly correct.
 */

#include <iostream>
#include <vector>

using namespace std;

const int N = 3;
vector<int> a(N);

// Print out result
void process() {
  for (int i = 0; i < N; i++)
    cout << a[i] << " ";
  cout << endl;
}

// Recursively place N-k rooks in a[k] to a[N-1]
void perm(int k) {
  if (k == N) { 
    process(); 
    return; 
  }

  for (int i = k; i < N; i++) {
    swap(a[k], a[i]);
    perm(k+1);
    swap(a[i], a[k]); // VERY IMPORTANT: restore array to original order
  }

}

// Wrapper that calls perm()
void perm_wrapper() {
  for (int i = 0; i < N; i++) 
    a[i] = i;

  perm(0);
}
    
// Test harness
int main() {
  perm_wrapper();

  return 0;
}
