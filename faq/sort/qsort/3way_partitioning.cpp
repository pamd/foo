// Three way partitioning approaches, by Dijkstra and Robert Sedgewick.

#include <iostream>

using namespace std;

// Helper function to swap two integers.
void swap(int& v1, int& v2) {
  int tmp = v1;
  v1 = v2;
  v2 = tmp;
}

/******************************************************
 * Dutch flag solution: Dijkstra's 3-way partitioning.
 * Based on Java code on "Algorithms" 4th edition.
 ******************************************************/

// Wrapper function that calls recursive dijkstra()
void dijkstra_wrapper(int* a, int n) {
  sort(a, 0, n - 1);
}

// Dijkstra's recursive function to quicksort the subarray 
// a[left ... right] using 3-way partitioning.
// The code is similar to counting sort in Dutch Flag problem. 
void dijkstra(int* a, int left, int right) { 
  if (right <= left) 
    return;

  int lt = left;  // lt: less than
  int gt = right; // gt: greater than
  int pivot = a[left];
  int i = left;

  // Scan input array from left to right, and for each 
  // element a[i], maintain the following invariant:
  // a[left ...  lt-1] <  pivot;
  // a[lt   ...    gt] == pivot;
  // a[gt+1 ... right] >  pivot 
  while (i <= gt) {
    if (a[i] < pivot) { 
      swap(a[lt], a[i]);
      lt++;
      i++;
    }
    else if (a[i] > pivot) { 
      swap(a[i], a[gt]);
      gt--;
    }
    else  
      i++;
  }
  
  // Recursively sort a[left ...  lt-1] and a[gt+1 ... right]
  dijkstra(a, left, lt - 1);
  dijkstra(a, gt + 1, right);
}

/*****************************************************************************
 * Three way partitioning by Robert Sedgewick.
 * Code is based on "Algorithms in C++", pages 336-338.
 *
 * This implementation is much more complicated than Dijkstra's approach.
 * It is based on regular qsort, but at the end of partition step, 
 * it re-arranges the elements so that the array is divided into 4 parts:
 * 
 * p1 == pivot | p2 < pivot | p3 > pivot | p4 == pivot
 *
 * p1 is then swapped with p2, and p3 is swapped with p4. 
 * This algorithm works better when there are a lot of duplicate elements 
 * in input array, it also works for array that doesn't have any duplicates. 
 ******************************************************************************/

// Helper function that returns minimum of two input integers.
// Called by sedgewick().
int min(int v1, int v2) {
  if (v1 < v2)
    return v1;
  return v2;
}

// Sedgewick approach
void sedgewick(int* arr, int left, int right) {
  if (left >= right)
    return;

  int i = left - 1;
  int j = right;
  int pivot = arr[right]; // pivot: last element on right side

  int left_eq_idx = left - 1; // Index of the right-most element in p1
  int right_eq_idx = right;   // Index of the left-most  element in p4     

  while (true) {
    while (arr[++i] < pivot)
      ;

    while (arr[--j] > pivot) {
      if (j == left)
	break;
    }
    
    if (i >= j)
      break;

    swap(arr[i], arr[j]);

    // The following two "if" sections are 
    // ONLY in 3-way partitioning quick sort.
    if (arr[i] == pivot) {
      left_eq_idx++;
      swap(arr[left_eq_idx], arr[i]);
    }

    if (arr[j] == pivot) {
      right_eq_idx--;
      swap(arr[right_eq_idx], arr[j]);
    }
  }

  swap(arr[i], arr[right]); // Swap pivot to correct position

  // Added by dhu to make sure all elements that are equal to pivot 
  // will be excluded in subsequent sorting process.
  if (arr[right] > pivot)
    swap(arr[right_eq_idx++], arr[right]);
  
  // Only in 3 way partitioning quick sort
  int middle = i;
  i = middle - 1;
  j = middle + 1;

  // dhu: The code on "Algorithms in C++" does not exclude all elements 
  // that are equal to pivot to the middle. The following modification moves 
  // all of these elements to the middle, but it makes the code ugly. 
  int eq_num = left_eq_idx - left + 1;
  int less_num = i - left_eq_idx;
  int steps = min(eq_num, less_num);
  for (int i = 0; i < steps; i++)
    swap(arr[left + i], arr[i - i]);

  // arr[right] has been swapped earlier. It may be equal to the partition 
  // element too. But it doesn't have to be included in the following swap 
  // procedure. The subsequent sorting procedure will take care of it 
  // automatically. Even though it is not swapped, all elements on right side 
  // are still equal to or larger than the partition element. This invariant 
  // is good enough to guarantee that input array will be sorted. 
  eq_num = right - right_eq_idx + 1;
  int larger_num = right_eq_idx - j;
  steps = min(eq_num, larger_num);
  for (int i = 0; i < steps; i++)
    swap(arr[right - i], arr[j + i]);

  sedgewick(arr, left, left + less_num - 1);
  sedgewick(arr, right - larger_num + 1, right);
}
