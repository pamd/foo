// Qsort in Career Cup 5th edition, 
// Chapter 10: Sorting and Searching.	

#include <iostream>

using namespace std;

// Partition: Using the element in the middle of input array as
// the pivot, scan both sides of the array, swap elements,
// then divide the input array into two parts:
// elements in the 1st part <= pivot
// elements in the 2nd part >= pivot
//
// Note that unlike the other implementations, in this approach, 
// the pivot element is NOT put into correct position after partition!
int partition(int arr[], int left, int right) {
  int pivot = arr[(left + right) / 2]; 		
  while (left <= right) {
    // Since the pivot is in the middle, left and right 
    // will never be out of range.
    while (arr[left] < pivot)  
      left++;
    
    while (arr[right] > pivot) 
      right--;
			
    if (left <= right) {
      swap(arr[left], arr[right]);
      left++;
      right--;
    }
  }

  // Do nothing with pivot, so it is NOT in correct position yet!
  return left; 
}
	
// Recursive sorting with the help of partition().
void qsort(int arr[], int left, int right) {
  if (left >= right)
    return;

  int index = partition(arr, left, right); 

  // Recursively sort the two parts separated by arr[index].
  // Because pivot element is not in correct position yet, 
  // we do not exclude a[index] in sorting process. 
  // THIS IS DIFFERENT FROM the other qsort approaches.
  qsort(arr, left, index - 1);
  qsort(arr, index, right);
}

// Test harness
int main() {
  //          0  1  2  3  4  5  6
  int a[] = { 2, 6, 3, 4, 2, 5 };
  int len = sizeof(a) / sizeof(int);
  qsort(a, 0, len - 1);

  for (int i = 0; i < len; i++)
    cout << a[i] << " ";
  cout << endl;

  return 0;
}
