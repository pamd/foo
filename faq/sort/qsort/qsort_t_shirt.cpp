/* Qsort code on T-shirt, based on the java code from
 * Robert Sedgewick "Algorithms I" Coursera lecture of Week 3, 
 * part 2, slide #3.
 */

#include <iostream>
#include <stdlib.h>
#include <assert.h>

using namespace std;

// Recursive function
void recur_qsort(int A[], int left, int right) {
  int i = left;
  int j = right;

  int x = A[(left + right) / 2]; // Element in the middle as pirot
  do { 
    //while (A[i] < x && i < right)
    while (A[i] < x)
      i++;

    //while (A[j] > x && j > left)
    while (A[j] > x)
      j--;

    if (i <= j) {
      int tmp = A[i];
      A[i] = A[j];
      A[j] = tmp;
      i++;
      j--;
    }
    
  } while (i <= j);

  if (left < j)
    recur_qsort(A, left, j);

  if (i < right)
    recur_qsort(A, i, right);
}

// dhu revision: make the code more compact
// Now the code is almost identical to career_cup5.cpp 
void dhu_qsort(int A[], int left, int right) {
  int i = left;
  int j = right;
  int x = A[(left + right) / 2]; // Element in the middle as pirot

  // In the next line, both "i < j" and "i <= j" will work, 
  // but "i <= j" is better, because when i == j, if we use "i < j", 
  // the two recursive calls at the end will have one overlap 
  // element a[i], which costs some extra time. 
  while (i < j) { 
    while (A[i] < x)
      i++;
    while (A[j] > x)
      j--;

    // The next line MUST USE "i <= j", "i < j" will cause error in 
    // this input array: A[] = { 0, 2 }, because left is 0, right is 1,
    // and when current loop exits, i is 0 and j is 0, so it will keeping 
    // calling itself because "i < right". 
    if (i <= j) 
      swap(A[i++], A[j--]);
  } 

  if (left < j)
    dhu_qsort(A, left, j);

  if (i < right)
    dhu_qsort(A, i, right);
}

// Wrapper that calls the recursive function
void qsort(int A[], int n) {
  dhu_qsort(A, 0, n - 1);
}

// Helper function that tells whether input array is sorted or not
bool isSorted(int A[], int n) {
  for (int i = 1; i < n; i++) {
    if (A[i] < A[i - 1])
      return false;
  }

  return true;
}

// Print input array
void print(int A[], int n) {
  for (int i = 0; i < n; i++) {
    cout << A[i] << " ";
  }
  cout << endl;
}

// Test harness
int main() {
  srand(time(0));
  
  int range = 100;
  for (int it = 0; it < 100; it++) {
    int n = rand() % range;
    int A[n];
    for (int i = 0; i < n; i++) {
      A[i] = rand() % range;
    }

    cout << "Test #" << it << endl;
    //print(A, n);    

    qsort(A, n);

    //print(A, n);

    assert(isSorted(A, n));
  }
  

  //int A[2] = { 0, 2 };
  //qsort(A, 2);

  return 0;
}
