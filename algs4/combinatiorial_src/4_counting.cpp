/****************************************************************
 * Enumerate all N-digit base-R numbers.
 * C++ code based on java code on slide #23.
 * 
 * dhu: The idea is similar to the famous "phoen book" problem.
 */

#include <iostream>
#include <vector>

using namespace std;

const int N = 3;
const int R = 9;
vector<int> a(N);

// Print out a[]
void process() {
  for (int i = 0; i < N; i++) 
    cout << a[i] << " ";
  cout << endl;
}

// Enumerate base-R numbers in a[k] to a[N-1]
void count(int k) {
  if (k == N) { 
    process(); 
    return; 
  }

  for (int r = 0; r < R; r++) {
    a[k] = r;
    count(k+1);
  }

  // The following cleanup is not needed, because a[k] gets overwritten 
  // in above "for" loop at the beginning of each iteration 
  // a[k] = 0; 
}

// Wrapper 
void wrapper() {
  count(0);
}

// Test harness
int main() {
  wrapper();

  return 0;
}
