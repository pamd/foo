/* Find k-th element from an unsorted array. 
 * Iterative approach. 
 * Copied from Robert Sedgewick "Algorithms I" 
 * lecture on Quick Sort, slide #26.
 */

// The code is very similar to binary search.
// See sedgewick_scan2.cpp for implementations of partition function.
int select(int A[], int n, int k) {
  assert(k >= 0 && k < n);

  int left = 0;
  int right = n - 1;

  // Since we know that the target is available in A[], 
  // the while loop below uses (left < right).
  // When left == right, left must be equal to k, and 
  // A[left] will be the element that we are looking for.
  while (left < right) {
    int j = partition(A, left, right);
    if (j == k)
      break;
    else if (j < k) 
      left = j + 1;
    else 
      right = j - 1;
  }

  return A[k];
}
