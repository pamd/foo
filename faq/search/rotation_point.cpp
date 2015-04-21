/* Find the rotation point (minimum) of a rotated sorted array.
 * http://www.mitbbs.com/article_t1/JobHunting/31778185_0_1.html
 */

#include <iostream>

using namespace std;

// This function is not correct when input array has duplicate elements.
int findMin_dhu(int arr[], int n) {
  int left = 0;
  int right = n - 1;
  while (left + 1 < right) {
    int mid = (left + right) / 2;
    if (arr[mid] > arr[left])
      left = mid;
    else
      right = mid;
  }

  return right;
}

/* Based on Java code in:
 * http://stackoverflow.com/questions/2796413/binary-search-to-find-the-rotation-point-in-a-rotated-sorted-list/2796523
 * This approach can not deal with duplicates either.
 */
int findMin_web(int arr[], int n) {
  int low = 0;
  int high = n - 1;
  while (arr[low] > arr[high]) {
    int mid = (low + high) /2;
    if (arr[mid] > arr[high]) 
      low = mid + 1;
    else 
      high = mid;
  }
  return low;
}

// Linear search the rotation point in a rotated sorted array 
// (helper function to deal with duplicates)
int linear_search(int arr[], int left, int right) {
  for (int i = left + 1; i <= right; i++) {
    if (arr[i] < arr[i - 1])
      return i;
  }

  return left;
}

/* dhu: in order to deal with duplicates, six cases have to be considered:
 * (1) middle > left && middle < right: array is not rotated at all, return 0;
 * (2) middle > left && middle >= right: rotation point is on right half;
 * (3) middle == left && middle < right: array is not rotated at all;
 * (4) middle == left && middle == right: rotation point could be on either side, 
 *     linear search on both sides is required;
 * (5) middle == left && middle > right: rotation point is on right half;
 * (6) middle < left: rotation point is on left half;
 */
int findMin(int arr[], int n) {
  int left = 0;
  int right = n - 1;
  while (left + 1 < right) {
    int mid = (left + right) / 2;
    // Case 1: middle > left && middle < right: array is not rotated at all, return 0;
    if (arr[mid] > arr[left] && arr[mid] < arr[right])
      return left;
    // Case 2: middle > left && middle >= right: rotation point is on right half;
    if (arr[mid] > arr[left])
      left = mid + 1;
    // Case 3: middle == left && middle < right: array not rotated at all
    else if (arr[mid] == arr[left] && arr[mid] < arr[right])
      return left;

    // Case 4: middle == left && middle == right: rotation point could be on either side, 
    //         linear search on both sides is required;
    else if (arr[mid] == arr[left] && arr[mid] == arr[right]) 
      return linear_search(arr, left, right);
    // Case 5: middle == left && middle > right: rotation point is on right half;
    else if (arr[mid] == arr[left] && arr[mid] > arr[right])
      left = mid + 1;
    // Case 6: middle < left: rotation point is on left half;
    else if (arr[mid] < arr[left])
      right = mid;

  }

  if (arr[left] > arr[right])
    return right;
  return left;
}

int main() {
  //   index:    0   1   2   3   4   5   6   7
  //int arr[] = { 14, 14, 16, 17, 18, 19, 14, 14 };
  //int n = sizeof(arr) / sizeof(int);
  
  int n = 1000;
  int arr[n];
  for (int i = 0; i < n; i++)
    arr[i] = 8;
  for (int i = 150; i < 200; i++)
    arr[i] = 1;
  for (int i = 200; i < 250; i++)
    arr[i] = 2;

  int ret = findMin(arr, n);
  cout << "index: "  << ret << endl;
  cout << "value: "  << arr[ret] << endl;

  return 0;
}
