/***********************************************************************
 * Given N jobs of varying length, divide among two machines to 
 * minimize the makespan (time the last job finishes).
 *
 * Slide #39:
 * Maintain difference in finish times and avoid recomputing cost 
 * from scratch. This has factor of N speedup (using Gray code order).
 * 
 * dhu: do not really understand how canBacktrack() should be implemented.
 * -----------------------------------------------------------------------
 */

#include <iostream>
#include <vector>

using namespace std;

const int N = 5;
vector<int> jobs(N);
vector<int> a(N);
vector<int> optimum(N);
int result = 0;
int sum = 0;

// Compare load in a[] with optimum and update optimum if necessary
void process() {
  int tmp = 0;
  for (int i = 0; i < N; i++) {
    if (a[i])
      tmp += jobs[i];
  }

  tmp = sum - 2 * tmp;
  if (tmp < 0)
    tmp = -tmp;
  if (tmp < result)
    result = tmp;
  optimum = a;
}

// Backtrack: do not really understand how this function 
// should be implemented.
bool canBacktrack(int k) {
  // ???
}

// Recursive partition
void partition(int k) {
  if (k == N) { 
    process(); 
    return;
  }

  if (canBacktrack(k)) 
    return;

  partition(k+1);
  a[k] = 1 - a[k];
  partition(k+1);
}

// Wrapper
void wrapper() {
  jobs[0] = 3;
  jobs[1] = 8;
  jobs[2] = 1;
  jobs[3] = 2;
  jobs[4] = 9;

  for (int i = 0; i < N; i++) 
    sum += jobs[i];

  result = sum;

  partition(0);
}

// Test harness
int main() {
  wrapper();

  for (int i = 0; i < N; i++) {
    if (optimum[i])
      cout << jobs[i] << " ";
  }
  cout << endl;
  cout << "Best result: " << result << endl;

  return 0;
}
