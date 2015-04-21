/* Merge sort with improvement: Eliminate the copy to the auxiliary array. 
 * Save time (but not space) by switching the role of the input and auxiliary 
 * array in each recursive call.
 *
 * Copied from Sedgewick coursera "Algorithms I" lecture, Week 3 #1, slide #21.
 */

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <assert.h>

using namespace std;

// Merge elements in A[left : mid] and A[mid + 1 : right] into aux[left : right]
void merge(int A[], int aux[], int left, int mid, int right) {
  int i = left;
  int j = mid + 1;
  for (int k = left; k <= right; k++) {
    if (i > mid)
      aux[k] = A[j++];
    else if (j > right)
      aux[k] = A[i++];
    else if (A[j] < A[i]) 
      aux[k] = A[j++];
    else
      aux[k] = A[i++];
  }
}

// Recursive sort
void recur_sort(int A[], int aux[], int left, int right) {
  if (left >= right)
    return;

  int mid = left + (right - left) / 2;

  // Sort elements in aux[left : mid]
  recur_sort(aux, A, left, mid); 

  // Sort elements in aux[mid + 1 : right]
  recur_sort(aux, A, mid + 1, right);

  // Merge elements in aux back into A
  merge(aux, A, left, mid, right);
}

// Merge sort, which is a wrapper of recur_sort()
void merge_sort(int A[], int n) {
  int aux[n];
  for (int i = 0; i < n; i++) 
    aux[i] = A[i];
  recur_sort(A, aux, 0, n - 1); 
}

// Helper function that tells whether input array is sorted or not
bool isSorted(int A[], int n) {
  for (int i = 1; i < n; i++) {
    if (A[i] < A[i - 1])
      return false;
  }

  return true;
}

// Test harness
int main() {
  srand(time(0));

  for (int it = 0; it < 1000; it++) {
    int n = rand() % 100;
    int A[n];
    for (int i = 0; i < n; i++) {
      A[i] = rand() % 100;
      //cout << A[i] << " ";
    }
    //cout << endl;
    
    merge_sort(A, n);
    assert(isSorted(A, n));

    /*
    for (int i = 0; i < n; i++) {
      cout << A[i] << " ";
    }
    cout << endl;
    */
  }

  return 0;
}
