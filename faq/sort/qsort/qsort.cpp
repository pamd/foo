#include <iostream>

using namespace std;

// Helper function
void swap(int& v1, int& v2) {
  int tmp = v1;
  v1 = v2;
  v2 = tmp;
}


// Qsort in Career Cup 5th edition, 
// Chapter 10: Sorting and Searching.	
int partition_ccv5(int arr[], int left, int right) 
{
  int pivot = arr[(left + right) / 2]; 		
  while (left <= right) {
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
  return left; 
}
	
void qsort_ccv5(int arr[], int left, int right) {
  int index = partition_ccv5(arr, left, right); 
  if (left < index - 1) 
    qsort_ccv5(arr, left, index - 1);

  if (index < right) 
    qsort_ccv5(arr, index, right);

}

// Test harness
int main()
{
  //          0  1  2  3  4  5  6
  int a[] = { 2, 6, 3, 4, 2, 5 };
  int len = sizeof(a) / sizeof(int);
  qsort_3way(a, 0, len - 1);

  for (int i = 0; i < len; i++)
    cout << a[i] << " ";
  cout << endl;

  return 0;
}
