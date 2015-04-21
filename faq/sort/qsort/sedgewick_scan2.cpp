/* Robert Sedgewick's qsort approaches. 
 * Scan input array from both left and right sides.
 * 
 * Copied from "Algorithms in C++" and "Algorithms" 4th edition.
 */

#include <iostream>

using namespace std;

// Use arr[right] as the pivot element.
// Copied from "Algorithms in C++".
int partition1(int* arr, int left, int right) {
  int i = left - 1;
  int j = right;
  int pivot = arr[right];
  
  while (true) {
    // Scan input array from left to right.
    // This loop will be always terminated. 
    // The furthest it can reach will be arr[right]. 
    while (arr[++i] < pivot)
      ;  

    // Scan input array from right to left.
    // If j and i cross, terminate the loop.
    while (arr[--j] > pivot) {
      if (j == i)
	break;
    }

    if (i >= j)
      break;

    swap(arr[i], arr[j]);
  }

  swap(arr[i], arr[right]); // Swap pivot to the correct position

  return left;
}

// Use arr[left] as pivot element.
// Bsed on the Java code on "Algorithms" 4th edition.
// The idea is identical to partition1().
int partition2(int* arr, int left, int right) {
  int i = left;
  int j = right + 1;
  int pivot = a[left];
  while (true) { 
    // Scan input array from left to right
    while (a[++i] < pivot) {
      if (i == right) 
	break;
    }    

    // Scan input array from right to left.
    // Since a[left] is the pivot, j will never be less than left,
    // so a[--j] always points to a valid element in input array.
    while (a[--j] > pivot) 
      ;

    // Check if pointers cross
    if (i >= j) 
      break;
    
    swap(a[i], a[j]);
  }

  // Swap the povot element into the correct position
  swap(a[left], a[j]);
  
  // Now a[left ... j-1] <= a[j] <= a[j+1 ... right]
  return j;
}


// Recursive qsort()
void qsort(int* arr, int left, int right) {
  if (left >= right)
    return;

  // Call either partition1() or partition2()
  int p = partition1(arr, left, right); 
  // int p = partition2(arr, left, right); 

  // Sort both left and right sides of pivot element recursively
  qsort(arr, left, p - 1);
  qsort(arr, p + 1, right);
}
