/* Leetcode OJ: Suppose a sorted array is rotated at some pivot unknown to you beforehand.
 * (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
 * You are given a target value to search. If found in the array, return its index; 
 * otherwise return -1.
 * You may assume no duplicate exists in the array.
 */

// 28ms for large dataset
class Solution {
public:
  int search(int A[], int n, int target) {
    if (n <= 0)
      return -1;
    
    int left = 0;
    int right = n - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (A[mid] == target)
	return mid;

      // Right half is sorted
      if (A[mid] < A[right]) {
	/* dhu note: NEVER write the next line as:
	 *   if (target > A[mid] && target < A[right])
	 */
	if (target >= A[mid] && target <= A[right])
	  left = mid + 1;
	else
	  right = mid - 1;
      }
      // Left half is sorted
      /* dhu note: NEVER write the next line as:
       *   else if (target > A[left] && target < A[mid])
       */ 
      else if (target >= A[left] && target <= A[mid]) 
	right = mid - 1;
      else
	left = mid + 1;
    }

    return -1;        
  }
};


// Dropbox solution: sort of tedious
int SearchInRotatedSortedArray(int array[], int low, int high, int target) {
  while (low <= high) {
    int mid = (low + high) / 2;
    if (target < array[mid]) {
      if (array[mid] < array[high]) // the higher part is sorted
	high = mid - 1; // the target would only be in lower part
      else  // the lower part is sorted
	if (target < array[low]) // the target is less than all elements in low part
	  low = mid + 1;
	else
	  high = mid - 1;
    }
    else if (array[mid] < target) {
      if (array[low] < array[mid]) // the lower part is sorted
	low = mid + 1; // the target would only be in higher part
      else {// the higher part is sorted
	if (array[high] < target) // the target is larger than all elements in higher part
	  high = mid - 1;
	else
	  low = mid + 1;
      }
    }
    else // if (array[mid] == target)
      return mid;
  }

  return -1;
}
