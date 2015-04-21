/* Leetcode OJ: Follow up for "Search in Rotated Sorted Array":
 * What if duplicates are allowed?
 * Would this affect the run-time complexity? How and why?
 * Write a function to determine if a given target is in the array.
 */

// 40ms for large dataset
class Solution {
public:
  bool search(int A[], int n, int target) {
    if (n <= 0)
      return false;

    return helper(A, 0, n - 1, target);
        
  }

  // Recursive helper function
  bool helper(int A[], int left, int right, int target) {
    if (left < 0 || left > right)
      return false;

    int mid = left + (right - left) / 2;
    if (A[mid] == target)
      return true;

    // Left half is sorted
    if (A[mid] > A[left]) {
      if (target >= A[left] && target < A[mid])
	return helper(A, left, mid - 1, target);
      else
	return helper(A, mid + 1, right, target);
    }

    // Right half is sorted
    if (A[mid] < A[right]) {
      if (target > A[mid] && target <= A[right])
	return helper(A, mid + 1, right, target);
      else
	return helper(A, left, mid - 1, target);
    }
    
    /* If A[mid] == A[left] && A[mid] == A[right], the target value
     * could be on either half. So we have to search both halves.
     * In the worse case, it will take O(n) time.
     */
    return helper(A, left, mid - 1, target) || helper(A, mid + 1, right, target);
  }

};
