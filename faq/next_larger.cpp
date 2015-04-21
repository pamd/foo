/* Reserved Algorithms Discussion #65:
 * You are given an unsorted array A of n elements, 
 * now construct an array B for which B[i] = A[j], 
 * where j is the least number such that A[j] > A[i] and j>i. 
 * If such a j does not exist, B[i] = -1. 
 * For example:
 * A = { 1, 3, 5, 7, 6, 4, 8 }
 * B = { 3, 5, 7, 8, 8, 8, -1 }
 * Code is based ont he idea on:
 * http://discuss.joelonsoftware.com/default.asp?interview.11.803322.3
 * Note the pseudocode on that website is incorrect.
 * The algorithm is similar to the one in "Maximum area in histogram". 
 */

#include <iostream>
#include <vector>

using namespace std;

void next_larger(int A[], int len) {
  int B[len];
  vector<int> stack;  // accessory stack as a helper

  for (int i = len - 1; i >= 0; i--) {
    if (stack.size() == 0) {
      B[i] = -1;
      stack.push_back(A[i]);
      continue;
    }

    while (stack.size() && stack.back() <= A[i]) 
      stack.pop_back();
	
    if (stack.size() == 0) {
      B[i] = -1;
      stack.push_back(A[i]);
      continue;
    }

    B[i] = stack.back();
    stack.push_back(A[i]);
  }

  for (int i = 0; i < len; i++) 
    cout << B[i] << " ";
  cout << endl;
}

int main() {
  int A[] = { 1, 3, 9, 7, 6, 4, 8 };
  int len = sizeof(A) / sizeof(int);
  next_larger(A, len);

  return 0;
}
