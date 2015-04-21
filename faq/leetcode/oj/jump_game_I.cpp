/* Given an array of non-negative integers, you are initially positioned 
 * at the first index of the array.
 * Each element in the array represents your maximum jump length at that position.
 * Determine if you are able to reach the last index.
 * For example:
 * A = [2,3,1,1,4], return true.
 * A = [3,2,1,0,4], return false.
 */

#include <iostream>

using namespace std;

// dhu: 44ms for large dataset 
class Solution {
public:
  bool canJump(int A[], int n) {
    if (n <= 1)
      return true;

    int right_edge = A[0];
    if (right_edge >= n - 1)
      return true;
    for (int i = 1; i <= right_edge; i++) {
      if (right_edge < i + A[i])
	right_edge = i + A[i];

      if (right_edge >= n - 1)
	return true;

    }

    return false;
  }
};

/*
int main() {
  int A[] = { 3, 2, 1, 0, 4};
  int n = sizeof(A) / sizeof(int);
  Solution foo;
  bool ret = foo.canJump(A, n);
  if (ret)
    cout << "yes" << endl;
  else
    cout << "no" << endl;

  return 0;
}
*/

// Dropbox solution
bool CanJump(int A[], int n) {
  int k = A[0]; // k starts from A[0]
  int i = 1;    // i starts from 1

  while (i <= k && i < n) {
    if (k < A[i] + i) 
      k = A[i] + i; // furthest we could jump so far
    ++i;
  }

  return i >= n; 
}


#include <stdio.h>

int main(int argc, char** argv) {
  int a[] = {2,3,1,1,4};
  int n = sizeof(a)/sizeof(int);
  printf("%d\n", CanJump(a,n)); // true
  
  int b[] = {3,2,1,0,4};
  n = sizeof(b)/sizeof(int);
  printf("%d\n", CanJump(b,n)); // false
  return 0;
}
