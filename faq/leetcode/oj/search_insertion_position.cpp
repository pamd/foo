/* Leetcode OJ: Given a sorted array and a target value, return the index 
 * if the target is found. If not, return the index where it would be inserted 
 * so that the array would be still in order.
 * You may assume no duplicates in the array. Here are few examples.
 *
 * [1,3,5,6], 5 => 2
 * [1,3,5,6], 2 => 1
 * [1,3,5,6], 7 => 4
 * [1,3,5,6], 0 => 0
 *
 */

// 40ms for large dataset
class Solution {
public:
  /* If target exists in A[], return the index of target. 
   * If target does not exist in A[], return the index of 
   * the first element in A[] that is larger than target. */ 
  int searchInsert(int A[], int n, int target) {
    if (n <= 0)
      return 0;

    int insertion = -1;
    int left = 0;
    int right = n - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (A[mid] == target)
	return mid;
      if (A[mid] > target) {
	insertion = mid;
        right = mid - 1;
      }
      else 
	left = mid + 1;
    }

    /* If all elements in A are smaller than target, 
     * then target should be inserted at the end of A[]. */
    if (insertion == -1)
      return n;

    return insertion;
  }

};

// Solution by anson627: just a simple binary search
class Solution {
public:
  int searchInsert(int A[], int n, int target) {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (A[mid] > target) 
	right = mid - 1;
      else if (A[mid] < target) 
	left = mid + 1;
      else 
	return mid;
    }
    return left;
  }
};
