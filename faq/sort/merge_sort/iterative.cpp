/* Iterative merge sort, coped from "Algorithms in C++" 
 * page 352 Program 8.2 and page 360 Program 8.5.
 */

#include <iostream>

using namespace std;

const int maxN = 1000;

/* Based on "Algorithms in C++" page 352 Program 8.2
 * It merges two sorted sub-arrrays: 
 * arr[start_idx : middle_idx], arr[middle_idx+1 : end_idx]  */
void merge(int* arr, int start_idx, int middle_idx, int end_idx)
{
  static int aux[maxN];
  
  int i, j;

  for (i = middle_idx + 1; i > start_idx; i--) 
    aux[i - 1] = arr[i - 1];

  for (j = middle_idx; j < end_idx; j++)
    aux[end_idx + middle_idx - j] = arr[j + 1];

  for (int k = start_idx; k <= end_idx; k++) {
    if (aux[j] < aux[i]) 
      arr[k] = aux[j--];
    else
      arr[k] = aux[i++];
  }
}

/* My own merge function, which is more intuitive, but probably less efficient.
 * It merges two sorted sub-arrrays: 
 * arr[start_idx : middle_idx], arr[middle_idx+1 : end_idx]  */
void merge2(int* arr, int start_idx, int middle_idx, int end_idx)
{
  int len1 = middle_idx - start_idx + 1;
  int len2 = end_idx - middle_idx;
  int* aux = new int[len1 + len2];

  int s1 = start_idx;
  int s2 = middle_idx + 1;
  int k = 0;
  while (s1 <= middle_idx && s2 <= end_idx) {
    if (arr[s1] < arr[s2])
      aux[k++] = arr[s1++];
    else
      aux[k++] = arr[s2++];
  }

  while (s1 <= middle_idx) 
    aux[k++] = arr[s1++];

  while (s2 <= end_idx) 
    aux[k++] = arr[s2++];
    
  for (k = 0; k < len1 + len2; k++)
    arr[start_idx + k] = aux[k];

  delete [] aux;
}

// Helper function
int min(int v1, int v2)
{
  if (v1 < v2)
    return v1;
  return v2;
}

// Based on "Algorithms in C++" page 360 Program 8.5
void merge_sort_bottom_up(int* arr, int start_idx, int end_idx)
{
  for (int m = 1; m <= end_idx - start_idx; m = m + m) {
    for (int i = start_idx; i <= end_idx - m; i += m + m)
      merge2(arr, i, i + m - 1, min(i + m + m - 1, end_idx));

  }
}

// Traditional recursive merge sort
void merge_sort_recursive(int* arr, int start_idx, int end_idx)
{
  if (start_idx >= end_idx)
    return;

  int mid_idx = start_idx + (end_idx - start_idx) / 2;
  merge_sort_recursive(arr, start_idx, mid_idx);
  merge_sort_recursive(arr, mid_idx + 1, end_idx);
  merge(arr, start_idx, mid_idx, end_idx);
}

// Test harness
int main() 
{
  // index:   0  1  2  3  4  5  6   7   8
  int a[] = { 5, 6, 4, 2, 1, 8, 15, 13, 14 };
  int len = sizeof(a) / sizeof(int);
  //merge_sort_bottom_up(a, 0, len - 1);

  merge_sort_recursive(a, 0, len - 1);

  for (int i = 0; i < len; i++)
    cout << a[i] << " ";
  cout << endl;

  return 0;
}
