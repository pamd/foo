/* Simplest version, Lomuto partitioning. 
 * Scan input array from left side only.
 *
 * Copied from "Programming Pearls" website. 
 */

#include <iostream>

using namespace std;

// Recursive qsort function that uses A[left] as pirot element.
// This function integrates partitioning and sorting steps 
// together into one function.
void lomuto(int arr[], int left, int right) {	
  if (left >= right)
    return;

  // arr[mid] is the right-most element that is smaller than pivot element.
  int mid = left;
  for (int i = left + 1; i <= right; i++) {
    if (arr[i] < arr[left])
      swap(arr[++mid], arr[i]);
  }
  
  swap(arr[left], arr[mid]); // Move pirot to correct position

  lomuto(left, mid - 1, arr);  // Sort elements on the left side of pivot
  lomuto(mid + 1, right, arr); // Sort elements on the right side of pivot
}

// We can also separate partitioning and sorting into two functions:
int partition(int arr[], int left, int right) {
  // arr[mid] is the right-most element that is smaller than pivot element.
  int mid = left;
  for (int i = left + 1; i <= right; i++) {
    if (arr[i] < arr[left])
      swap(arr[++mid], arr[i]);
  }
  
  swap(arr[left], arr[mid]); // Move pirot to correct position
  return mid;
}

// Sorting step: calls partition() and itself recursively
void qsort(int arr[], int left, int right) {
  if (left >= right)
    return;

  int p = partition(arr, left, right);
  qsort(arr, left, p - 1);
  qsort(arr, p + 1, right);
}


// Test harness
int main() {
  int a[] = { 2, 5, 1, 7, 8, 10, 4 };
  int len = sizeof(a) / sizeof(int);
  lomuto(a, 0, len - 1);
  for (int i = 0; i < len; ++i) {
    cout << a[i] << " ";
  }
  cout << endl;

}
